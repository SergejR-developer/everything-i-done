#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image/stb_image_write.h>

#define PROXIMITY_BIAS 0.5 //proximity to root
#define CORNER_BIAS -0.2 //being in a corner

void generateMatrix(int rows, int cols, int rootRow, int rootCol, float threshold, float matrix[rows][cols]);
int* twoDtoOneD(int rows, int cols, float matrix[rows][cols]);
void createPNG(int *array, int rows, int cols);

int main()
{
    srand(time(NULL));

    int rows = 32;
    int cols = 16;
    float matrix[rows][cols];

    int rootRow = rand() % rows;
    int rootCol = rand() % cols;

    float threshold = .53;

    generateMatrix(rows, cols, rootRow, rootCol, threshold, matrix);

    int *array = twoDtoOneD(rows, cols, matrix);

    createPNG(array, rows, cols);

    return 0;
}

void generateMatrix(int rows, int cols, int rootRow, int rootCol, float threshold, float matrix[rows][cols])
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++) {
            matrix[i][j] = (float)rand() / (float)RAND_MAX;

            if ((i == 0 && j == 0) || (i == 0 && j == cols - 1) ||
                (i == rows - 1 && j == 0) || (i == rows - 1 && j == cols - 1))
            {
                matrix[i][j] += CORNER_BIAS;
            }
            if ((i == rootRow && abs(rootCol - j) == 1) ||
                (j == rootCol && abs(rootRow - i) == 1))
            {
                matrix[i][j] += PROXIMITY_BIAS;
            }
            else if (abs(rootRow - i) == 1 && abs(rootCol - j) == 1)
            {
                matrix[i][j] += PROXIMITY_BIAS / 2;
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

int* twoDtoOneD(int rows, int cols, float matrix[rows][cols])
{
    int *array = malloc(sizeof(int) * rows * cols);
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

void createPNG(int *array, int rows, int cols)
{
    int channels = 3;
    int size = rows * cols * channels;

    unsigned char *data = malloc(size);
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