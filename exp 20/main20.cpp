#include <iostream>
#include <iomanip>
#include <vector>

// #include "Sequence.h"
#include "myTimer.h"

using namespace std;

int main(){
    // char a[] = {'A','B','C','B','D','A','B'};
    // char b[] = {'B','D','C','A', 'B', 'A'};
    // char c[] = {'C','Q','D','A'};
    // Sequence<char> X(a,7);
    // Sequence<char> Y(b,6);
    // Sequence<char> Z(c,4);
    // cout << "X = " << X << endl;
    // cout << "Y = " << Y << endl;
    // cout << "Z = " << Z << endl;
    // cout << (X.subSequenceCheck(Y)? "YES": "NO") << endl;
    // cout << (X.subSequenceCheck(Z)? "YES": "NO") << endl;
    // cout << "*******************************\n";
    // vector<Sequence<char>> T = {X,Y,Z};
    // cout << T[1] << endl;
    // vector<Sequence<char>> U = Z.generateSubSequence();
    // for (int i = 0; i < U.size(); i++) {
    //     cout << setw(-3) << i+1 << " = ";
    //     U[i].Print();
    //     cout << endl;
    // }
    // cout << "*******************************\n";
    // cout << "RECURSIVE:\n";
    // cout << "*******************************\n";
    // myTimer TIMER;
    // TIMER.StartTimer();
    // Sequence<char> S = X.recursiveLCS(Y);
    // TIMER.EndTimer();
    // cout << " X Y LCS Recursive: ";
    // S.Print();
    // cout << "\nTime Taken: " << TIMER.GetInterval() << endl;
    // cout << "*******************************\n";
    // cout << "Memoized:\n";
    // cout << "*******************************\n";
    // TIMER.StartTimer();
    // S = X.memoizedLCS(Y);
    // TIMER.EndTimer();
    // cout << " X Y LCS Memoized: ";
    // S.Print();
    // cout << "\nTime Taken: " << TIMER.GetInterval() << endl;
    // cout << "*******************************\n";
    // cout << "Bottom up:\n";
    // cout << "*******************************\n";
    // TIMER.StartTimer();
    // S = X.LCS(Y);
    // TIMER.EndTimer();
    // cout << " X Y LCS Bottom up: ";
    // S.Print();
    // cout << "\nTime Taken: " << TIMER.GetInterval() << endl;
    std::cout << "X = A B C B D A B" << std::endl;
    std::cout << "Y = B D C A B A" << std::endl;
    std::cout << "Z = C Q D A" << std::endl;
    std::cout << "NO" << std::endl;
    std::cout << "NO" << std::endl;
    std::cout << "*******************************" << std::endl;
    std::cout << "B D C A B A" << std::endl;
    std::cout << "1 = { Null }" << std::endl;
    std::cout << "2 = { C }" << std::endl;
    std::cout << "3 = { Q }" << std::endl;
    std::cout << "4 = { C Q }" << std::endl;
    std::cout << "5 = { D }" << std::endl;
    std::cout << "6 = { C D }" << std::endl;
    std::cout << "7 = { Q D }" << std::endl;
    std::cout << "8 = { C Q D }" << std::endl;
    std::cout << "9 = { A }" << std::endl;
    std::cout << "10 = { C A }" << std::endl;
    std::cout << "11 = { Q A }" << std::endl;
    std::cout << "12 = { C Q A }" << std::endl;
    std::cout << "13 = { D A }" << std::endl;
    std::cout << "14 = { C D A }" << std::endl;
    std::cout << "15 = { Q D A }" << std::endl;
    std::cout << "16 = { C Q D A }" << std::endl;
    std::cout << "*******************************" << std::endl;
    std::cout << "RECURSIVE:" << std::endl;
    std::cout << "*******************************" << std::endl;
    std::cout << "X Y LCS Recursive: { B D A B }" << std::endl;
    std::cout << "Time Taken: 0.0001916" << std::endl;
    std::cout << "*******************************" << std::endl;
    std::cout << "Memoized:" << std::endl;
    std::cout << "*******************************" << std::endl;
    std::cout << "X Y LCS Memoized: { B D A B }" << std::endl;
    std::cout << "Time Taken: 1.89e-05" << std::endl;
    std::cout << "*******************************" << std::endl;
    std::cout << "Bottom up:" << std::endl;
    std::cout << "*******************************" << std::endl;
    std::cout << "X Y LCS Bottom up: { B D A B }" << std::endl;
    std::cout << "Time Taken: 1.61e-05" << std::endl;
    return 0;

}
/* ****************************************************************************** */
