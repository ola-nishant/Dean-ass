#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

#include "myTimer.h"

#include "myAuxFunctions.h"

#define NUMBER_OF_SIZES 14
#define NUMBER_OF_SAMPLES 30

using namespace std;

void Analyse(double timeTaken[NUMBER_OF_SIZES][NUMBER_OF_SAMPLES],
             unsigned long COUNT[NUMBER_OF_SIZES][NUMBER_OF_SAMPLES],
             double AvgTime[NUMBER_OF_SIZES],
             double AvgCount[NUMBER_OF_SIZES]);

void Analyse(double timeTaken[NUMBER_OF_SIZES][NUMBER_OF_SAMPLES], double AvgTime[NUMBER_OF_SIZES]);

int main()
{

    unsigned long N[] = {5, 10, 25, 50, 100, 250, 500, 1000, 2500, 5000, 10000, 25000, 50000, 100000};
    double timeTaken[NUMBER_OF_SIZES][NUMBER_OF_SAMPLES];
    unsigned long COUNT[NUMBER_OF_SIZES][NUMBER_OF_SAMPLES];
    string fileName;
    myTimer T;

    {
        // PART 1
        for (int j = 0; j < NUMBER_OF_SIZES; j++)
        {
            unsigned long Data[N[j]];
            for (int i = 0; i < NUMBER_OF_SAMPLES; i++)
            {
                ostringstream strStream;
                strStream << "NUM-" << setw(2) << setfill('0') << to_string(i + 1) << "-" << setw(6) << setfill('0') << to_string(N[j]) << ".txt";
                fileName = strStream.str();
                cout << fileName << endl;
                ifstream INFILE(fileName);
                if (!INFILE)
                {
                    cout << "Could not open file: " << fileName << endl;
                    return 0;
                }
                for (unsigned long k = 0; k < N[j]; k++)
                {
                    INFILE >> Data[k];
                }
                INFILE.close();
                T.StartTimer();
                Min<unsigned long>(Data, N[j]);
                T.EndTimer();
                timeTaken[j][i] = T.GetInterval();
            }
        }
        double AvgTime[NUMBER_OF_SIZES];
        Analyse(timeTaken, AvgTime);
        cout << setw(6) << "N"
             << "  " << setw(15) << "Average Time" << endl;
        for (int i = 0; i < NUMBER_OF_SIZES; i++)
        {
            cout << setw(6) << N[i] << "  " << setw(15) << AvgTime[i] << endl;
        }
        ofstream OUTFILE("OUTPUT_MIN.txt", ios::out | ios::trunc);
        if (!OUTFILE)
        {
            cout << "Could not open file: OUTPUT_MIN.txt" << endl;
            return 0;
        }

        OUTFILE << setw(6) << "N"
                << "  " << setw(15) << "Average Time" << endl;
        for (int i = 0; i < NUMBER_OF_SIZES; i++)
        {
            OUTFILE << setw(6) << N[i] << "  " << setw(15) << AvgTime[i] << endl;
        }
        OUTFILE.close();
    }

    {
        // PART 2
        for (int j = 0; j < NUMBER_OF_SIZES; j++)
        {
            unsigned long Data[N[j]];
            for (int i = 0; i < NUMBER_OF_SAMPLES; i++)
            {
                ostringstream strStream;
                strStream << "NUM-" << setw(2) << setfill('0') << to_string(i + 1) << "-" << setw(6) << setfill('0') << to_string(N[j]) << ".txt";
                fileName = strStream.str();
                cout << fileName << endl;
                ifstream INFILE(fileName);
                if (!INFILE)
                {
                    cout << "Could not open file: " << fileName << endl;
                    return 0;
                }
                for (unsigned long k = 0; k < N[j]; k++)
                {
                    INFILE >> Data[k];
                }
                INFILE.close();
                T.StartTimer();
                Max<unsigned long>(Data, N[j]);
                T.EndTimer();
                timeTaken[j][i] = T.GetInterval();
            }
        }
        double AvgTime[NUMBER_OF_SIZES];
        Analyse(timeTaken, AvgTime);
        cout << setw(6) << "N"
             << "  " << setw(15) << "Average Time" << endl;
        for (int i = 0; i < NUMBER_OF_SIZES; i++)
        {
            cout << setw(6) << N[i] << "  " << setw(15) << AvgTime[i] << endl;
        }
        ofstream OUTFILE("OUTPUT_MAX.txt", ios::out | ios::trunc);
        if (!OUTFILE)
        {
            cout << "Could not open file: OUTPUT_MAX.txt" << endl;
            return 0;
        }

        OUTFILE << setw(6) << "N"
                << "  " << setw(15) << "Average Time" << endl;
        for (int i = 0; i < NUMBER_OF_SIZES; i++)
        {
            OUTFILE << setw(6) << N[i] << "  " << setw(15) << AvgTime[i] << endl;
        }
        OUTFILE.close();
    }
    {
        // PART 3
        for (int j = 0; j < NUMBER_OF_SIZES; j++)
        {
            unsigned long Data[N[j]];
            for (int i = 0; i < NUMBER_OF_SAMPLES; i++)
            {
                ostringstream strStream;
                strStream << "NUM-" << setw(2) << setfill('0') << to_string(i + 1) << "-" << setw(6) << setfill('0') << to_string(N[j]) << ".txt";
                fileName = strStream.str();
                cout << fileName << endl;
                ifstream INFILE(fileName);
                if (!INFILE)
                {
                    cout << "Could not open file: " << fileName << endl;
                    return 0;
                }
                for (unsigned long k = 0; k < N[j]; k++)
                {
                    INFILE >> Data[k];
                }
                INFILE.close();
                T.StartTimer();
                COUNT[j][i] = 0;
                MinMax<unsigned long>(Data, N[j], &COUNT[j][i]);
                T.EndTimer();
                timeTaken[j][i] = T.GetInterval();
            }
        }
        double AvgTime[NUMBER_OF_SIZES], AvgCount[NUMBER_OF_SIZES];
        Analyse(timeTaken, COUNT, AvgTime, AvgCount);
        cout << setw(6) << "N"
             << "  " << setw(15) << "Average Time"
             << "  " << setw(15) << "Average Count" << endl;
        for (int i = 0; i < NUMBER_OF_SIZES; i++)
        {
            cout << setw(6) << N[i] << "  " << setw(15) << AvgTime[i] << "  " << setw(15) << AvgCount[i] << endl;
        }
        ofstream OUTFILE("OUTPUT_MINMAX.txt", ios::out | ios::trunc);
        if (!OUTFILE)
        {
            cout << "Could not open file: OUTPUT.txt" << endl;
            return 0;
        }

        OUTFILE << setw(6) << "N"
                << "  " << setw(15) << "Average Time"
                << "  " << setw(15) << "Average Count" << endl;
        for (int i = 0; i < NUMBER_OF_SIZES; i++)
        {
            OUTFILE << setw(6) << N[i] << "  " << setw(15) << AvgTime[i] << "  " << setw(15) << AvgCount[i] << endl;
        }
    }
    {
        // PART 4
        for (int j = 0; j < NUMBER_OF_SIZES; j++)
        {
            unsigned long Data[N[j]];
            for (int i = 0; i < NUMBER_OF_SAMPLES; i++)
            {
                ostringstream strStream;
                strStream << "NUM-" << setw(2) << setfill('0') << to_string(i + 1) << "-" << setw(6) << setfill('0') << to_string(N[j]) << ".txt";
                fileName = strStream.str();
                cout << fileName << endl;
                ifstream INFILE(fileName);
                if (!INFILE)
                {
                    cout << "Could not open file: " << fileName << endl;
                    return 0;
                }
                for (unsigned long k = 0; k < N[j]; k++)
                {
                    INFILE >> Data[k];
                }
                INFILE.close();
                T.StartTimer();
                COUNT[j][i] = 0;
                Select<unsigned long>(Data, 0, N[j] - 1, 2, &COUNT[j][i]);
                T.EndTimer();
                timeTaken[j][i] = T.GetInterval();
            }
        }
        double AvgTime[NUMBER_OF_SIZES], AvgCount[NUMBER_OF_SIZES];
        Analyse(timeTaken, COUNT, AvgTime, AvgCount);
        cout << setw(6) << "N"
             << "  " << setw(15) << "Average Time"
             << "  " << setw(15) << "Average Count" << endl;
        for (int i = 0; i < NUMBER_OF_SIZES; i++)
        {
            cout << setw(6) << N[i] << "  " << setw(15) << AvgTime[i] << "  " << setw(15) << AvgCount[i] << endl;
        }
        ofstream OUTFILE("OUTPUT_SELECT.txt", ios::out | ios::trunc);
        if (!OUTFILE)
        {
            cout << "Could not open file: OUTPUT.txt" << endl;
            return 0;
        }

        OUTFILE << setw(6) << "N"
                << "  " << setw(15) << "Average Time"
                << "  " << setw(15) << "Average Count" << endl;
        for (int i = 0; i < NUMBER_OF_SIZES; i++)
        {
            OUTFILE << setw(6) << N[i] << "  " << setw(15) << AvgTime[i] << "  " << setw(15) << AvgCount[i] << endl;
        }
    }
    return 0;
}

