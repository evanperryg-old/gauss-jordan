GAUSS-JORDAN ELIMINATION IN C++
Evan Perry Grove, 2017

This repository contains some matrix algorithms based on Gauss-Jordan. Everything here is in C++, compiled with g++ on Kubuntu 16.04.

Contents:
./
    rref_approx.cpp: returns the reduced echelon form (REF) and the reduced row echelon Form (RREF) of an augmented matrix specified by user inputs. Also shows the exact steps it took to reach the results.
    
    
Known Issues:
    rref_approx.cpp: If any of the elements (1,1) (2,2) etc are equal to zero, the correct REF and RREF forms are not returned.