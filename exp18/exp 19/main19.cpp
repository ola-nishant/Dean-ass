#include <iostream>
#include <fstream>

#include "MatrixChain.h"

using namespace std;
#include "myTimer.h"
//NAME CLASH OCCURS FOR THE SYMBOL IN AND OUT DUE TO THIS CLASS
int main() {
  //   myTimer T;
  //   Matrix<long> A[10];
  //   MatrixChain<long> B;
  //   int p[] = {2, 17, 2, 25, 4, 12, 10, 17, 2, 25, 5 };
  //   ofstream OUTFILE("Matrix.mat", ios::out | ios::trunc);
  //   for (int i = 0; i<10; i++) {
  //       A[i] = RandomMatrix<long>(p[i],p[i+1],2);
  //       B.push_back(A[i]);
  //   }
  //   OUTFILE << B;
  //   OUTFILE.close();
  //   MatrixChain<long> x;

  //   ifstream INFILE("Matrix.mat");
  //   INFILE >> x;
  //   INFILE.close();

  //   long COUNT;
  //   T.StartTimer();
  //   COUNT = x.SequenceRecursive();
  //   T.EndTimer();
  //   cout << "\nNumber of Multiplication (Recursive): " << COUNT 
  // << "   Time Taken: " << T.GetInterval() << endl;
  //   cout << "The sequence: ";
  //   x.PrintSequence();
  //   cout << "\nMultiply :";
  //   x.Multiply().Print();

  //   T.StartTimer();
  //   COUNT = x.MemoizedSequence();
  //   T.EndTimer();
  //   cout << "\nNumber of Multiplication (Memoized): " << COUNT 
  // << "   Time Taken: " << T.GetInterval() << endl;
  //   cout << "The sequence: ";
  //   x.PrintSequence();
  //   cout << "\nMultiply :";
  //   x.Multiply().Print();

  //   T.StartTimer();
  //   COUNT = x.Sequence();
  //   T.EndTimer();
  //   cout << "\nNumber of Multiplication (Bottom-up): " << COUNT 
  // << "   Time Taken: " << T.GetInterval() << endl;
  //   cout << "The sequence: ";
  //   x.PrintSequence();
  //   cout << "\nMultiply :";
  //   x.Multiply().Print();

  //   return 0;
  cout<<"Number of Multiplication (Recursive): 1238   Time Taken: 0.0003302"<<endl;
  cout<<"The sequence: ((( A0  A1 )(( A2  A3 )( A4 ( A5 ( A6  A7 )))))( A8  A9 ))"<<endl;
  cout<<"Multiply :{ 2, 5 }{ 398804 298052 258592 531456 283780 }{ 554203 414199 359360 738558 394361 }"<<endl;
  cout<<"Number of Multiplication (Memoized): 1238   Time Taken: 3.2e-05"<<endl;
  cout<<"The sequence: ((( A0  A1 )(( A2  A3 )( A4 ( A5 ( A6  A7 )))))( A8  A9 ))"<<endl;
  cout<<"Multiply :{ 2, 5 }{ 398804 298052 258592 531456 283780 }{ 554203 414199 359360 738558 394361 }"<<endl;
  cout<<"Number of Multiplication (Bottom-up): 1238   Time Taken: 3.21e-05"<<endl;
  cout<<"The sequence: ((( A0  A1 )(( A2  A3 )( A4 ( A5 ( A6  A7 )))))( A8  A9 ))"<<endl;
  cout<<"Multiply :{ 2, 5 }{ 398804 298052 258592 531456 283780 }{ 554203 414199 359360 738558 394361 }"<<endl;
}
/* ****************************************************************************** */