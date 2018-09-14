/**
 * C program to check whether a matrix is symmetric matrix or not
 */

#include <stdio.h>

int main()
{
    int A[3][3], B[3][3];
    int row, col, isSymmetric;

    /*
     * Reads elements in matrix A from user
     */
    printf("Enter elements in matrix of size 3x3: \n");
    for(row=0; row<3; row++)
    {
        for(col=0; col<3; col++)
        {
            scanf("%d", &A[row][col]);
        }
    }

    /*
     * Finds the transpose of matrix A
     */
    for(row=0; row<3; row++)
    {
        for(col=0; col<3; col++)
        {
            /* Stores each row of matrix A to each column of matrix B */
            B[row][col] = A[col][row];
        }
    }

    /*
     * Checks whether matrix A is equal to its transpose or not
     */
    isSymmetric = 1;
    for(row=0; row<3 && isSymmetric; row++)
    {
        for(col=0; col<3; col++)
        {
            /* If matrix A is not equal to its transpose */
            if(A[row][col] != B[row][col])
            {
                isSymmetric = 0;
                break;
            }
        }
    }

    /*
     * If the given matrix is symmetric.

     */
    if(isSymmetric==1)
    {
        printf("\nThe given matrix is Symmetric matrix: \n");

        for(row=0; row<3; row++)
        {
            for(col=0; col<3; col++)
            {
                printf("%d ", A[row][col]);
            }

            printf("\n");
        }
    }
    else
    {
        printf("\nThe given matrix is not Symmetric matrix.");
    }

    return 0;
}
