/*
 * Method for finding the determinant of a matrix
 * Evan Perry Grove, 2017
 * 
 * uses recursive form of Laplace.
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

int minCt = 0;
int detCt = 0;

vector< vector<double> > getMinimo(vector< vector<double> > src, int ia, int ja, int ord)
{
    minCt++;
    vector< vector<double> > minimo(ord-1, vector<double> (ord-1,0));
    int row = 0;
    for (int i = 0; i < ord; i++)
    {
        int col = 0;
        if (i != ia)
        {
            for (int j = 0; j < ord; j++)
            {
                if (j != ja)
                {
                    minimo[row][col] = src[i][j];
                    col++;
                }
                
            }
            row++;
        }
    }
    return minimo;
}

double determinant(vector< vector<double> > src, int order)
{
    detCt++;
    if (order == 2)
    {
        double addPart = src[0][0] * src[1][1];
        double subPart = src[1][0] * src[0][1];
        return addPart - subPart;
    }
    else
    {
        double det = 0;
        for (int j = 0; j < order; j++)
        {
            vector< vector<double> > min = getMinimo(src, 0, j, order);
            if ((j % 2) == 0) 
            {
                det += src[0][j] * determinant(min, order-1);
            }
            else 
            { 
                det -= src[0][j] * determinant(min, order-1); 
            }
        }
        return det;
    }
}

void printMatrix ( vector< vector<double> > M) {
  //just does what it means
  int size = M.size();
  for( int i = 0; i < size; i++ ) {
    cout << "\t";
    for( int j = 0; j < size; j++ ) {
      cout << M[i][j] << "\t"; }
    cout << endl << endl << endl; }
  cout << endl;
}

void introduction()
{
    cout << "\033[2J\033[1;1H";                             // clear the screen
    cout << "\033[1;34m****************************************\033[0m\n";
    cout << "\033[1;34m*                                      *\033[0m\n";
    cout << "\033[1;34m*         Determinant Algorithm        *\033[0m\n";
    cout << "\033[1;34m*        Evan Perry Grove   2017       *\033[0m\n";
    cout << "\033[1;34m*                                      *\033[0m\n";
    cout << "\033[1;34m****************************************\033[0m\n" << endl;
}

int main() {
    introduction();
    cout << "\033[1;37mHow many variables are we solving for? ";
    int n;
    cin >> n;                                               // initialize and set n
    
    vector <vector<double> > matrix( n, vector<double> (n, 0));
    
    // prompt the user for each element. This can be simplified massively, at the expense of having a not-so-pretty interface.
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // clear screen and print out updated matrix each time we prompt for a new element.
            cout << "\033[2J\033[1;1H";
            cout << "\033[1;37mExcellent! Now to establish the values of each element." <<  endl;
            
            printMatrix(matrix);
            cout << endl <<   "Row " << i+1 << "   Column " << j+1 << "    Value: ";
            cin >> matrix[i][j];                                 // user inputs each element's value.
        }
    }
    
    
    
    // show what the user entered
    cout << "\033[2J\033[1;1H";
    cout << "\033[1;37mHere's your matrix:" << endl;

    printMatrix(matrix);
    
    // verify that the entered matrix is what the user wanted.
    char correct = 'n';
    double fix = 0;
    int fixrow = 1;
    int fixcol = 1;
    cout << endl << "\033[1;31mIs this correct? (y/n) \033[1;37m";
    cin >> correct;
    while (correct == 'n')
    {
        cout << endl << "\033[1;31mEnter a correction: \n"; 
        cout << "\033[1;37mrow:"; cin >> fixrow; cout << endl;
        cout << "\033[1;37mcol:"; cin >> fixcol; cout << endl;
        cout << "\033[1;37mfix:"; cin >> fix; cout << endl;
        matrix[fixrow - 1][fixcol - 1] = fix;
        cout << endl << "\033[1;31mIs this correct? (y/n) \033[1;37m";
        cin >> correct;
    }

    cout << "\nCalculating the determinant... this may take some time for larger matrices.\n";
    double det = determinant(matrix, n);
    cout << "The determinant is:  " << det << endl;
}