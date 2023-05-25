#include <iostream>
#include "myList.h"
using namespace std;

int main()
{
    myList<int> L;
    cout << L;
    L.addFront(1);
    L.addFront(2);
    L.addFront(3);
    L.addLast(4);
    L.addLast(5);
    cout << L;
    L.addAfter(5,6);
    cout << L;
    L.addAfter(10,6);
    cout << L;

    cout << "Value Removed = " << L.RemoveFirst()->Data << endl;
    cout << L;
    L.addFront(3);
    cout << L;
    cout << "Value Removed = " << L.RemoveLast()->Data << endl;
    cout << L;
    L.addLast(6);
    cout << L;
    myList<int> K(L);
    K.addLast(30);
    cout << "K = " << K;
    myList<int> R;
    R = K;
    cout << "R = " << R;
    myList<int> A;
    A = K + R;
    cout << "A = " << A;
    return 0;
}
