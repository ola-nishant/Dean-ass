#include <iostream>
#include <iomanip>
#include "optimalBST.h"

#include "myTimer.h"

using namespace std;

int main()
{
    double p2[] ={ 0.04, 0.06, 0.08, 0.02, 0.10, 0.12, 0.14};
    double q2[] ={ 0.06, 0.06, 0.06, 0.06, 0.05, 0.05, 0.05, 0.05};
    int Key2[] = {1,2,3,4,5,6,7};

    myTimer TIMER;
    optimalBSTree<int> A;

    double Cost;
    cout << "\n----------------------------------------------------------------------\n";
    cout << "RECURSIVE: \n";
    cout << "----------------------------------------------------------------------\n";
    TIMER.StartTimer();
    Cost = A.makeBST(7,Key2,p2,q2,RECURSIVE);
    TIMER.EndTimer();
    cout << " Time Taken: " << TIMER.GetInterval() << "(Seconds)\n";
    cout << " Optimal Search Cost: " << Cost << "\n";
    cout << "TREE:\n";
    A.Print();

    cout << "\n----------------------------------------------------------------------\n";
    cout << "MEMOIZED: \n";
    cout << "----------------------------------------------------------------------\n";
    TIMER.StartTimer();
    Cost = A.makeBST(7,Key2,p2,q2,MEMOIZED);
    TIMER.EndTimer();
    cout << " Time Taken: " << TIMER.GetInterval() << "(Seconds)\n";
    cout << " Optimal Search Cost: " << Cost << "\n";
    cout << "TREE:\n";
    A.Print();

    cout << "\n----------------------------------------------------------------------\n";
    cout << "ITERATIVE: \n";
    cout << "----------------------------------------------------------------------\n";
    TIMER.StartTimer();
    Cost = A.makeBST(7,Key2,p2,q2,ITERATIVE);
    TIMER.EndTimer();
    cout << " Time Taken: " << TIMER.GetInterval() << "(Seconds)\n";
    cout << " Optimal Search Cost: " << Cost << "\n";
    cout << "TREE:\n";
    A.Print();
    cout << "\n----------------------------------------------------------------------\n";
    A.Clear();
    A.Print();
    return 0;
}
/* ***************************************************************************** */