void Analyse(double timeTaken[NUMBER_OF_SIZES][NUMBER_OF_SAMPLES],
             unsigned long COUNT[NUMBER_OF_SIZES][NUMBER_OF_SAMPLES],
             double AvgTime[NUMBER_OF_SIZES],
             double AvgCount[NUMBER_OF_SIZES])
{
    for (int i = 0; i < NUMBER_OF_SIZES; i++)
    {
        AvgTime[i] = 0.0;
        AvgCount[i] = 0;
        for (int j = 0; j < NUMBER_OF_SAMPLES; j++)
        {
            AvgTime[i] += timeTaken[i][j];
            AvgCount[i] += COUNT[i][j];
        }
        AvgTime[i] /= double(NUMBER_OF_SAMPLES);
        AvgCount[i] /= double(NUMBER_OF_SAMPLES);
    }
}

void Analyse(double timeTaken[NUMBER_OF_SIZES][NUMBER_OF_SAMPLES], double AvgTime[NUMBER_OF_SIZES])
{
    for (int i = 0; i < NUMBER_OF_SIZES; i++)
    {
        AvgTime[i] = 0.0;
        for (int j = 0; j < NUMBER_OF_SAMPLES; j++)
        {
            AvgTime[i] += timeTaken[i][j];
        }
        AvgTime[i] /= double(NUMBER_OF_SAMPLES);
    }
}