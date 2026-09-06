#include <stdio.h>
#include <string.h>

int main(){
    int first = 0;
    int second = 1;

    int n = 0;
    char string[10] = "";

    printf("Type 'FIBONACCI': ");
    scanf("%s", string);

    if (strcmp(string, "FIBONACCI") != 0) {return 0;}

    printf("What Fibonacci number are you interested in? ");
    scanf("%d", &n);

    if (n == 1)
    {
        printf("%d",first);
    }

    else if (n == 2)
    {
        printf("%d",second);
    }

    else
    {
        int current = 0;

        for (int i = 3; i <= n; i++)
        {
            current = first + second;
            first = second;
            second = current;
        }

        printf("%d",current);
    }

    return 0;
}