#include <iostream>
#include <sstream>
#include <string>
#include "mySet.h"

using namespace std;

int main() {
    {
        mySet<int> L;
        cout << "1. L= " << L;
        L.addLast(1);
        cout << "2. L= " << L;

        L.addLast(2);
        L.addLast(3);
        L.addLast(4);
        L.addLast(5);
        cout << "3. L= " << L;
        //L.addLast(5);
        //cout << "4. L= " << L;
        //L += 5;
        //cout << "5. L= " << L;
        L+=6;
        cout << "6. L= " << L;
        mySet<int> R(-1);
        cout << "7. R=" << R;
        mySet<int> S(L);
        cout << "8. S=" << S;
        S -= 1;
        cout << "9. S=" << S;
        R -= S;
        cout << "10. L=" << R;
    }




/* ************************************ */
    {
        int a[] = {1,2,3,4}, b[] = {2,3,4,5};
        mySet<int> L(a,4),R(b,4);
        cout << "11. L=" << L;
        cout << "12. R=" << R;
        L *= R;
        cout << "13. L=" << L;
        mySet<int> S;
        S = L * R;
        cout << "14. S=" << S;
        cout << "15. S=" << S.Name() << endl;
        S -= 2;
        cout << "16. S=" << S;
        S += 2;
        cout << "17. S=" << S;
        cout << "18. S=" << S.Name()<<endl;
    }
    return 0;
}
