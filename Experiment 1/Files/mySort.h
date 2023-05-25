#ifndef __MYSORT__
#define __MYSORT__
void SwapUL(unsigned long *a, unsigned long *b);
unsigned long getMaxUL(unsigned long data[], long Size);
/* ********************************************************** */
/* Comparison based sorting                                   */
/* ********************************************************** */

// All functions return the number of comparisons
unsigned long InsertionSort(unsigned long data[], long Size)
{
    for (long i = 1; i < Size; i++)
    {
        unsigned long key = data[i];
        long j = i - 1;
        while (j >= 0 && data[j] > key)
        {
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = key;
    }
    return data[Size / 2]; // return the element at the middle index
};
unsigned long BubbleSort(unsigned long data[], long Size);
unsigned long SelectionSort(unsigned long data[], long Size);
unsigned long ShellSort(unsigned long data[], long Size);
void swap(unsigned long &a, unsigned long &b)
{
    unsigned long temp = a;
    a = b;
    b = temp;
}

unsigned long qsort(unsigned long data[], long low, long high, unsigned long cnt)
{
    
    if (low < high)
    {
        unsigned long pivot = data[high];
        long i = (low - 1);
    

        for (long j = low; j <= high - 1; j++)
        {
            if (data[j] <= pivot)
            {
                i++;
                cnt++;
                swap(data[i], data[j]);
            }
        }
        swap(data[i + 1], data[high]);

        qsort(data, low, i, cnt);
        qsort(data, i + 2, high, cnt);
    }
    return cnt;
}
unsigned long QuickSort(unsigned long data[], long Size)
{
    unsigned long cnt=0;
    cnt = qsort(data, 0, Size - 1, cnt);
    return cnt;
};
void heapify(unsigned long data[], long n, long i,unsigned long &cnt)
{
    long largest = i;
    long l = 2 * i + 1;
    long r = 2 * i + 2;

    if (l < n && data[l] > data[largest])
    {
        largest = l;
        cnt++;
    }

    if (r < n && data[r] > data[largest])
    {
        largest = r;
        cnt++;
    }

    if (largest != i)
    {
        std::swap(data[i], data[largest]);
        heapify(data, n, largest,cnt);
    }
}
unsigned long HeapSort(unsigned long data[], long Size)
{
    unsigned long cnt = 0;

    for (long i = Size / 2 - 1; i >= 0; i--)
        heapify(data, Size, i, cnt);

    for (long i = Size - 1; i >= 0; i--)
    {
        std::swap(data[0], data[i]);
        heapify(data, i, 0, cnt);
    }

    return cnt;
};
void merge(unsigned long data[], long l, long m, long r)
{
    long i, j, k;
    long n1 = m - l + 1;
    long n2 = r - m;
    unsigned long L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = data[l + i];
    for (j = 0; j < n2; j++)
        R[j] = data[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            data[k] = L[i];
            i++;
        }
        else
        {
            data[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        data[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        data[k] = R[j];
        j++;
        k++;
    }
}

void Mergesort(unsigned long data[], long l, long r)
{
    if (l < r)
    {
        long m = l + (r - l) / 2;

        Mergesort(data, l, m);
        Mergesort(data, m + 1, r);

        merge(data, l, m, r);
    }
}
unsigned long Mergesort(unsigned long data[], long Size)
{
    Mergesort(data, 0, Size - 1);
    return *data;
};
void swap(unsigned long *a, unsigned long *b)
{
    unsigned long t = *a;
    *a = *b;
    *b = t;
}

long partition(unsigned long data[], long low, long high)
{
    unsigned long pivot = data[high];
    long i = (low - 1);

    for (long j = low; j <= high - 1; j++)
    {
        if (data[j] <= pivot)
        {
            i++;
            swap(&data[i], &data[j]);
        }
    }
    swap(&data[i + 1], &data[high]);
    return (i + 1);
}

long randomPartition(unsigned long data[], long low, long high)
{
    srand(time(NULL));
    long random = low + rand() % (high - low);
    swap(&data[random], &data[high]);
    return partition(data, low, high);
}

void RandomizedQuickSort(unsigned long data[], long low, long high)
{
    if (low < high)
    {
        long pi = randomPartition(data, low, high);
        RandomizedQuickSort(data, low, pi - 1);
        RandomizedQuickSort(data, pi + 1, high);
    }
}
unsigned long RandomizedQuickSort(unsigned long data[], long Size)
{
    RandomizedQuickSort(data, 0, Size - 1);
    return *data;
};
/* ********************************************************** */
/* Non-Comparison based sorting                               */
/* ********************************************************** */
// Sorting in linear time
unsigned long CountingSort(unsigned long data[], long Size)
{
    // The size of count must be at least the (max+1) but
    // we cannot assign declare it as int count(max+1) in C++ as
    // it does not support dynamic memory allocation.
    // So, its size is provided statically.
    int output[10];
    int count[10];
    int max = data[0];

    // Find the largest element of the array
    for (int i = 1; i < Size; i++)
    {
        if (data[i] > max)
            max = data[i];
    }

    // Initialize count array with all zeros.
    for (int i = 0; i <= max; ++i)
    {
        count[i] = 0;
    }

    // Store the count of each element
    for (int i = 0; i < Size; i++)
    {
        count[data[i]]++;
    }

    // Store the cummulative count of each array
    for (int i = 1; i <= max; i++)
    {
        count[i] += count[i - 1];
    }

    // Find the index of each element of the original array in count array, and
    // place the elements in output array
    for (int i = Size - 1; i >= 0; i--)
    {
        output[count[data[i]] - 1] = data[i];
        count[data[i]]--;
    }

    // Copy the sorted elements into original array
    for (int i = 0; i < Size; i++)
    {
        data[i] = data[i];
    }
    return data[0];
}

// The algorithm copies the auxiliary memory into data,
// return is same as data (extra time taken to copy)

unsigned long RadixSort(unsigned long data[], long Size)
{
    // Find the maximum element in the input array
    unsigned long max_element = data[0];
    for (long i = 1; i < Size; ++i)
    {
        if (data[i] > max_element)
        {
            max_element = data[i];
        }
    }

    // Initialize the count and output arrays
    unsigned long *count = new unsigned long[256];
    unsigned long *output = new unsigned long[Size];

    // Perform counting sort on each digit, starting from the least significant
    for (unsigned long digit = 1; max_element / digit > 0; digit *= 256)
    {
        // Reset the count array
        for (unsigned long i = 0; i < 256; ++i)
        {
            count[i] = 0;
        }

        // Count the number of occurrences of each digit in the input array
        for (long i = 0; i < Size; ++i)
        {
            unsigned long digit_value = (data[i] / digit) % 256;
            ++count[digit_value];
        }

        // Compute the prefix sum of the count array
        for (unsigned long i = 1; i < 256; ++i)
        {
            count[i] += count[i - 1];
        }

        // Use the count array to place each element in its sorted position
        for (long i = Size - 1; i >= 0; --i)
        {
            unsigned long digit_value = (data[i] / digit) % 256;
            output[count[digit_value] - 1] = data[i];
            --count[digit_value];
        }

        // Copy the sorted output array back to the input array
        for (long i = 0; i < Size; ++i)
        {
            data[i] = output[i];
        }
    }

    // Find the median element in the sorted array
    unsigned long median = data[Size / 2];

    // Free memory used by count and output arrays
    delete[] count;
    delete[] output;

    return median;
};
// return is same as data (extra time taken to copy)

unsigned long BucketSort(double data[], long Size);
// sorted value returned in data. You may use the STL vector to implement
// Returns the number of comparisons. Buckets sorted using Insertion sort

// You may not implement the following (EXTRA002)
unsigned long BucketSort(unsigned long data[], long Size);
// sorted value returned in data. You may use the STL vector to implement
// Returns the number of comparisons. Buckets sorted using Insertion sort

#endif // __MYSORT__