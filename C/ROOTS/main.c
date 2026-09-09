/*
Creates pseudo-random matrix with two biases based on threshold.
Using stb_image creates roots.png with 3 colours.
White for the "background", black for the "root" and grey for "branches"
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image/stb_image_write.h>

#define PROXIMITY_BIAS 0.5 //proximity to root
#define CORNER_BIAS -0.2 //being in a corner

void generateMatrix(int rows, int cols, int rootRow, int rootCol, float threshold, float matrix[rows][cols]);
int degreeOfProximity (int rootRow, int rootCol, int currRow, int currCol);
int * twoDtoOneD(int rows, int cols, float matrix[rows][cols]);
void createPNG(int *array, int rows, int cols);

int main()
{
    srand(time(NULL));

    const int rows = 16;
    const int cols = 16;
    float matrix[rows][cols];

    const int rootRow = rand() % rows;
    const int rootCol = rand() % cols;

    const float threshold = .53;

    generateMatrix(rows, cols, rootRow, rootCol, threshold, matrix);

    int * array = twoDtoOneD(rows, cols, matrix);

    createPNG(array, rows, cols);

    return 0;
}

void generateMatrix(int rows, int cols, int rootRow, int rootCol, float threshold, float matrix[rows][cols])
{
    /*
    Generates matrix based on biases
    
    rows, cols - dimensions of the matrix
    rootRow, rootCol - parameters of the root
    threshold - given threshold
    matrix[rows][cols] - matrix to generate
    */
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++) {

            if (i == rootRow && j == rootCol)
            {
                continue;
            }
            
            matrix[i][j] = (float)rand() / (float)RAND_MAX;
            matrix[i][j] += (PROXIMITY_BIAS / degreeOfProximity(rootRow, rootCol, i, j));

            if ((i == 0 && j == 0) || (i == 0 && j == cols - 1) ||
                (i == rows - 1 && j == 0) || (i == rows - 1 && j == cols - 1))
            {
                matrix[i][j] += CORNER_BIAS;
            }         
            
            if (matrix[i][j] >= threshold)
            {
                matrix[i][j] = 1;
            }
            else
            {
                matrix[i][j] = 0;
            }
        }
    }

    matrix[rootRow][rootCol] = 2.0;

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            printf("%2.f", matrix[i][j]);
        }
        printf("\n");
    }
}

int degreeOfProximity (int rootRow, int rootCol, int currRow, int currCol)
{
    /*
    Returns non-euclidean distance from root to current pixel

    rootRow, rootCol - parameters of the root
    currRow, currCol - parameters of the current pixel
    */
    return abs(rootRow - currRow) + abs(rootCol - currCol);
}

int * twoDtoOneD(int rows, int cols, float matrix[rows][cols])
{
    /*
    Convertes 2d matrix into 1d array
    
    rows, cols - dimensions of the matrix
    matrix[rows][cols] - matrix to generate

    returns pointer to a 1d array
    */
    int * array = malloc(sizeof(int) * rows * cols);
    if(array == NULL)
    {
        exit(-1);
    }

    int count = 0;
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            array[count++] = matrix[i][j];
        }
    }

    free(array);
    return array;
}

void createPNG(int * array, int rows, int cols)
{
    /*
    Creates 3-channel png using stbi_image_write

    array - pointer to a 1d array
    rows, cols - dimensions of the matrix
    */
    int channels = 3;
    int size = rows * cols * channels;

    unsigned char * data = malloc(size);
    int i = 0;
    for (unsigned char *p = data; p != data + size; p+=channels)
    {
        switch (array[i])
        {
        case 1:
            *p       = 85;
            *(p + 1) = 85;
            *(p + 2) = 85;
            break;
        
        case 2:
            *p       = 0;
            *(p + 1) = 0;
            *(p + 2) = 0;
            break;

        default:
            *p       = 255;
            *(p + 1) = 255;
            *(p + 2) = 255;
            break;
        }
        i++;
    }

    stbi_write_png("roots.png", cols, rows, channels, data, cols * channels);

    free(data);
}