#include <stdio.h>
#include <stdbool.h>

#define TOP(field) ((field[0] == field[1]) && (field[1] == field[2]))
#define MIDDLE(field) ((field[3] == field[4]) && (field[4] == field[5]))
#define BOTTOM(field) ((field[6] == field[7]) && (field[7] == field[8]))

#define LEFT(field) ((field[0] == field[3]) && (field[3] == field[6]))
#define CENTER(field) ((field[1] == field[4]) && (field[4] == field[7]))
#define RIGHT(field) ((field[2] == field[5]) && (field[5] == field[8]))

#define MAINDIAGONAL(field) ((field[0] == field[4]) && (field[4] == field[8]))
#define ANTIDIAGONAL(field) ((field[2] == field[4]) && (field[4] == field[6]))

char gameLoop();

int main(){
    char continuation = '\0';
    int gamesCount = 0;
    int xWins = 0;
    int oWins = 0;
    int draws = 0;
    char gameResult = '\0';

    do
    {
        gamesCount++;
        gameResult = gameLoop();

        switch (gameResult)
        {
        case 'X':
            xWins++;
            break;

        case 'O':
            oWins++;
            break;

        default:
            draws++;
        }
        
        while (continuation != 'Y' || continuation != 'n' || continuation != 'y' || continuation != 'N')
        {
            printf("\nContinue? [Y/n] ");
            scanf(" %c", &continuation);

            if (continuation == 'N' || continuation == 'n')
            {
                printf("\nThanks for playing!\n");
                printf("Games Played\txWins\toWins\tDraws\n%d\t\t%d\t%d\t%d\n", gamesCount, xWins, oWins, draws);
                return 0;
            }
            else if (continuation == 'Y' || continuation == 'y')
            {
                break;
            }
            else
            {
                printf("\nPlease choose Y/y (yes) or N/n (no)");
            }
        }
    } while (continuation == 'Y' || continuation == 'y');
}

char gameLoop(){
    char field[9] = "123456789";
    int choice = 0;
    bool WinnerNotDecided = true;
    char player = 'X';
    int MovesCount = 0;
    
    int gamesCount = 0;
    int xWins = 0;
    int oWins = 0;
    int draws = 0;

    while (true)
    {        
        printf(" %c | %c | %c\n", field[0], field[1], field[2]);
        printf("-----------\n");
        printf(" %c | %c | %c\n", field[3], field[4], field[5]);
        printf("-----------\n");
        printf(" %c | %c | %c\n", field[6], field[7], field[8]);

        // Draw logic
        MovesCount++;
        if (MovesCount == 10)
        {
            draws++;
            printf("Draw!");
            return 'D';            
        }

        // Win logic
        else if (TOP(field) || MIDDLE(field) || BOTTOM(field) || 
                LEFT(field) || CENTER(field) || RIGHT(field) || 
                MAINDIAGONAL(field) || ANTIDIAGONAL(field))
        {
            if (player == 'X')
            { 
                player = 'O';
                oWins++;
            }
            else
            { 
                player = 'X';
                xWins++;
            }

            printf("Player %c wins!", player);
            return player;
        }
        
        else 
        {            
        printf("Player %c turn\n", player);

        do
        {
            printf("What field do you want to take? ");
            scanf("%d", &choice);

            if (choice > 9 || (field[choice-1] == 'X') || (field[choice-1] == 'O'))
            {
                printf("\nPlease choose valid field!\n");
            }

        } while (choice > 9 || (field[choice-1] == 'X') || (field[choice-1] == 'O'));

        field[choice-1] = player;

        if (player == 'X') { player = 'O'; }
        else { player = 'X'; }
        }
    }
}