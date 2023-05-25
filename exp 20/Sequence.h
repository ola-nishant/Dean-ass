#ifndef SEQUENCE_H_INCLUDED
#define SEQUENCE_H_INCLUDED
#include <ostream>
#include <string>
#include <stack>
#include <vector>
// #include "Matrix.h"
// #include "myException.h"

#define MAX(a,b) ((a) > (b)) ? (a) : (b)

//Forward declarations
template <class T>
class Sequence;

template <class T>
class Sequence {
    T *D; //Data
    int S; //Size
    Matrix<long> C;
    /* ****************************************************************************** */
    /* A private function for allocation of memory                                    */
    /* ****************************************************************************** */
    void Allocate(int N) {
        D = new T[S=N];
        if (!D) throw myException("Sequence:Memory initialization failed\n");
    }

public:
    /* ****************************************************************************** */
    /* CONSTRUCTOR(S)                                                                 */
    /* ****************************************************************************** */

    Sequence<T>(){ D = NULL; S = 0;} //noninitialized array

    Sequence<T>(unsigned int Size) {
        if (Size <= 0) {D = NULL; S = 0; return;}
        Allocate(int(Size));
        for (int i = 0; i < S; i++) D[i] =T(0);
    }

    Sequence<T>(T *d, unsigned int Size) {
        if (Size <= 0) {D = NULL; S = 0; return;}
        Allocate(int(Size));
        for (int i = 0; i < S; i++) D[i] =d[i];
    }
    Sequence<T>(const Sequence<T>& A) {
        if (A.S <= 0) {D = NULL; S = 0; return;}
        Allocate(A.S);
        for (int i = 0; i < S; i++) D[i] =A.D[i];
    }

    /* ****************************************************************************** */
    /* DESTRUCTOR                                                                     */
    /* ****************************************************************************** */
    virtual ~Sequence(){ Clear(); }

    /* ****************************************************************************** */
    /* Auxiliary functions but useful                                                 */
    /* ****************************************************************************** */
    bool isEmpty() { return S == 0;} // If data exists false else true
    int Size() {return S;} // Number of data items put in array
    void Clear(){ delete [] D; S = 0; D = NULL;} // Truncates the array
    Matrix<long> getC() { return C;}
    /* ****************************************************************************** */
    /* OPERATOR OVERLOADING                                                           */
    /* ****************************************************************************** */
    T& operator[] (int i){ //Access by index (zero based)
        if (i > -1 && i < S) return D[i];
        throw myException("Sequence: Out of range access\n");
    }

    Sequence<T>& operator = (Sequence<T> x){ //asignment
        if (x.Size() < 0) throw myException("Sequence: Assigning non initialized array\n");
        Clear();
        if (x.Size() == 0) return *this;
        Allocate(x.S);
        for (int i = 0; i < S; i++) D[i] = x.D[i];
        return *this;
    }

    Sequence<T>& operator += (Sequence<T> x){//concatenation of a sequence
        Sequence<T> temp(S+x.S);
        for (int i = 0; i < S; i++) temp[i] = D[i];
        for (int i = 0; i < x.S; i++) temp[i+S] = x[i];
        *this = temp;
        return *this;
    }

    Sequence<T>& operator += (T x){//concatenation of one element
        Sequence<T> temp(S+1);
        for (int i = 0; i < S; i++) temp[i] = D[i];
        temp[S] = x;
        *this = temp;
        return *this;
    }

    Sequence<T> operator + (Sequence<T> x){//concatenation of a sequence
        Sequence<T> temp(*this);
        temp += x;
        return temp;
    }

    Sequence<T> operator + (T x){//concatenation of a sequence
        Sequence<T> temp(*this);
        temp += x;
        return temp;
    }

    bool operator == (Sequence<T> &x){//equality check
        if (S != x.S ) return false;
        for (int i = 0; i < S; i++) if (D[i] != x[i]) return false;
        return true;
    }

    
    /* ************************************************************* */
    /* RECURSIVE SUBSEQUENCE CHECK FUNCTION                          */
    /* ************************************************************* */
    bool subSequenceRecursive(Sequence<T> &Y){
        return checkSubSequenceRecursive(Y, Y.S - 1, S - 1);
    }

