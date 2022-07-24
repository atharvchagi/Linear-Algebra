#include <iostream>
#include <cmath>
#include <ctime>
using namespace std;

struct Vector
{
    double x;
    double y;
    double z;
};

void getVector(Vector &vector)
{
    cout << "Enter X Coordinate: ";
    cin >> vector.x;
    cout << "Enter Y Coordinate: ";
    cin >> vector.y;
    cout << "Enter Z Coordinate: ";
    cin >> vector.z;
}

void displayVector(Vector vector)
{
    cout << "[ " << vector.x << " ]" << endl
         << "| " << vector.y << " |" << endl
         << "[ " << vector.z << " ]" << endl;
}

void line()
{
    cout << "---------------------------------" << endl;
}

Vector crossProduct(Vector vec1, Vector vec2)
{
    Vector cross;
    cross.x = (vec1.y * vec2.z) - (vec2.y * vec1.z);
    cross.y = (vec2.x * vec1.z) - (vec1.x * vec2.z);
    cross.z = (vec1.x * vec2.y) - (vec2.x * vec1.y);
    return cross;
}

void getPtrMatrix(double **matrix, int r, int c)
{
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
            cout << "Enter data for row #" << i + 1 << " column #" << j + 1 << ":";
            cin >> matrix[i][j];
        }
    }
}

void displayPtrMatrix(double **matrix, int r, int c)
{
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

double compute2x2det(double **m)
{
    return ((m[0][0] * m[1][1]) - (m[0][1] * m[1][0]));
}

double compute3x3det(double **m)
{
    double det = (m[0][0] * ((m[1][1] * m[2][2]) - (m[1][2] * m[2][1]))) + (m[0][1] * ((m[1][2] * m[2][0]) - (m[1][0] * m[2][2]))) + (m[0][2] * ((m[1][0] * m[2][1]) - (m[2][0] * m[1][1])));
    return det;
}

double dotProduct(Vector vec1, Vector vec2)
{
    double dotP = (vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z);
    return dotP;
}

const int eRow = 2;
const int eCol = 2;

void getArrMatrix(double mat[][eCol])
{
    for (int i = 0; i < eRow; ++i)
    {
        for (int j = 0; j < eCol; ++j)
        {
            cout << "Row #" << i + 1 << " Column #" << j + 1 << ": ";
            cin >> mat[i][j];
        }
    }
}

void displayArrMatrix(double mat[][eCol])
{
    for (int i = 0; i < eRow; ++i)
    {
        cout << "[";
        for (int j = 0; j < eCol; ++j)
        {
            cout << mat[i][j];

            if (j != eCol - 1)
            {
                cout << "\t";
            }
        }
        cout << "]" << endl;
    }
}