/*
 * Method for finding the determinant of a matrix
 * Evan Perry Grove, 2017
 * 
 * 
 */

#include <iostream>
#include <iomanip>
using namespace std;

double detTwo(int n, double matrix[n][n], int i, int j)  //return the determinant of a chunk of a larger matrix, starting at element i,j of that matrix. n specifies matrix size.
{
    return ((matrix[i][j] * matrix[i + 1][j + 1]-(matrix[i + 1][j] * matrix[i][j + 1]);
}

int main() {
    double matrix[2][2]
    for (int k = 0; k < 4; k++)
    {
        cin >> matrix [k]
    }
    detTwo(2, matrix, 0, 0);
}