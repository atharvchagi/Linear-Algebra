#include "linalg.h"

int main()
{
    double mat[eRow][eCol];
    cout << "2x2 Eigenvalue Calculator - Atharv Chagi" << endl;
    cout << "Please enter the data for the 2x2 matrix." << endl;

    getArrMatrix(mat);

    double a = mat[0][0];
    double b = mat[0][1];
    double c = mat[1][0];
    double d = mat[1][1];

    line();
    displayArrMatrix(mat);
    line();

    double disc = pow((a + d), 2) - 4 * ((a * d) - (b * c));

    if (disc > 0)
    {
        double eigenvalue1 = (a + d)/2 + sqrt(disc) / 2;
        double eigenvalue2 = (a + d)/2 - disc / 2;

        cout << "The eigenvalues are " << eigenvalue2 << " and " << eigenvalue1 << "." << endl;
    }

    if (disc < 0)
    {
        disc *= -1;
        double eigenvalue1 = (a + d) + sqrt(disc) / 2;
        double eigenvalue2 = (a + d) - sqrt(disc) / 2;

        cout << "Complex Eigenvalues" << endl;
        cout << "The eigenvalues are " << (a + d) / 2 << " + " << sqrt(disc) / 2 << "i"
             << " and " << (a + d) / 2 << " - " << sqrt(disc) / 2 << "i." << endl;
    }
}
