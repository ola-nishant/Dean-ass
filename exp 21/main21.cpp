#include <iostream>
#include "Tree.h"
using namespace std;

int main() {
    int n = 5;
    allBSTree x(n);
    cout << "No of BST:"<<x.numberBST() << endl;
    for (int i = 1; i <= x.C(n); i++) {
        cout << "*************************************************************************\n";
        cout << " i = " << i << endl;
        cout << "*************************************************************************\n";
        x.Print(i);
    }
    return 0;
}