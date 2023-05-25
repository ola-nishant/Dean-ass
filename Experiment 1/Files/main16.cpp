#include <iostream>
#include <sstream>
#include <string>
#include "myDisjointSet.h"

using namespace std;

int main() {
    char a[] = {'A', 'B', 'C', 'D'};
    myDS<char> L;
    cout << "1. L= " << L << endl;
    L += 'U';
    cout << "2. L= " << L << endl;
    L += 'V';
    L += 'W';
    cout << "3. L= " << L << endl;

    L += 'X';
    cout << "4. L= " << L << endl;

    myDS<char> R(a,4);
    cout << "5. R= " << R << endl;
    myDS<char> A;
    cout << "6. A= " << (A = R+L) << endl;
    cout << "7. 'a' in Set: " << A.Contains('a') << endl;
    cout << "8. 'A' in Set: " << A.Contains('A') << endl;
    return 0;
}
