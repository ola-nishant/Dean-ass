#include <iostream>
#include <fstream>

#include "MatrixChain.h"

using namespace std;
#include "myTimer.h"
//NAME CLASH OCCURS FOR THE SYMBOL IN AND OUT DUE TO THIS CLASS
int main() {
    myTimer T;
    Matrix<long> A[10];
    MatrixChain<long> B;
    int p[] = {2, 17, 2, 25, 4, 12, 10, 17, 2, 25, 5 };
    ofstream OUTFILE("Matrix.mat", ios::out | ios::trunc);
    for (int i = 0; i<10; i++) {
        A[i] = RandomMatrix<long>(p[i],p[i+1],2);
        B.push_back(A[i]);
    }
    OUTFILE << B;
    OUTFILE.close();
    MatrixChain<long> x;

    ifstream INFILE("Matrix.mat");
    INFILE >> x;
    INFILE.close();

    long COUNT;
    T.StartTimer();
    COUNT = x.SequenceRecursive();
    T.EndTimer();
    cout << "\nNumber of Multiplication (Recursive): " << COUNT 
  << "   Time Taken: " << T.GetInterval() << endl;
    cout << "The sequence: ";
    x.PrintSequence();
    cout << "\nMultiply :";
    x.Multiply().Print();

    T.StartTimer();
    COUNT = x.MemoizedSequence();
    T.EndTimer();
    cout << "\nNumber of Multiplication (Memoized): " << COUNT 
  << "   Time Taken: " << T.GetInterval() << endl;
    cout << "The sequence: ";
    x.PrintSequence();
    cout << "\nMultiply :";
    x.Multiply().Print();

    T.StartTimer();
    COUNT = x.Sequence();
    T.EndTimer();
    cout << "\nNumber of Multiplication (Bottom-up): " << COUNT 
  << "   Time Taken: " << T.GetInterval() << endl;
    cout << "The sequence: ";
    x.PrintSequence();
    cout << "\nMultiply :";
    x.Multiply().Print();

    return 0;
}
/* ****************************************************************************** */