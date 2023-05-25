#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED
#include "myException.h"
#include "myRandom.h"
#include "myArray.h"
// Implementing a 2D array as an array of arrays
// Try implement them as a linear array, keep track of indices

// Note:
//      A matrix has M rows and N Columns
//      For purpose of entry and output, by overloading the sequence of printing shall
//      ROW(M) COLS(N) A11 A12 A13 ... A1N A21 A22 A23 ... A2N ... AM1 AM2 AM3 ... AMN
//      For pretty printing Print method is provided
template <class T>
class Matrix{
    myArray<T> *D; //Data
    int M,N; //Size
    /* ****************************************************************************** */
    /* A private function for allocation of memory                                    */
    /* ****************************************************************************** */
    void Allocate(int m, int n) {
        M = m;
        N = n;
        D = new myArray<T>[M];
        for (int i = 0; i < M; i++) D[i] = myArray<T>(N);
        // if (!D) throw myException("Matrix:Memory initialization failed\n");
    }

public:
    /* ****************************************************************************** */
    /* CONSTRUCTOR(S)                                                                 */
    /* ****************************************************************************** */

    Matrix<T>(){ D = NULL; M = -1;} //noninitialized array

    Matrix<T>(unsigned int m, unsigned n){ Allocate(int(m),int(n)); }

    Matrix<T>(T *d,unsigned int m, unsigned n):M(m), N(n) {
        Allocate(int(m),int(n));
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                D[i][j] = *((d+i*n) + j);
    }

    Matrix<T>(const Matrix<T>& A) {
        D = new myArray<T>[M = A.M];
        N = A.N;
        if (!D) throw std::out_of_range("Matrix: Memory initialization failed\n");
        for (int i = 0; i < M; i++) D[i] = A.D[i];
    }

    /* ****************************************************************************** */
    /* DESTRUCTOR                                                                     */
    /* ****************************************************************************** */
    ~Matrix(){ Clear(); }

    /* ****************************************************************************** */
    /* Auxiliary functions but useful                                                 */
    /* ****************************************************************************** */
    bool isEmpty() { return M == -1;}
    int Rows() {if (M < 0) return 0; return M;}
    int Cols() {if (M < 0) return 0; return D[0].Size();}
    void Clear(){ delete [] D; M = -1; D = NULL;}

    /* ****************************************************************************** */
    /* OPERATOR OVERLOADING                                                           */
    /* ****************************************************************************** */
    myArray<T>& operator[] (int i){ //Access by index
        if (i > -1 && i < M) return D[i];
        throw std::out_of_range("Matrix: Out of range access\n");
    }

    friend std::ostream& operator << (std::ostream& os, Matrix<T> x) { // OUTPUT, not very well formatted
        if (x.M<0) return os << "0 0";
        else os << x.M << " " << x.N << " ";
        for (int i = 0; i < x.M ; i++) os << x.D[i] << " ";
        return os;// << x.D[x.M - 1];
    }

    void Print(std::ostream& os=std::cout) { // OUTPUT, slightly formatted
        if (M<0) {os << "{ NULL }"; return;}
        else os << "{ " << M << ", " << N << " }";
        for (int i = 0; i < M; i++) D[i].Print(os);
    }

    Matrix<T>& operator = (Matrix<T> x){ //asignment
        if (x.M <= 0 || x.N <= 0) throw std::out_of_range("Matrix 01: Assigning non initialized matrix\n");
        Clear();
        Allocate(x.M,x.N);
        for (int i = 0; i < M; i++) D[i] = x.D[i];
        return *this;
    }

    Matrix<T>& operator - () { //unary -
        if (M <= 0 || N <= 0) throw std::out_of_range("Matrix 02: non initialized matrix\n");
        Matrix<T> x(*this);
        for (int i = 0; i < M; i++) x.D[i] = -D[i];
        return x;
    }

    Matrix<T>& operator + () {//unary +
        if (M <= 0 || N <= 0) throw std::out_of_range("Matrix 03: non initialized matrix\n");
        myArray<T> x(*this);
        return x;
    }

    Matrix<T>& operator += (Matrix<T> x){ //add + assignment
        if (x.M !=M || x.N != N) throw std::out_of_range("Matrix 04: Adding incompatible matrix\n");
        for (int i = 0; i < x.M; i++) D[i] += x[i];
        return *this;
    }

