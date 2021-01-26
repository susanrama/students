# students
A program to save and download students' records on one course


This project was made for course Basics in C programming, Aalto University. 
The purpose of this code is to make it possible to save course's students and their points and also edit them. 
Student's will be saved in this format: \
Student_ID LastName FirstName PointsFromEachRoundSeparetedWithWhiteSpaces \
E.g. Like this \
123456 Gearloose Gyro 7 0 8 0 0 0 \
223344 Student Osmo 0 2 0 0 2 0 

Each student had been described as a structure. 
You can use all these functions: \
Student* RELEASEMEMORY(Student* start); \
Student* ADDSTUDENT(Student* start, char* opnro, char* Lname, char* Fname, int* points); \
Student* FILELOAD(const char* filename, Student* start); \
void SAVEFILE(Student* start, char* filename); \
void PRINT(Student* start); \
int TOTALPOINTS(int* points); \
void UPDATEPOINTS(Student* start, char* opnro, int round, int points); \
int main(void);

How to use these functions? \
Add a new student: A StudentID LastName FirstName \
Update points: U StudentID Round RoundPoints \
Print current students: L \
Save file: W filename \
Load file: O filename \
Close program: Q
