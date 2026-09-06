#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getComputerChoice();
int getPlayerChoice();
int checkWinner(int computerChoice, int playerChoice);

int main()
{
    printf("---ROCK PAPER SCISSORS GAME---\n");
    printf("You play against computer\n");

    srand(time(NULL));

    int computerChoice = getComputerChoice();
    int playerChoice = getPlayerChoice();

    switch (playerChoice)
    {
    case 1:
        printf("You choose ROCK\n");
        break;
    
    case 2:
        printf("You choose PAPER\n");
        break;
    
    case 3:
        printf("You choose SCISSORS\n");
        break;
    }

    switch (computerChoice)
    {
    case 1:
        printf("Computer chooses ROCK\n");
        break;
    
    case 2:
        printf("Computer chooses PAPER\n");
        break;
    
    case 3:
        printf("Computer chooses SCISSORS\n");
        break;
    }

    if (computerChoice == playerChoice)
    {
        printf("DRAW!");
    }
    else
    {
        checkWinner(computerChoice, playerChoice);
    }

    return 0;
}

int getComputerChoice()
{
    return (rand() % 3) + 1; 
}
int getPlayerChoice()
{
    int playerChoice = 0;

    printf("Choose your move:\n");
    printf("1. ROCK\n");
    printf("2. PAPER\n");
    printf("3. SCISSORS\n");
    printf("You choose ");
    scanf("%d", &playerChoice);

    return playerChoice;
}
int checkWinner(int computerChoice, int playerChoice)
{    
    if ((playerChoice == 1 && computerChoice == 3) ||
        (playerChoice == 2 && computerChoice == 1) ||
        (playerChoice == 3 && computerChoice == 2))
    {
        printf("YOU WIN!");
    }
    else
    {
        printf("YOU LOOSE :(");
    }
    
    return 0;
}