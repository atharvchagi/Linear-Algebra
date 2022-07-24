// Determinant calculator for 2x2 and 3x3 matrices (dynamic memory allocation)
#include "linalg.h"

// void getMatrix(double **matrix, int r, int c)
// {
//     for (int i = 0; i < r; ++i)
//     {
//         for (int j = 0; j < c; ++j)
//         {
//             cout << "Enter data for row #" << i + 1 << " column #" << j + 1 << ":";
//             cin >> matrix[i][j];
//         }
//     }
// }

// void displayPtrMatrix(double **matrix, int r, int c)
// {
//     for (int i = 0; i < r; ++i)
//     {
//         for (int j = 0; j < c; ++j)
//         {
//             cout << matrix[i][j] << "\t";
//         }
//         cout << endl;
//     }
// }

// double compute2x2det(double **m)
// {
//     return ((m[0][0] * m[1][1]) - (m[0][1] * m[1][0]));
// }

// double compute3x3det(double **m)
// {
//     double det = (m[0][0] * ((m[1][1] * m[2][2]) - (m[1][2] * m[2][1]))) + (m[0][1] * ((m[1][2] * m[2][0]) - (m[1][0] * m[2][2]))) + (m[0][2] * ((m[1][0] * m[2][1]) - (m[2][0] * m[1][1])));
//     return det;
// }

int main()
{
    int choice;
    cout << "Determinant Calculator - Atharv Chagi" << endl;
    line();
    cout << "Enter 0 for a 2x2 matrix or 1 for a 3x3 matrix: ";
    cin >> choice;
    line();
    if (choice == 0)
    {
        int row = 2;
        int col = 2;

        double **matrix = new double *[row];

        for (int i = 0; i < row; ++i)
        {
            matrix[i] = new double[col];
        }

        cout << "Enter data for the matrix:" << endl;
        getPtrMatrix(matrix, row, col);
        line();
        displayPtrMatrix(matrix, row, col);
        line();

        double det2x2 = compute2x2det(matrix);

        cout << "The determinant is " << det2x2 << ".";

        for (int i = 0; i < row; ++i)
        {
            delete[] matrix[i];
        }

        delete[] matrix;
    }

    if (choice == 1)
    {
        int row = 3;
        int col = 3;

        double **matrix = new double *[row];

        for (int i = 0; i < row; ++i)
        {
            matrix[i] = new double[col];
        }

        cout << "Enter data for the matrix:" << endl;
        getPtrMatrix(matrix, row, col);
        line();
        displayPtrMatrix(matrix, row, col);
        line();

        double det3x3 = compute3x3det(matrix);

        cout << "The determinant is " << det3x3 << ".";

        for (int i = 0; i < row; ++i)
        {
            delete[] matrix[i];
        }

        delete[] matrix;
    }
}
