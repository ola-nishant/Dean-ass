#include <iostream>
#include "myDSF.h"
using namespace std;

int main()
{
    Node<int> x;
    Node<int> y(1);
    cout << "1. X = " << x << " Y = " << y << endl;
    cout << "2. X == Y" << (x == y) << endl;
    cout << "-----------------\n";
    Node<char> a('A', 0);
    myDSF<char> z(BYRANK);
    z += a;
    cout << "3. Z = " << z << endl;
    a.idx = 1;
    a.Data = 'B';
    z += a;
    cout << "4. Z = " << z << endl;
    for (char i = 'C'; i <= 'H'; i++)
    {
        a.idx = (int)(i - 'A');
        a.Data = i;
        z += a;
    }
    cout << "5. Z = " << z << endl;
    z.Union('E', 'F'); // union 4 5
    cout << "6. Z = " << z << endl;
    z.Union('G', 'H'); // union 6 7
    cout << "7. Z = " << z << endl;
    z.Union('F', 'H'); // union 5 7
    cout << "8. Z = " << z << endl;

    cout << "9. Z = " << z[z.mySet('A')] << endl;
    cout << "----------\n";
    z.Union('Q', 'H');
    cout << "10. Z = " << z << endl;
    return 0;
}
