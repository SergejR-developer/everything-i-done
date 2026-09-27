/*
This project represents atempt to understand how to work with .txt files in C.
Writes or appends to a file depending on whether it exists or not
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct{
    int id;
    char firstName[255];
    char lastName[255];
    int age;
} Person;

const char cols[] = "ID, FIRST NAME, LAST NAME, AGE\n"; 

void writeToFile();
char modeForFile();

int main()
{
    int choice = 0;
    printf("Welcome to the database. Columns are as follows: %s\nWhat are you interested in?\n", cols);
    printf("1. Write to the file\n2. Read from the file (Under Development)\n3. Change line in the file (Under Development)\n");
    printf("Enter your choice: ");
 
    while(choice != 1 || choice != 2 || choice != 3)
    {
        scanf(" %d", &choice);

        switch (choice)
        {
            case 1:
                writeToFile();
                break;
            case 2:
                printf("UNDER DEVELOPMENT");
                return 0;
                break;
            case 3:
                printf("UNDER DEVELOPMENT");
                return 0;
                break;
            default:
                printf("Please enter valid choice: ");
                break;
        }
        break;
    }

    return 0;
}

void writeToFile()
{
    Person person = {};
    char firstName[255] = "";
    char lastName[255] = "";
    char mode[1] = "";

    printf("\nWRITING TO FILE\n");
    printf("Enter ID: "); //Will be changed in the future
    scanf("%d", &person.id);

    getchar();
    printf("Enter first name: ");
    fgets(firstName, sizeof(firstName), stdin);
    firstName[strlen(firstName) - 1] = '\0';

    printf("Enter last name: ");
    fgets(lastName, sizeof(lastName), stdin);
    lastName[strlen(lastName) - 1] = '\0';

    printf("Enter age: ");
    scanf("%d", &person.age);

    strcpy(person.firstName, firstName);
    strcpy(person.lastName, lastName);

    mode[0] = modeForFile();
    
    FILE *f = fopen("database.txt", mode);
    if (f == NULL)
    {
        printf("ERROR");
        exit(1);
    }

    if(mode[0] == 'w')
    {
        fprintf(f, "%s", cols);
    }

    fprintf(f, "%d, %s, %s, %d\n", person.id, person.firstName, person.lastName, person.age);

    fclose(f);
}

char modeForFile()
{
    if(access("database.txt", F_OK) == 0)
    {
        return 'a'; //file exists
    }
    else
    {
        return 'w'; //file doesn't exist
    }
}