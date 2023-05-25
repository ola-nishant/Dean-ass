#include <iostream>
#include <fstream>
#include "Matrix.h"

using namespace std;

int main() {
    //Creates a set of matrices
    Matrix<int> A, B, C;
    Matrix<long> D, E, F;
    Matrix<double> G, H, I;

    //INITIALIZE BY INVOKING RANDOMMATRIX
    A = RandomMatrix<int>(3,3,2);
    B = RandomMatrix<int>(3,3,5);
    C = RandomMatrix<int>(3,3,10);

    D = RandomMatrix<long>(3,3,4);
    E = RandomMatrix<long>(3,3,6);
    F = RandomMatrix<long>(3,3,8);

    G = RandomMatrix<double>(3,3,4);
    H = RandomMatrix<double>(3,3,1);
    I = RandomMatrix<double>(3,3,2);

    //PRINT THEM OUT
    cout << "A = "; A.Print(); cout << endl;
    cout << "B = "; B.Print(); cout << endl;
    cout << "C = "; C.Print(); cout << endl;

    //PRINT THEM OUT
    cout << "D = "; F.Print(); cout << endl;
    cout << "E = "; E.Print(); cout << endl;
    cout << "F = "; D.Print(); cout << endl;

    //PRINT THEM OUT
    cout << "G = "; G.Print(); cout << endl;
    cout << "H = "; H.Print(); cout << endl;
    cout << "I = "; I.Print(); cout << endl;

    //OPERATIONS ON SAME TYPE
    //PRINT THEM OUT
    cout << "A + B = "; (A+B).Print(); cout << endl;
    cout << "A - B = "; (A-B).Print(); cout << endl;
    cout << "A * B = "; (A*B).Print(); cout << endl;

    //PRINT THEM OUT
    cout << "D + F = "; (D+F).Print(); cout << endl;
    cout << "D - F = "; (D-F).Print(); cout << endl;
    cout << "D * F = "; (D*F).Print(); cout << endl;

    //PRINT THEM OUT
    cout << "G + H = "; (G+H).Print(); cout << endl;
    cout << "G - H = "; (G-H).Print(); cout << endl;
    cout << "G * H = "; (G*H).Print(); cout << endl;

    //OPERATIONS ON DIFFERENT TYPE
    //WILL NOT WORK: CAN YOU MAKE IT WORK

    //cout << "A + D = "; (A+D).Print(); cout << endl;
    //cout << "A - G = "; (A-G).Print(); cout << endl;
    //cout << "D * G = "; (D*G).Print(); cout << endl;

    return 0;
}
/* ****************************************************************************** */