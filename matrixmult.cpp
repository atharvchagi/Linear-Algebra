//Matrix Multiplication calculator for up to 10x10 matrices
#include <iostream>
using namespace std;

const int row = 10;
const int col = 10;

void getData(int mat[][col], int r, int c)
{
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
            cout << "Row #" << i + 1 << " Column #" << j + 1 << ": ";
            cin >> mat[i][j];
        }
    }
}

void display(int mat[][col], int r, int c)
{
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
            cout << mat[i][j] << "\t";
        }
        cout << endl;
    }
}

void line()
{
    cout << "------------------------------------------------" << endl;
}

int main()
{
    int mat1[row][col];
    int mat2[row][col];
    int mat3[row][col];
    int r1, c1, r2, c2;

    cout << "Matrix Multiplication - Atharv Chagi";
    line();
Back:
    cout << "Enter number of rows for Matrix 1:  ";
    cin >> r1;

    cout << "Enter number of columns for Matrix 1: ";
    cin >> c1;

    cout << "Enter the number of rows for Matrix 2: ";
    cin >> r2;
    if (r2 != c1)
    {
        cout << "Matrices are not compatible, please try again." << endl;
        goto Back;
    }
    cout << "Etner the number of columns for Matrix 2: ";
    cin >> c2;

    line();

    cout << "Please enter the data for Matrix 1." << endl;
    cin.ignore();
    getData(mat1, r1, c1);

    line();
    display(mat1, r1, c1);
    line();

    cout << "Please enter the data for Matrix 2." << endl;
    cin.ignore();
    getData(mat2, r2, c2);

    line();
    display(mat2, r2, c2);
    line();

    for (int i = 0; i < r1; ++i)
    {
        for (int j = 0; j < c2; ++j)
        {
            mat3[i][j] = 0;
            for (int k = 0; k < r2; ++k)
            {
                mat3[i][j] += (mat1[i][k] * mat2[k][j]);
            }
        }
    }

    cout << "The product of the matrices is: " << endl;
    display(mat3, r1, c2);
}
