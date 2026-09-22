#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int id;
    char firstName[255];
    char lastName[255];
    int age;
} Person;

void writeToFile(Person persons[], int nPersons, char mode[]);

int main()
{
    Person persons[] = {{1, "Adam", "Smith", 303}, 
                        {2, "Karl", "Marx", 208}};

    int nPersons = sizeof(persons) / sizeof(persons[0]);
    
    for(int i = 0; i < nPersons; i++)
    {
        printf("Id: %d, Full name: %s %s, Age: %d\n", persons[i].id, persons[i].firstName, persons[i].lastName, persons[i].age);
    }

    writeToFile(persons, nPersons, "a");

    return 0;
}

void writeToFile(Person persons[], int nPersons, char mode[1])
{
    FILE *f = fopen("database.txt", mode);
    if (f == NULL)
    {
        printf("ERROR");
        exit(1);
    }

    switch (mode[0])
    {
    case 'w':
        fprintf(f, "ID, FIRST NAME, LAST NAME, AGE\n");
        break;
    
    case 'a':
        for(int i = 0; i < nPersons; i++)
        {
            printf("Appending...\n");
            fprintf(f, "%d, %s, %s, %d\n", 
                    persons[i].id, persons[i].firstName,
                    persons[i].lastName, persons[i].age);
        }
        break;
    }

    fclose(f);
}