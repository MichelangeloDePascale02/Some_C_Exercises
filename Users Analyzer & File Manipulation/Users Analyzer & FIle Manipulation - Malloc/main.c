/**
 * Program that read a file called "users.txt", and extracts users'data 
 * into a struct called "User". If the extraction is successful the program:
 * 1) sort the users by their age 
 * 2) create a new file "students.txt", where will be stored all the informations of
 *    the users that are also students
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

// file definitions
#define FILE_NAME_USERS "users.txt"
#define FILE_NAME_STUDENTS "students.txt"
#define READ "r"
#define WRITE "w"
#define APPEND "a"

// Occupation definition
#define STUDENT "student"

// enum for boolean
enum Bool
{
    FALSE,
    TRUE
};

// struct that identifies an User
typedef struct User_File
{
    int userId;
    int age;
    char *sex;
    int filmSeen;
    char *occupation[14];
} User;

// Function prototype declaration area
int countLines(FILE *f);
int writeStudent(User *u, FILE *f, int size);
void extractUser(User *u, char *line);
void bubbleSort(User *u, int length);
void printUsers(User *u, int size);

int main()
{
    FILE *fUsers; // pointer at file structure
    User *users;  // users structure

    int usersLength = 0;
    char line[100];

    fUsers = fopen(FILE_NAME_USERS, READ); // open the reading stream

    if (fUsers != NULL)
    {
        int i = 0;

        puts("Users' file open correctly");
        usersLength = countLines(fUsers);
        printf("Numero utenti: %d\n", usersLength);
        users = (User *)malloc(sizeof(User) * usersLength); // allocate the users

        if (users != NULL)
        {
            rewind(fUsers); // rewind fpp
            puts("Users allocated correctly");

            // extract the lines from the file and fill the users' array
            while (fscanf(fUsers, "%s", line) == 1)
            {
                extractUser(&users[i], line);
                i++;
            }

            fclose(fUsers); // close the stream

            bubbleSort(users, usersLength); // sort the users by the age
            printUsers(users, usersLength);

            // write the students in another file
            FILE *fStudents;                              // students stream
            fStudents = fopen(FILE_NAME_STUDENTS, WRITE); // open the writing stream

            if (fStudents != NULL)
            {
                puts("\nStudents file open correctly");

                writeStudent(users, fStudents, usersLength);
                fclose(fStudents);
            }
        }
    }

    free(users);

    return 0;
}

int countLines(FILE *f)
{
    char c;
    int count = 0; // number of line

    while ((c = fgetc(f)) != EOF)
    {
        if (c == '\n')
            count++;
    }

    return count;
}

void extractUser(User *u, char *line)
{
    u->userId = atoi(strtok(line, ","));
    u->age = atoi(strtok(NULL, ","));
    u->sex = strtok(NULL, ",")[0];
    u->filmSeen = atoi(strtok(NULL, ","));
    strcpy(u->occupation, strtok(NULL, ","));
}

void bubbleSort(User *u, int length)
{
    int flag = TRUE; // true
    while (flag == 1)
    {
        flag = FALSE;

        for (int i = 0; i < length - 1; i++)
        {
            if (u[i].age > u[i + 1].age) // ordinamento crescente
            {
                int temp = u[i].age;
                u[i].age = u[i + 1].age;
                u[i + 1].age = temp;
                flag = TRUE;
            }
        }

        length--;
    }
}

void printUsers(User *u, int size)
{
    puts("ID\tAGE\tSEX\tFILMS\t    OCCUPATION\n");
    for (int i = 0; i < size; i++)
    {
        printf("%3d\t", u[i].userId);
        printf("%2d\t", u[i].age);
        printf("%c\t", u[i].sex);
        printf("%2d\t", u[i].filmSeen);
        printf("%14s\t", u[i].occupation);
        puts(""); // start new line
    }
}

int writeStudent(User *u, FILE *f, int size)
{
    int lineWrote = 0;
    for (int i = 0; i < size; i++)
    {
        if (strcmp(u[i].occupation, STUDENT) == 0)
        {
            lineWrote = fprintf(f, "%d,%d,%c,%d,%s\n",
                                u[i].userId, u[i].age, u[i].sex, u[i].filmSeen, u[i].occupation);
        }
    }

    return lineWrote;
}
