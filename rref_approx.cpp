/*
 * Method for Approximating the Reduced Row Echelon Form of an Augmented Matrix
 * Developed independently by Evan Perry Grove, 2017
 * 
 * I'm sure a plenty of CompSci people out there have already made algorithms
 * virtually identical to this one, and have probably made some that are far
 * more efficient, as well. This is purely for my own enrichment; if it
 * provides some value to someone out there, all the better.
 * 
 */

#include <iostream>
#include <iomanip>
using namespace std;
int main() 
{
    int mode = 0;
    cout << "\033[2J\033[1;1H";                             // clear the screen
    // is it necessary to keep turning ASCII colors on and off here? nah, not really.
    cout << "\033[1;34m****************************************\033[0m\n";
    cout << "\033[1;34m*                                      *\033[0m\n";
    cout << "\033[1;34m*  Reduced Row Echelon Form Algorithm  *\033[0m\n";
    cout << "\033[1;34m*        Evan Perry Grove   2017       *\033[0m\n";
    cout << "\033[1;34m*                                      *\033[0m\n";
    cout << "\033[1;34m****************************************\033[0m\n" << endl;
    cout << "\033[1;37mPlease select an option from below." << endl;
    cout << "0) Standard Mode: Output the REF and RREF matrices." << endl;
    cout << "1) Verbose Mode: Show human-friendly steps taken to reach REF and RREF." << endl;
    cout << "2) Extra Verbose Mode: Show the matrix after each step. (not recommended)" << endl;
    cin >> mode;
    
    if(mode > 3 || mode < 0)
    {
        cout << "Invalid mode specified. Default is Standard Mode (0)." << endl;
        mode = 0;
    }
    
    cout << "\033[1;37mHow many variables are we solving for? ";
    int n;
    cin >> n;                                               // initialize and set n
    double matrix[n][n + 1];                                // create the augmented matrix with n rows and n+1 columns
    
    // make each element 0,  for now.
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            matrix[i][j] = 0;                               // user inputs each element's value.
        }
    }
    
    // prompt the user for each element. This can be simplified massively, at the expense of having a not-so-pretty interface.
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            // clear screen and print out updated matrix each time we prompt for a new element.
            cout << "\033[2J\033[1;1H";
            cout << "\033[1;37mExcellent! Now to establish the values of each element." <<  endl;
            
            // these for loops can be copy-pasted anywhere in the program and they'll spit out the matrix.
            for (int idisp = 0; idisp < n; idisp++)
            {
                for (int jdisp = 0; jdisp <= n; jdisp++)
                {
                    
                    cout << setw(12) <<  matrix[idisp][jdisp];   //spit out elements of row i
                }
                cout << endl;                                    // go to next row and continue spitting out things
            }
        
            cout << endl <<   "Row " << i+1 << "   Column " << j+1 << "    Value: ";
            cin >> matrix[i][j];                                 // user inputs each element's value.
        }
    }
    
    // show what the user entered
    cout << "\033[2J\033[1;1H";
    cout << "\033[1;37mHere's your matrix:" << endl;
    // this is the same methodology we'll always use to spit out the matrix.
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            cout << setw(12) <<  matrix[i][j];          // spit out elements of row i
        }
        cout << endl;                                   // go to next row and continue spitting out things
    }
    
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

    // get the REF form of the matrix. c is used to represent the column of the element we are making zero
    for (int c = 0; c < n-1; c++)
    {
        //we're going to use elements M(1,1) M(2,2) etc as pivots. Make them all equal to 1 before moving things around
        for (int i = 0; i < n; i++)
        {
            //this algorithm works off of the assumption that M(c,c), M(i,i), or whatever else you want to call it,
            //is always equal to 1 when performing the row operations. Although it increases the number of calculations
            //we must perform, it means the row operation function can be brutally simple.
            double divisor = matrix[i][i];
            if (divisor != 0) {
                for (int j = 0; j <= n; j++)
                {
                    //in MATLAB terms: M(i,:) = M(i,:) / M(i,i)
                    //in English: divide every row i by its element in column i.
                    matrix[i][j] = matrix[i][j] / divisor;
                }
                if (divisor !=  1) 
                {
                    switch (mode)
                    {
                        case 0:
                            break;
                        case 1:
                            cout << "R" << i+1 << "<- R" << i+1 << " / " << divisor << endl;
                            break;
                        case 2:
                            cout << "R" << i+1 << "<- R" << i+1 << " / " << divisor << endl;
                            for (int idisp = 0; idisp < n; idisp++)
                                {
                                    for (int jdisp = 0; jdisp <= n; jdisp++)
                                    {
                                        cout << setw(12) <<  matrix[idisp][jdisp];   // spit out elements of row i
                                    }
                                    cout << endl;                                    // go to next row and continue spitting out things
                                }
                            break;
                    }
                }
            }
        }
        
        // subtract multiples of other rows to the row we're manipulating to get elements to zero
        for (int i = n-1; i > c; i--)
        {
            //here's how this works: we know from the for() loop above that any element M(c,c) is going to be 1. So,
            //we can say that by doing row operation M(i,:) = M(i,:)-M(c,:)*M(i,c), we will always get M(i,c)=0.
            double multiplier = matrix[i][c];
            for (int j = 0; j <= n; j++)
            {
                matrix[i][j] = matrix[i][j] - (matrix[c][j] * multiplier);
            }
            switch (mode)
            {
                case 0:
                    break;
                case 1:
                    cout << "R" << i+1 << "<- R" << i+1 << " - (R" << c+1 << " * " << multiplier << ")" << endl;
                    break;
                case 2:
                    cout << "R" << i+1 << "<- R" << i+1 << " - (R" << c+1 << " * " << multiplier << ")" << endl;
                    for (int idisp = 0; idisp < n; idisp++)
                    {
                        for (int jdisp = 0; jdisp <= n; jdisp++)
                        {
                            cout << setw(12) <<  matrix[idisp][jdisp];   // spit out elements of row i
                        }
                        cout << endl;                                    // go to next row and continue spitting out things
                    }
                    break;
            }
        }
            
    }
    
    //make sure the eventual pivots are 1 again. Works the same as earlier.
    for (int i = 0; i < n; i++)
    {
        double divisor = matrix[i][i];
        if (divisor != 0) {
            for (int j = 0; j <= n; j++)
            {
                matrix[i][j] = matrix[i][j] / divisor;
            }
            if (divisor !=  1) 
            {
                switch (mode)
                {
                    case 0:
                        break;
                    case 1:
                        cout << "R" << i+1 << "<- R" << i+1 << " / " << divisor << endl;
                        break;
                    case 2:
                        cout << "R" << i+1 << "<- R" << i+1 << " / " << divisor << endl;
                        for (int idisp = 0; idisp < n; idisp++)
                            {
                                for (int jdisp = 0; jdisp <= n; jdisp++)
                                {
                                    cout << setw(12) <<  matrix[idisp][jdisp];   // spit out elements of row i
                                }
                                cout << endl;                                    // go to next row and continue spitting out things
                            }
                        break;
                }
            }
        }
    }
    
    // display the REF form
    cout << "REF Form:" << endl;
    for (int idisp = 0; idisp < n; idisp++)
    {
        for (int jdisp = 0; jdisp <= n; jdisp++)
        {
            cout << setw(12) <<  matrix[idisp][jdisp];   // spit out elements of row i
        }
        cout << endl;                                    // go to next row and continue spitting out things
    }
    cout << endl << endl;   // throw some more lines in there
    
    // now for the RREF form.
    // everything here works exactly the same as the REF stuff. However, instead of starting at the bottom left of
    // the matrix, working upwards then to the right, we now work from the top right, work downwards then to the left.
    for (int c = n-1; c > 0; c--)
    {
        for (int i = 0; i < n; i++)
        {
            double divisor = matrix[i][i];
            if (divisor != 0) {
                for (int j = 0; j <= n; j++)
                {
                    matrix[i][j] = matrix[i][j] / divisor;
                }
                if (divisor !=  1) {
                    switch (mode)
                    {
                        case 0:
                            break;
                        case 1:
                            cout << "R" << i+1 << "<- R" << i+1 << " / " << divisor << endl;
                            break;
                        case 2:
                            cout << "R" << i+1 << "<- R" << i+1 << " / " << divisor << endl;
                            for (int idisp = 0; idisp < n; idisp++)
                            {
                                for (int jdisp = 0; jdisp <= n; jdisp++)
                                {
                                    cout << setw(12) <<  matrix[idisp][jdisp];   // spit out elements of row i
                                }
                                cout << endl;                                    // go to next row and continue spitting out things
                            }
                            break;
                    }
                }
            }
        }
        
        for (int i = 0; i < c; i++)
        {
            double multiplier = matrix[i][c];
            for (int j = 0; j <= n; j++)
            {
                matrix[i][j] = matrix[i][j] - (matrix[c][j] * multiplier);
            }
            switch (mode)
            {
                case 0:
                    break;
                case 1:
                    cout << "R" << i+1 << "<- R" << i+1 << " - (R" << c+1 << " * " << multiplier << ")" << endl;
                    break;
                case 2:
                    cout << "R" << i+1 << "<- R" << i+1 << " - (R" << c+1 << " * " << multiplier << ")" << endl;
                    for (int idisp = 0; idisp < n; idisp++)
                    {
                        for (int jdisp = 0; jdisp <= n; jdisp++)
                        {
                            cout << setw(12) <<  matrix[idisp][jdisp];   // spit out elements of row i
                        }
                        cout << endl;                                    // go to next row and continue spitting out things
                    }
                    break;
            }
        }
            
    }
    
    // make sure it's all ones, one more time
    for (int i = 0; i < n; i++)
    {
        double divisor = matrix[i][i];
        if (divisor !=  1) 
        {
            switch (mode)
            {
                case 0:
                    break;
                case 1:
                    cout << "R" << i+1 << "<- R" << i+1 << " / " << divisor << endl;
                    break;
                case 2:
                    cout << "R" << i+1 << "<- R" << i+1 << " / " << divisor << endl;
                    for (int idisp = 0; idisp < n; idisp++)
                    {
                        for (int jdisp = 0; jdisp <= n; jdisp++)
                        {
                            cout << setw(12) <<  matrix[idisp][jdisp];   // spit out elements of row i
                        }
                        cout << endl;                                    // go to next row and continue spitting out things
                    }
                    break;
            }
        }
    }
    
    // display the RREF form
    cout << "RREF Form:" << endl;
    for (int idisp = 0; idisp < n; idisp++)
    {
        for (int jdisp = 0; jdisp <= n; jdisp++)
        {
            
            cout << setw(12) <<  matrix[idisp][jdisp];   // spit out elements of row i
        }
        cout << endl;                                    // go to next row and continue spitting out things
    }
    
    cout << "\033[1;34m \033[0m\n";                      // make sure all the ASCII shenanigans are done before the program ends
    return 0;
}
