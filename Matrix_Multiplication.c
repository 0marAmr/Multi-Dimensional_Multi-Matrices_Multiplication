#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int *M;
    int rows, columns;
} MATRIX;

typedef enum
{
    FALSE,
    TRUE
} bool;

void get_size_ip(int *, int *);
MATRIX create_mat(int rows, int colums);
bool check(int, int);
void print_mat(MATRIX const *const MAT);
MATRIX multiply(MATRIX const *const MAT1, MATRIX const *const MAT2);

int main()
{
    int row, column;
    get_size_ip(&row, &column);
    MATRIX M1 = create_mat(row, column);

    while (row && column) // loops till either row or col input is zero
    {
        get_size_ip(&row, &column);
        if (!check(M1.columns, row))
        {
            printf("cannot be multiplied\n");
            continue;
        }
        MATRIX M2 = create_mat(row, column); // pirnt M2
        
        M1 = multiply(&M1, &M2); // save result in M1
        print_mat(&M1);
    }
}

void get_size_ip(int *row, int *col)
{
    printf("enter the size of the matrix as Row x Column\n");
    scanf("%dx%d", row, col);
}

MATRIX create_mat(int rows, int colums)
{
    MATRIX MAT = {NULL, rows, colums};
    int elements = rows * colums;
    MAT.M = (int *)calloc(rows * colums, sizeof(int));
    printf("enter %d elements\n", elements);
    fflush(stdout);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < colums; j++)
            scanf("%d", (MAT.M + colums * i + j));
    print_mat(&MAT);
    return MAT;
}

bool check(int col1, int row2)
{
    return col1 == row2;
}

void print_mat(MATRIX const *const MAT)
{
    printf("\n");
    for (int i = 0; i < MAT->rows; i++)
    {
        for (int j = 0; j < MAT->columns; j++)
            printf("%d   ", *(MAT->M + MAT->columns * i + j));
        printf("\n");
    }
    printf("\n");
}
MATRIX multiply(MATRIX const *const MAT1, MATRIX const *const MAT2)
{
    MATRIX MAT_ANS = {NULL, MAT1->rows, MAT2->columns};
    MAT_ANS.M = (int *)calloc(MAT_ANS.rows * MAT_ANS.columns, sizeof(int));
    for (int i = 0; i < MAT_ANS.rows; i++)
        for (int j = 0; j < MAT_ANS.columns; j++)
            for (int k = 0; k < MAT2->rows; k++)
                *(MAT_ANS.M + MAT_ANS.columns * i + j) += *(MAT1->M + MAT1->columns * i + k) * *(MAT2->M + MAT2->columns * k + j);
    free(MAT1->M);
    free(MAT2->M);
    return MAT_ANS;
}
