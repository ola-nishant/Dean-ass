#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include "myTimer.h"
#include "myAuxFunctions.h"
#include "myRandom.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        cout << "Syntax:\n\tLAB001 <N><M><S>"
             << "\n\twhere N is an integer representing the number "
             << "\n\tof random numbers to be generated per file while"
             << "\n\tM is the number of files to be generated. "
             << "\n\n\tWhereas S is an optional parameter specifing "
             << "\n\tthe initial seed of the random number generator.\n\n";
        return 0;
    }
    // START MEASURING TIME FROM HERE
    myTimer T;
    T.StartTimer();
    //////////////////////////////////////////////////////////
    myRandom R;
    unsigned long N = StrToULong(argv[2]), M = StrToULong(argv[3]);
    if (argc == 4)
        R.setSeed(StrToULong(argv[3]));
    
    // print the commandline
    for (int i = 0; i < argc; i++)
        cout << argv[i] << "  ";
    cout << endl;

    string fileName;
    for (int i = 0; i < int(M); i++)
    {
        ostringstream strStream;
        strStream << "NUM-" << setw(2) << setfill('0') << to_string(i + 1)
                  << "-" << setw(6) << setfill('0') << to_string(N) << ".txt";
        fileName = strStream.str();
        // cout << fileName << endl;

        //storing files in subdirectory
        string filepath(__FILE__);
        size_t index = filepath.find_last_of("/\\");
        string directory = filepath.substr(0, index + 1);
        string subdirectory = "Files/";
        ofstream OUTFILE(directory + subdirectory + fileName, ios::out | ios::trunc);
        if (!OUTFILE)
        {
            cout << "Could not open file: " << fileName << endl;
            return 0;
        }
        for (int j = 0; j < N; j++)
        {
            OUTFILE << R.getVal() << endl;
        }
        OUTFILE.close();
    }
    ///////////////////////END THE TIME
    T.EndTimer();
    cout << "Average Time Taken: "
         << setw(20) << setprecision(10) << T.GetInterval() / M << " seconds" << endl;
    return 0;
}
