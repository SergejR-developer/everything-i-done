#include <stdio.h>

int main()
{
    int twoD[2][3] = {{1, 2, 3}, {4, 5, 6}};
    int oneD[6];

    int counter = 0;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            oneD[counter++] = twoD[i][j];
        }
    }

    for (int i = 0; i < 6; i++)
    {
        printf("%d ", oneD[i]);
    }

    return 0;
}