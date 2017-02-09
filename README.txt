Gauss-Jordan and Recursive Laplace Methodologies
Evan Perry Grove, 2017

This repository contains some matrix algorithms. Everything here is in C++,
compiled using g++ on Kubuntu 16.04.

Contents:
./
    rref_approx.cpp   returns the row echelon form (REF) and the reduced
        row echelon Form (RREF) of an augmented matrix specified by user 
        inputs using Gauss-Jordan elimination. Also shows the exact steps it 
        took to reach the results.
        
    determinant.cpp   finds the determinant of the inputted matrix using a
        recursive form of the Laplace method. Uses a self-referencing command
        in order to recursively dissect any given matrix into smaller parts.
    
    
Known Issues:
    RESOLVED 2/5/2017: rref_approx.cpp: If any of the diagonal elements (1,1)
        thru (n-1,n-1) etc are equal to zero, the correct REF and RREF forms
        are not always returned.
        SOLUTION: Before going into the elimination algorithms, if a row has
            a zero where we don't want it to have a zero, switch that row with
            another one. Keep doing that until there's nonzeros wherever they
            are needed. Not a pretty solution, but programatically very simple.