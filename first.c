#include <stdio.h>
void DataEntry(int fst[][10], int sec[][10], int row1, int column1, int row2, int column2);
void MatrixMult(int fst[][10], int sec[][10], int multResult[][10], int row1, int column1, int row2, int column2);
void display(int mult[][10], int row1, int column2);

int main() {
    int fst[10][10], sec[10][10], mult[10][10], row1, column1, row2, column2;
    printf("Kindly Enter rows and the column for the first matrix: ");
    scanf("%d %d", &row1, &column1);
    printf("Kindly Enter rows and column for the second matrix: ");
    scanf("%d %d", &row2, &column2);


    while (column1 != row2) {
        printf("Error encountered! Enter rows and columns again.\n");
        printf("Enter the rows and the column for the first matrix: ");
        scanf("%d%d", &row1, &column1);
        printf("Enter the rows and the column for the first matrix: ");
        scanf("%d%d", &row2, &column2);
    }


    DataEntry(fst, sec, row1, column1, row2, column2);

    MatrixMult(fst, sec, mult, row1, column1, row2, column2);


    display(mult, row1, column2);

    return 0;
}

void Datantry(int fst[][10], int sec[][10], int row1, int column1, int row2, int column2) {
    printf("\nEnter the elements in the matrix 1:\n");

    for (int i = 0; i < row1; ++i) {
        for (int j = 0; j < column1; ++j) {
            printf("Enter a%d%d: ", i + 1, j + 1);
            scanf("%d", &fst[i][j]);
        }
    }
    printf("\nEnter elements of matrix 2:\n");

    for (int i = 0; i < row2; ++i) {
        for (int j = 0; j < column2; ++j) {
            printf("Enter b%d%d: ", i + 1, j + 1);
            scanf("%d", &sec[i][j]);
        }
    }
}

void MatrixMult(int fst[][10], int sec[][10], int mult[][10], int row1, int column1, int row2, int column2) {


    for (int i = 0; i < row1; ++i) {
        for (int j = 0; j < column2; ++j) {
            mult[i][j] = 0;
        }
    }


    for (int i = 0; i < row1; ++i) {
        for (int j = 0; j < column2; ++j) {
            for (int k = 0; k < column1; ++k) {
                mult[i][j] += fst[i][k] * sec[k][j];
            }
        }
    }
}

void display(int mult[][10], int row1, int column2) {

    printf("\nOutput Matrix:\n");
    for (int i = 0; i < row1; ++i) {
        for (int j = 0; j < column2; ++j) {
            printf("%d  ", mult[i][j]);
            if (j == column2 - 1)
                printf("\n");
        }
    }
}