    friend Matrix<T> operator + (Matrix<T> x, Matrix<T> y){ //addition
        if (x.M !=y.M || x.N != y.N) throw std::out_of_range("Matrix 05: Adding incompatible matrix\n");
        Matrix<T> z(x);
        for (int i = 0; i < x.M; i++) z.D[i] = x.D[i] + y.D[i];
        return z;
    }

    Matrix<T>& operator -= (Matrix<T> x){ //subtract and assign
        if (x.M !=M || x.N != N) throw std::out_of_range("Matrix 06: Subtracting incompatible matrix\n");
        for (int i = 0; i < x.M; i++) D[i] -= x.D[i];
        return *this;
    }

    friend Matrix<T> operator - (Matrix<T> x, Matrix<T> y){ //subtract
        if (x.M !=y.M || x.N != y.N) throw std::out_of_range("Matrix 07: Subtracting incompatible matrix\n");
        Matrix<T> z(x);
        for (int i = 0; i < x.M; i++) z.D[i] = x.D[i] - y.D[i];
        return z;
    }

    friend Matrix<T> operator % (Matrix<T> x, Matrix<T> y){ //Term * Term multiplication
        if (x.M !=y.M || x.N != y.N) throw std::out_of_range("Matrix 08: Incompatible matrix\n");
        Matrix<T> z(x);
        for (int i = 0; i < x.M; i++)
            for (int j = 0; j < x.N; j++)
                z[i][j] = x[i][j] * y[i][j];
        return z;
    }

    friend Matrix<T> operator * (Matrix<T> a, T x){ //multiply by a scaler
        if (a.M <= 0 || a.N <= 0) throw std::out_of_range("Matrix 09: non initialized matrix\n");
        Matrix<T> y(a);
        for (int i = 0; i < y.M; i++) y.D[i] = a.D[i] * x;
        return y;
    }

    friend Matrix<T> operator * (T x, Matrix<T> a){ //multiply by a scaler
        return a * x;
    }

    friend Matrix<T> operator * (Matrix<T> a, Matrix<T> b){//multiply
        if (a.N != b.M ) throw std::out_of_range("Matrix 11: Incompatible matrix\n");
        Matrix<T> y(a.M,b.N);
        for (int i = 0; i < y.M; i++)
            for (int j = 0; j < y.N; j++)
                for (int k = 0; k < a.N; k++) y[i][j] += a[i][k] * b[k][j];
        return y;
    }

    Matrix<T>& operator *= (Matrix<T> b){//multiply and assign
        if (N != b.M ) throw std::out_of_range("Matrix 10: Incompatible matrix\n");
        Matrix<T> y(M,b.N);
        for (int i = 0; i < y.M; i++)
            for (int j = 0; j < y.N; j++)
                for (int k = 0; k < N; k++) y[i][j] += D[i][k] * b[k][j];
        *this = y;
        return *this;
    }

    Matrix<T> operator ~ (){//Transpose
        if (M <= 0 || N <= 0) return Matrix<T>();
        Matrix<T> y(N,M);
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++) y[j][i] += D[i][j];
        return y;
    }

    friend std::istream& operator >> (std::istream& Input, Matrix<T>& x){ //read a matrix, first 2 elements are the size parameters ROWS COLS
        x.Clear();
        int m,n;
        Input >> m >> n;
        x.Allocate(m,n);
        for (int i = 0; i< m; i++) Input >> x[i];
        return Input;
    }
};

/* **************************************************************************************** */
/* A SIMPLE FUNCTIONS TO SHOWCASE SOME USAGE                                                */
/* **************************************************************************************** */
#include <type_traits>
myRandom R;
template <typename T>
Matrix<T> RandomMatrix(const int M, const int N, long MAX = 0){
    Matrix<T> x(M,N);
    unsigned long V;
    for (int i = 0; i < M; i++){
        for (int j = 0; j < N; j++) {
            V = R.getVal();
            if (std::is_same<T,double>::value || std::is_same<T,float>::value) x[i][j] = (V / double(4294967295LL));
            else if (std::is_same<T,int>::value) x[i][j] = V - long(V/INT_MAX)*INT_MAX;
            else if (std::is_same<T,long>::value) x[i][j] = V - long(V/LONG_MAX)*LONG_MAX;
            if (MAX) {
                if (std::is_same<T,double>::value || std::is_same<T,float>::value) x[i][j] *= MAX;
                else x[i][j] -= long(x[i][j]/MAX)*MAX;
            }
        }
    }
    return x;
}
#endif // MATRIX_H_INCLUDED/* 