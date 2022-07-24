// Dot product calculator for 2 vectors
#include "linalg.h"

int main()
{
    Vector vector1;
    Vector vector2;

    cout << "Vector Dot Product Calculator - Atharv Chagi" << endl;
    line();

    cout << "Enter the coordinates for Vector 1" << endl;
    getVector(vector1);
    line();
    displayVector(vector1);
    line();

    cout << "Enter the coordnates for Vector 2" << endl;
    getVector(vector2);
    line();
    displayVector(vector2);
    line();

    double dotP = dotProduct(vector1, vector2);

    cout << "The Dot Product of these vectors is " << dotP << ".";
}