    // Return true if YES else false
    bool checkSubSequenceRecursive(Sequence<T> &Y, long m, long n){
        //YOUR CODE HERE

    }
    /* ************************************************************* */
    /* RECURSIVE SUBSEQUENCE CHECK FUNCTION END                      */
    /* ************************************************************* */
    /* ITERATIVE SUBSEQUENCE CHECK FUNCTION                          */
    /* ************************************************************* */
    // Return true if YES else false
    bool subSequenceCheck(Sequence<T> &Y){
        // YOUR CODE HERE
    }
    /* ************************************************************* */
    /* ITERATIVE SUBSEQUENCE CHECK FUNCTION ENDS                     */
    /* ************************************************************* */
    /* ************************************************************* */
    /* GENERATE SUBSEQUENCE                                          */
    /* ************************************************************* */
    std::vector<Sequence<T>> generateSubSequence(){
        std::vector<Sequence<T>> A;
        A.push_back(Sequence<T>());
        for (int i = 0; i < S; i++){
            size_t currSize = A.size();
            for (size_t j = 0; j < currSize; j++) {
                A.push_back(A[j]+D[i]);
            }
        }
        //If you want to remove the null subsequence uncomment the next line
        //A.erase(A.begin(),A.begin()+1);
        return A;
    }
    /* ************************************************************* */
    /* GENERATE SUBSEQUENCE END                                      */
    /* ************************************************************* */
    /* FIND LCS Recursive                                            */
    /* ************************************************************* */
    //m is size of x, and n is size of n
private:
    long recursiveLCS(size_t m, Sequence<T>& y, size_t n){
        // YOUR CODE HERE
    }
public:
    //returns the the longest subsequence
    Sequence<T> recursiveLCS(Sequence<T> x){
        C.Clear();
        C = Matrix<long>(S+1,x.S+1);
        for (size_t i = 1; i <= S; i++)
            for (size_t j = 1; j <= x.S; j++) C[i][j] = recursiveLCS(i, x, j);
        return getSubSequence(x);
    }
    /* ************************************************************* */
    /* FIND LCS Recursive ENDS                                       */
    /* ************************************************************* */
    
    /* ************************************************************* */
    /* FIND LCS Memoized                                       */
    /* ************************************************************* */
    //m is size of x, and n is size of n
private:
    long memoizedLCS(size_t m, Sequence<T>& y, size_t n){
        // YOUR CODE HERE
    }
public:
    //returns the longest subsequence
    Sequence<T> memoizedLCS(Sequence<T> x){
        C.Clear();
        C = Matrix<long>(S+1,x.S+1);
        for (size_t i = 0; i <= S; i++)
            for (size_t j = 0; j <= x.S; j++) C[i][j] = -1;
        for (size_t i = 0; i <= S; i++)
            for (size_t j = 0; j <= x.S; j++) C[i][j] = memoizedLCS(i,x,j);
        C[S][x.S]  = memoizedLCS(S, x, x.S);
        return getSubSequence(x);
    }
    /* ************************************************************* */
    /* FIND LCS Memoized  ENDS                                       */
    /* ************************************************************* */
    /* ************************************************************* */
    /* FIND LCS BOTTOM UP                                            */
    /* ************************************************************* */
    Sequence<T> LCS(Sequence<T> x){
        // YOUR CODE HERE
    }
    /* ************************************************************* */
    /* RETURN THE SUBSEQUENCE                                        */
    /* ************************************************************* */
    Sequence<T> getSubSequence(Sequence<T> &y) {
        // YOUR CODE HERE
    }
    //OUTPUT STREAM OVERLOAD. NOT A VERY TRICKY FUNCTION
    friend std::ostream& operator << (std::ostream& os, Sequence<T> x){
        if (x.Size() <= 0) return os << "{ Null }";
        for (int i = 0; i < x.Size() - 1; i++ ) os << x[i] << " ";
        return os << x[x.Size() - 1];
    }

    //OUTPUT in a slightly formatted manner
    void Print(std::ostream& os=std::cout ){
        if (Size() <= 0) {os << "{ Null }"; return;}
        os << "{ ";
        for (int i = 0; i < Size()-1; i++ ) os << D[i] << " ";
        os << D[Size() - 1] << " }";
    }

    // Read an array. The size of the array is fixed before reading
    friend std::istream& operator >> (std::istream& Input, Sequence<T>& x){
        int n=x.S;
        for (int i = 0; i< n; i++) Input >> x[i];
        return Input;
    }
};
#endif // SEQUENCE_H_INCLUDED
/* ******************************************************************************/
