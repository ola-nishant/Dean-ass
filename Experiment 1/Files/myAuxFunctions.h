#ifndef MYAUXFUNCTIONS_H_INCLUDED
#define MYAUXFUNCTIONS_H_INCLUDED
#include "myRandom.h"

#include <cstdlib>
#include <iostream>
using namespace std;

// Str to unsigned long
unsigned long StrToULong(char *x)
{
    unsigned long val = 0;
    unsigned int i = 0;
    while (x[i] != '\0')
    {
        val = val * 10 + (x[i++] - '0');
    }
    return val;
}

// Swap function
template <typename T>
void Swap(T &x, T &y);

template <typename T>
void Swap(T *x, T *y);

template <typename T>
T Min(T A[], long Size)
{
    // Initialize the minimum value to the first element in the array
    T min_value = A[0];

    // Iterate through the array and update the minimum value as necessary
    for (long i = 1; i < Size; ++i)
    {
        if (A[i] < min_value)
        {
            min_value = A[i];
        }
    }

    // Return the minimum value
    return min_value;
};

template <typename T>
T Max(T A[], long Size)
{
    // Initialize the maximum value to the first element in the array
    T max_value = A[0];

    // Iterate through the array and update the maximum value as necessary
    for (long i = 1; i < Size; ++i)
    {
        if (A[i] > max_value)
        {
            max_value = A[i];
        }
    }

    // Return the maximum value
    return max_value;
};

template <class T>
class Pair
{
private:
    T x;
    T y;

public:
    Pair() { x = y = 0; };
    Pair(T f, T s) : x(f), y(s) {};
    Pair(Pair<T> &);
    T &getX();
    T &getY();
    Pair<T> &operator=(Pair<T> b);

    friend ostream &operator<<(ostream &os, const Pair<T> &x)
    {
        return os << "( " << x.x << ", " << x.y << " )";
    }
};

template <typename T>
Pair<T> MinMax(T A[], long Size, unsigned long *COUNT = NULL)
{
    T min_value = A[0];
    T max_value = A[0];

    unsigned long comparisons = 0;

    for (long i = 1; i < Size; ++i)
    {
        T current_x = A[i];
        T current_y = A[i];

        ++comparisons;
        if (current_x < min_value)
        {
            min_value = current_x;
        }
        if (current_y < min_value)
        {
            min_value = current_y;
        }

        ++comparisons;
        if (current_x > max_value)
        {
            max_value = current_x;
        }
        if (current_y > max_value)
        {
            max_value = current_y;
        }
    }

    if (COUNT != NULL)
    {
        *COUNT = comparisons;
    }

    Pair<T> result(min_value, max_value);

    return result;
};

template <typename T>
long Partition(T d[], long low, long high, unsigned long *COUNT = NULL);

template <typename T>
long randomPartition(T d[], long low, long high, unsigned long *COUNT = NULL);

template <typename T>
T* Select(T d[], long left, long right, long k, unsigned long *COUNT = NULL)
{
    // Use counting sort to find the k-th smallest element
    long n = right - left + 1;
    long unsigned int max_val = Max(d + left, n);
    long unsigned int min_val = Min(d + left, n);
    unsigned long range = max_val - min_val + 1;
    unsigned long *C = new unsigned long[range]();
    for (long i = left; i <= right; i++)
    {
        C[d[i] - min_val]++;
        if (COUNT)
            (*COUNT)++;
    }
    for (unsigned long i = 1; i < range; i++)
    {
        C[i] += C[i - 1];
    }
    T *B = new T[n]();
    for (long i = right; i >= left; i--)
    {
        B[--C[d[i] - min_val]] = d[i];
        if (COUNT)
            (*COUNT)++;
    }
    T kth_smallest = B[k - 1];
    delete[] C;
    delete[] B;
    T *result = new T;
    *result = kth_smallest;
    return result;
};
#endif // MYAUXFUNCTIONS_H_INCLUDED
