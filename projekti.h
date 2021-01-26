#ifndef PROJEKTI_H
#define PROJEKTI_H

typedef struct student_st {
	char* firstname;
	char* lastname;
	char nro[7];
	int points[6];
	struct student_st* next;
} Student;

Student* RELEASEMEMORY(Student* start);
Student* ADDSTUDENT(Student* start, char* opnro, char* Lname, char* Fname, int* points);
Student* FILELOAD(const char* filename, Student* start);
void SAVEFILE(Student* start, char* filename);
void PRINT(Student* start);
int TOTALPOINTS(int* points);
void UPDATEPOINTS(Student* start, char* opnro, int round, int points);
int main(void);

#endif