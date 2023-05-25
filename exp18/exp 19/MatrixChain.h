#ifndef MATRIXCHAIN_H_INCLUDED
#define MATRIXCHAIN_H_INCLUDED

#include <limits>
#include "Matrix.h"
#include <vector>
#include<fstream>

template <class T>
class MatrixChain {
    std::vector<Matrix<T>> D; //The matrices
    myArray<int> p;           //The chain
    Matrix<int> s;            //The partition index holder matrix
    Matrix<long> m;           //The subchain cost matrix

public:
    //CONSTRUCTORS
    MatrixChain<T>() {}
    MatrixChain<T>(Matrix<T> &x) {
        D.push_back(x);
    }
    MatrixChain<T>(MatrixChain<T> &x) {
        if (x.empty()) {
            for (auto i : x) D.push_back(i);
        }
    }
    MatrixChain<T>& push_back(Matrix<T> &x){
        D.push_back(x);
        return *this;
    }

    //Auxiliary helpful functions
    myArray<int> get_p() { return p; }
    Matrix<int>  get_s() { return s; }
    Matrix<long> get_m() { return m; }

    //Chain Printing functions
    friend std::istream& operator >> (std::istream& Input, MatrixChain<T>& x){
        x.D.clear();
        Matrix<T> a;
        char c;
        while (1) {
            while (!Input.eof()) {
                Input.get(c);
                if (!isspace(c)) {
                    Input.putback(c);
                    break;
                }
            }
            if (Input.eof()) break;
            Input >> a;
            x.D.push_back(a);
        }
        return Input;
    }

    friend std::ostream& operator << (std::ostream& os, MatrixChain<T>& x){
        for (size_t i = 0; i< x.D.size(); i++) {
            os << x.D[i];
        }
        return os;
    }

    void Print(std::ostream& os=std::cout){
        for (size_t i = 0; i< D.size(); i++) {
            D[i].Print(os);
            os << std::endl;
        }
    }

    // If the matrices are compatible returns the array p or the size array.
    // else returns an empty myArray object;
    myArray<int> Compatible() {
         if (D.size() <= 1) {
        return myArray<int>();  // Return an empty myArray object if there is only one matrix
    }

    for (size_t i = 0; i < D.size() - 1; i++) {
        if (D[i].Cols() != D[i + 1].Rows()) {
            return myArray<int>();  // Return an empty myArray object if matrices are incompatible
        }
    }

    myArray<int> a(D.size() + 1);
    a[0] = D[0].Rows();
    for (size_t i = 0; i < D.size(); i++) {
        a[i + 1] = D[i].Cols();
    }
    return a;}

private:
    // This function implements the Matrix Chain Order Calculation in a pure recursive fashion
    // It returns the cost of multiplying I to j. This function is kept private
    long MatrixOrder(int i, int j, const myArray<int>& dimensions) {
     // Base case: If there is only one matrix, no multiplication is needed
    if (i == j)
        return 0;

    long minCost = std::numeric_limits<long>::max();
    int split = 0; // Variable to store the optimal split position

    // Iterate through all possible split positions to find the one with minimum cost
    for (int k = i; k < j; k++) {
        long cost = MatrixOrder(i, k, dimensions) + MatrixOrder(k + 1, j, dimensions)
            + dimensions[i - 1] * dimensions[k] * dimensions[j];

        if (cost < minCost) {
            minCost = cost;
            split = k;
        }
    }

    // Store the optimal split position in the s matrix
    s[i][j] = split;

    return minCost;
}

public:
    //Number of multiplications if it could find the sequence and -1 if the sequence is 
    // incompatible
    long SequenceRecursive() {
    p = Compatible();
    if (p.Size() <= 0)
        return -1;
    m.Clear();
    s.Clear();
    m = Matrix<long>(D.size(), D.size());
    s = Matrix<int>(D.size(), D.size());

    // Calculate the dimensions array
    myArray<int> dimensions = Compatible();

    return MatrixOrder(1, D.size(), dimensions);
}

private:
    // Number of multiplications if it could find the sequence and -1 if the sequence is 
    // incompatible
    long LookupChain(int i, int j){
	// YOUR IMPLEMENTATION HERE
      // YOUR IMPLEMENTATION HERE

        // Base case: If the subchain has already been calculated, return its cost
        if (m[i][j] < LONG_MAX)
            return m[i][j];

        // If there is only one matrix in the subchain, no multiplication is needed
        if (i == j) {
            m[i][j] = 0;
            return m[i][j];
        }

        long minCost = LONG_MAX;

        // Iterate through all possible split positions to find the one with minimum cost
        for (int k = i; k < j; k++) {
            long cost = LookupChain(i, k) + LookupChain(k + 1, j) + D[i].Rows() * D[k].Cols() * D[j].Cols();
            if (cost < minCost)
                minCost = cost;
        }

        m[i][j] = minCost;
        return m[i][j];
    }
public:
    // Number of multiplications if it could find the sequence and -1 if the sequence is 
    // incompatible 
    // Memoized Top-Down, this is the public interface to the algorithm
    long MemoizedSequence() {
        p = Compatible();
        if (p.Size() <= 0) return -1;
        m.Clear();
        s.Clear();
        m = Matrix<long>(D.size(), D.size());
        s = Matrix<int>(D.size(), D.size());

        for (int i = 0; i < m.Rows(); i++)
            for (int j = i; j < m.Cols(); j++) m[i][j] = LONG_MAX;
        return LookupChain(1,D.size());
    }

    // Number of multiplications if it could find the sequence and -1 if the sequence is 
    // incompatible
    // Bottom-up
    long Sequence() {
        // YOUR IMPLEMENTATION HERE
        // YOUR IMPLEMENTATION HERE

    int n = D.size();
    m = Matrix<long>(n, n);

    for (int i = 0; i < n; i++)
        m[i][i] = 0;

    for (int L = 2; L <= n; L++) {
        for (int i = 1; i <= n - L + 1; i++) {
            int j = i + L - 1;
            m[i][j] = LONG_MAX;
            for (int k = i; k <= j - 1; k++) {
                long cost = m[i][k] + m[k + 1][j] + D[i - 1].Rows() * D[k].Cols() * D[j - 1].Cols();
                if (cost < m[i][j])
                    m[i][j] = cost;
            }
        }
    }

    return m[1][n];

    }

private:
    //private function used to print the optimum sequence
  // Private function used to print the optimum sequence
void PrintSequenceOrder(int i, int j, std::ostream& os = std::cout) {
    if (i >= j) {
        os << "A" << i;
        return;
    }

    os << "(";
    PrintSequenceOrder(i, s[i][j], os);
    PrintSequenceOrder(s[i][j] + 1, j, os);
    os << ")";
}

public:
    //the public interface for printing the sequence
    void PrintSequence(std::ostream& os=std::cout){
        if (p.Size() <= 0) return;
        PrintSequenceOrder(0,p.Size()-2);
    }

private:
    Matrix<T> Multiply(int i, int j){
        if (i == j) return D[i];
        return Multiply(i,s[i][j]) * Multiply(s[i][j]+1,j);
    }
public:
    Matrix<T> Multiply(){
        if (p.Size() <= 0) return Matrix<T>();
        return Multiply(0,p.Size()-2);
    }
};

#endif //MATRIX_H_INCLUDED
/* ****************************************************************************** */