#ifndef MYARRAY_H_INCLUDED
#define MYARRAY_H_INCLUDED
#include <ostream>
#include <string>
#include "myException.h"

/* ********************************************************************************** */
/* For proper usage these class typename T should be one of the numeric data types    */
/* Usage with other datatypes is fraught with inconvenience. For non-numeric datatype */
/* Use AT YOUR OWN RISK.                                                              */
/* ********************************************************************************** */

//Forward declarations
template <class T>
class myArray;

template <class T>
class myArray {
    T *D; //Data
    int S; //Size
    /* ****************************************************************************** */
    /* A private function for allocation of memory                                    */
    /* ****************************************************************************** */
    void Allocate(int N) {
        D = new T[S=N];
        if (!D) throw myException("myArray:Memory initialization failed\n");
    }

public:
    /* ****************************************************************************** */
    /* CONSTRUCTOR(S)                                                                 */
    /* ****************************************************************************** */

    myArray<T>(){ D = NULL; S = -1;} //noninitialized array

    myArray<T>(unsigned int Size) {
        Allocate(int(Size));
        for (int i = 0; i < S; i++) D[i] =T(0);
    }

    myArray<T>(T *d, unsigned int Size) {
        Allocate(int(Size));
        for (int i = 0; i < S; i++) D[i] =d[i];
    }

    myArray<T>(const myArray<T>& A) {
        Allocate(A.S);
        for (int i = 0; i < S; i++) D[i] =A.D[i];
    }

    /* ****************************************************************************** */
    /* DESTRUCTOR                                                                     */
    /* ****************************************************************************** */
    virtual ~myArray(){ Clear(); }

    /* ****************************************************************************** */
    /* Auxiliary functions but useful                                                 */
    /* ****************************************************************************** */
    bool isEmpty() { return S == -1;} // If data exists false else true
    int Size() {if (S < 0) return 0;  return S;} // Number of data items put in array
    void Clear(){ delete [] D; S = -1; D = NULL;} // Truncates the array

    /* ****************************************************************************** */
    /* OPERATOR OVERLOADING                                                           */
    /* ****************************************************************************** */
    T& operator[] (int i){ //Access by index (zero based)
        if (i > -1 && i < S) return D[i];
        throw myException("myArray: Out of range access\n");
    }

    myArray<T>& operator = (myArray<T> x){ //asignment
        if (x.Size() <= 0) throw myException("myArray: Assigning non initialized array\n");
        Clear();
        Allocate(x.S);
        for (int i = 0; i < S; i++) D[i] = x.D[i];
        return *this;
    }

    myArray<T>& operator - () { //unary -
        if (Size() <= 0) throw myException("myArray: negative of unassigned array\n");
        myArray<T> x(*this);
        for (int i = 0; i < S; i++) x[i] = -x[i];
        return x;
    }

    myArray<T>& operator + () {//unary +
        if (Size() <= 0) throw myException("myArray: negative of unassigned array\n");
        myArray<T> x(*this);
        return x;
    }

    myArray<T>& operator += (myArray<T> x){ //add + assignement
        if (x.Size() != Size()) throw myException("myArray +: Different sized array\n");
        for (int i = 0; i < x.Size(); i++) D[i] += x[i];
        return *this;
    }

    friend myArray<T> operator + (myArray<T> x, myArray<T> y){ //addition
        if (x.Size() != y.Size()) throw myException("myArray +: Different sized array\n");
        myArray<T> z(x.Size());
        for (int i = 0; i < x.Size(); i++) z[i] = x[i] + y[i];
        return z;
    }

    myArray<T>& operator -= (myArray<T> x){ //subtract and assign
        if (x.Size() != Size()) throw myException("myArray +: Different sized array\n");
        for (int i = 0; i < x.Size(); i++) D[i] -= x[i];
        return *this;
    }

    friend myArray<T> operator - (myArray<T> x, myArray<T> y){ //subtract
        if (x.Size() != y.Size()) throw myException("myArray +: Different sized array\n");
        myArray<T> z(x.Size());
        for (int i = 0; i < x.Size(); i++) z[i] = x[i] - y[i];
        return z;
    }

    friend T operator %  (myArray<T> x, myArray<T> y){ //dot product
        if (x.Size() != y.Size()) throw myException("myArray +: Different sized array\n");
        T z= T(0);
        for (int i = 0; i < x.Size(); i++) z += x[i] * y[i];
        return z;
    }

    friend myArray<T> operator * (myArray<T> a, T x){ //multiply by a constant
        if (a.Size() <= 0) throw myException("myArray: negative of unassigned array\n");
        myArray<T> y(a);
        for (int i = 0; i < y.Size(); i++) y[i] = a[i] * x;
        return y;
    }

    friend myArray<T> operator * (T x, myArray<T> a){ //multiply by a constant
        return a * x;
    }

    //OUTPUT STREAM OVERLOAD. NOT A VERY TRICKY FUNCTION
    friend std::ostream& operator << (std::ostream& os, myArray<T> x){
        if (x.Size() <= 0) return os << "{ Null }";
        for (int i = 0; i < x.Size() - 1; i++ ) os << x[i] << " ";
        return os << x[x.Size() - 1];
    }

    //OUTPUT in a slighly formatted manner
    void Print(std::ostream& os=std::cout ){
        if (Size() <= 0) {os << "{ Null }"; return;}
        os << "{ ";
        for (int i = 0; i < Size()-1; i++ ) os << D[i] << " ";
        os << D[Size() - 1] << " }";
    }

    // Read an array. The size of the array is fixed before reading
    friend std::istream& operator >> (std::istream& Input, myArray<T>& x){
        int n=x.S;
        for (int i = 0; i< n; i++) Input >> x[i];
        return Input;
    }

};

#endif // MYARRAY_H_INCLUDED