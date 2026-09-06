#include <stdio.h>
#include <string.h>

struct Drink
{
    char name[50];
    float price;
};

int main()
{
    struct Drink vodka;

    char name[50] = "";
    float price = 0.0;
    char yourName[30] = "";

    printf("What's your name? ");
    fgets(yourName, sizeof(yourName), stdin);
    //yourName[strlen(yourName) - 1] = '\0';

    printf("What is the name of the drink? ");
    fgets(name, sizeof(name), stdin);
    name[strlen(name) - 1] = '\0';

    printf("What is the price of %s? ", name);
    scanf(" %f", &price);

    strcpy(vodka.name, name);
    vodka.price = price;

    printf("The price for %s is %.2f", vodka.name, vodka.price);

    return 0;
}