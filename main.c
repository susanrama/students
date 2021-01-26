#include "projekti.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void UPDATEPOINTS(Student* start, char* opnro, int round, int points) {
	Student* pointer = start;
	int found = 0;
	while (pointer != NULL) {
		if (strncmp(pointer->nro, opnro, 6) == 0) {
			pointer->points[round - 1] = points;
			found = 1;
			break;
		}
		pointer = pointer->next;
	}
	if (found == 1)
		printf("Points updated successfully! :)\n");
	else
		printf("Couldn't find student with that number.\n");
}

int TOTALPOINTS(int* points) {
	int sum = 0;
	for (int i = 0; i < 6; i++) {
		sum += points[i];
	}
	return sum;
}

void PRINT(Student* start) {
	
	Student* pointer = start; 
	int count = 0;
	while (pointer != NULL) {
		count++;
		pointer = pointer->next;
	}
	int* TOTAL = malloc(count * sizeof(int));   
	if (!TOTAL)
		printf("MEMORY ERROR!\n");
	int i = 0;
	pointer = start;
	while (pointer != NULL) {
		TOTAL[i] = TOTALPOINTS(pointer->points);  // luodaan lista, jossa on opiskelijoiden kokonaispisteet niillä indekseillä, joilla opiskelijat ovat 
		i++;
		pointer = pointer->next;
	}
	int* ORDER = malloc(count * sizeof(int));   
	if (!ORDER)
		printf("MEMORY ERROR!\n");
	for (int i = 0; i < count; i++) {
		ORDER[i] = i;							// luodaan lista indekseistä
	}
	for (int i = 0; i < count; i++) {
		for (int j = 0; j < count; j++) {
			if (TOTAL[ORDER[i]] > TOTAL[ORDER[j]]) {    // pyöritetään indeksit suuruusjärjestykseen
				int temp = ORDER[i];
				ORDER[i] = ORDER[j];
				ORDER[j] = temp;
			}
		}
	}
	printf("%6s %15s %15s %8s %3s %3s %3s %3s %3s %4s\n", "Number",
		"Last name", "First name", "Round: 1", "2", "3", "4", "5", "6", "Sum");
	
	int j;
	for (int i = 0; i < count; i++) {
		j = 0;
		pointer = start;
		while (pointer != NULL) {
			if (ORDER[i] == j) {
				printf("%6s %15s %15s %8d %3d %3d %3d %3d %3d %4d\n", pointer->nro, pointer->lastname, pointer->firstname,
					pointer->points[0], pointer->points[1], pointer->points[2], pointer->points[3], pointer->points[4], pointer->points[5], TOTALPOINTS(pointer->points));
			}
			j++;
			pointer = pointer->next;
		}
	}
	free(ORDER);
	free(TOTAL);
}

void SAVEFILE(Student* start, char* filename) {
	FILE* f = fopen(filename, "w");
	Student* pointer = start;
	if (!f) {
		printf("Opening file failed.\n");
		return;
	}
	while (pointer != NULL) {
		fprintf(f, "%s %s %s %d %d %d %d %d %d\n", pointer->nro, pointer->lastname, pointer->firstname,
			pointer->points[0], pointer->points[1], pointer->points[2], pointer->points[3], pointer->points[4], pointer->points[5]);
		pointer = pointer->next;
	}
	fclose(f);
}

Student* FILELOAD(const char* filename, Student* start) {
	char read[80];
	int ret;
	char opnro[7], Fname[15], Lname[15];
	int points[6] = { 0 };
	start = RELEASEMEMORY(start);
	FILE* f = fopen(filename, "r");
	if (!f) {
		printf("Opening file failed.\n");
		return NULL;
	}
	while (fgets(read, 80, f) != NULL) {
		ret = sscanf(read, "%s %s %s %d %d %d %d %d %d", opnro, Lname, Fname, &points[0],
			&points[1], &points[2], &points[3], &points[4], &points[5]);
		if (ret == 9)
			start = ADDSTUDENT(start, opnro, Lname, Fname, points);
		else
			printf("Invalid line in file.\n");
	}
	fclose(f);
	return start;
}

Student* ADDSTUDENT(Student* start, char* opnro, char* Lname, char* Fname, int* points) {
	Student* new, * helper;  //uusi opiskelija ja avustava pointteri
	if ((new = (Student*)malloc(sizeof(Student))) == NULL) {
		printf("Mallocating memory failed.\n");
		return NULL;
	}
	if ((new->firstname = (char*)malloc((strlen(Fname) * sizeof(char)) + 1)) == NULL) {
		printf("Mallocating memory for firstname failed.\n");
		return NULL;
	}
	if ((new->lastname = (char*)malloc((strlen(Lname) * sizeof(char)) + 1)) == NULL) {
		printf("Mallocating memory for lastname failed.\n");
		return NULL;
	}
	strcpy(new->firstname, Fname);
	strcpy(new->lastname, Lname);
	strcpy(new->nro, opnro);
	for (int i = 0; i < 6; i++)
		new->points[i] = points[i];
	new->next = NULL;
	if (start == NULL)
		start = new;
	else {
		helper = start;
		while (helper->next != NULL)
			helper = helper->next;
		helper->next = new;
	}
	return start;
}

Student* RELEASEMEMORY(Student* start) {
	Student* pointer = start;  //tyhjennetään tämä tässä mihin viitataan ja sitten siitä tulee seuraava
	while (pointer != NULL) {
		start = pointer->next;
		free(pointer->firstname);
		free(pointer->lastname);
		free(pointer);
		pointer = start;
	}
	return start;
}

int main(void) {
	int o = 1;
	char DO[2];
	char filename[15];
	char opnro[7];
	char Fname[15];
	char Lname[15];
	int ret, round, roundpoints;
	int points[6] = { 0 };
	Student* start = NULL;
	while (o) {
		char read[80];
		if (fgets(read, sizeof(read), stdin) == NULL)
			printf("Nothing read.");
		switch (read[0]) {
		case 'A':
			//add new studentchar 
			ret = sscanf(read, "%s %s %s %s", DO, opnro, Lname, Fname);
			if (ret == 4)
				start = ADDSTUDENT(start, opnro, Lname, Fname, points);
			if (start != NULL) {
				printf("Student added successfully!\n");
			}
			else
				printf("For some reason, couldn't add student. :(\n");
			break;
		case 'U':
			ret = sscanf(read, "%s %s %d %d", DO, opnro, &round, &roundpoints);
			if (ret == 4) //update points
				UPDATEPOINTS(start, opnro, round, roundpoints);
			break;
		case 'L':
			PRINT(start);
			//print the situation
			break;
		case 'W':
			ret = sscanf(read, "%s %s", DO, filename);
			if (ret == 2) {
				SAVEFILE(start, filename);
				printf("Students are now in the file %s\n", filename);
			}
			else
				printf("Check the way you called for this operation.\n");
			//save results in file
			break;
		case 'O':
			ret = sscanf(read, "%s %s", DO, filename);
			if (ret == 2) {
				start = FILELOAD(filename, start); //download results and replace them in memory
				if (start != NULL)
					printf("Students read successfully from file %s!\n", filename);
			}
			else
				printf("Check the way you called this function.\n");
			break;
		case'Q':
			o = 0;
			start = RELEASEMEMORY(start);
			if (start == NULL)
				printf("Memory released and program will shut down.");//quit program and release memory
			break;
		default:
			printf("This command does nothing. Give another one to do something!\n");
		}
	}
}