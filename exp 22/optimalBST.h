#ifndef OPTIMALBST_H_INCLUDED
#define OPTIMALBST_H_INCLUDED
#include <cmath>
#include <iostream>
#include<iomanip>
#include <ostream>
#include <vector>
#include <limits>
#include "myException.h"

#define MAX(a,b) ((a) > (b)) ? (a) : (b)

//T must be a comparable data type

template <class T>
class Node{
    T V;// Key
    int IDX; //The index of the key
    double prob; //associated key probability (NOT A NECESSARY ITEM)
    Node *L; //LEFT CHILD POINTER
    Node *R; //RIGHT CHILD POINTER

public:
    Node<T>(): L(nullptr), R(nullptr), IDX(-1) {}
    Node<T>(T x): V(x), L(nullptr), R(nullptr), IDX(-1) {}
    //Node<T>(T x, Node *left, Node *right): V(x), L(left), R(right) {}
    Node<T>(Node<T> &x): V(x.V), L(x.L), R(x.R), IDX(x.IDX){}
    virtual ~Node<T>() { }
    Node<T>& operator = (Node<T> x) {
        V = x.V;
        L = x.L;
        R = x.R;
        IDX = x.IDX;
        return *this;
    }

    friend std::ostream& operator << (std::ostream& os, Node x) {
        return os << x.V;
    }

    T& Value() { return V;}
    int& Index() { return IDX;}
    double& Probability() { return prob;}
    Node<T>** Left() { return &L;}
    Node<T>** Right() { return &R;}


};

typedef enum{RECURSIVE, MEMOIZED, ITERATIVE} bst_mode;

/* ***************************************************************************** */
/* Assumptions:                                                                  */
/*    1. KEYS ARE ASSUMED TO BE SORTED IN ASCENDING ORDER                        */
/* ***************************************************************************** */
template <class T>
class optimalBSTree{
    /* ************************************************************************* */
    /* PRIVATE DATA                                                              */
    /* ************************************************************************* */
    Node<T> * D; //The BST's
    std::vector<std::vector<double>> W;
    std::vector<std::vector<int>> R;
    std::vector<std::vector<double>> C;
    std::vector<double> P; //all key probabilities
    std::vector<double> Q; //all dummy probabilities
    std::vector<T> KEY; //all keys

    /* ************************************************************************* */
    /* PRINTING FUNCTIONS                                                        */
    /* ************************************************************************* */
private:
    int treeHeight(Node<T>* Data){
        if (Data == NULL) return 0;
        int a = treeHeight(*Data->Left());
        int b = treeHeight(*Data->Right());
        return int(MAX(a,b)) + 1;
    }

    int Column(int A){
        if (A  == 1) return A;
        return Column(A - 1) + Column(A - 1)  + 1;
    }
    void pTree(int **Layout, Node<T>* Data, int column, int  row, int height) {
        if (Data == NULL) return;
        Layout[row][column] = Data->Index(); //Data->Value()
        pTree(Layout, *Data->Left(), column - pow(2, height - 2), row + 1, height - 1);
        pTree(Layout, *Data->Right(), column + pow(2, height - 2), row + 1, height - 1);
    }

    void Print(Node<T> * Data, std::ostream& os = std::cout) {
        int h = treeHeight(Data);
        int column = Column(h);
        int **Layout = new int*[h];
        for (int i = 0; i < h; i++) Layout[i] = new int[column];
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < column; j++) Layout[i][j] = -1;
        }
        pTree(Layout, Data, column / 2, 0, h);
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < column; j++) {
                if (Layout[i][j] == -1) std::cout << " " << " ";
                else std::cout << KEY[Layout[i][j]] << " ";
            }
            std::cout << std::endl;
        }
    }
    void preorder(Node<T> *d){
        if (d != NULL) {
            std::cout << d->Value() << " ";
            preorder(*d->Left());
            preorder(*d->Right());
        }
    }
public:
    void Print(std::ostream& os = std::cout){//print the tree
        if (D == nullptr) {
            os << "{ NULL }";
            return;
        }
        Print(D);
    }

    void preorder(){
        preorder(D);
        std::cout << std::endl;
    }

    void PrintW(std::ostream &os = std::cout) {
        for(size_t i = 0; i <= W.size() - 1; i++) {
            for(size_t j = 0; j <=W[0].size() - 1; j++) {
                os << std::setw(5) << W[i][j] << "  ";
            }
            os << std::endl;
        }
    }
    void PrintC(std::ostream &os = std::cout) {
        for(size_t i = 0; i <= C.size() - 1; i++) {
            for(size_t j = 0; j <=C[0].size() - 1; j++) {
                os << std::setw(5) << C[i][j] << "  ";
            }
            os << std::endl;
        }
    }

    void PrintR(std::ostream &os = std::cout) {
        for(size_t i = 0; i <= R.size() - 1; i++) {
            for(size_t j = 0; j <=R[0].size() - 1; j++) {
                os << std::setw(5) << R[i][j] << "  ";
            }
            os << std::endl;
        }
    }
    /* ************************************************************************* */
    /* PRINTING FUNCTIONS END                                                    */
    /* ************************************************************************* */

    /* ************************************************************************* */
    /* FUNCTIONS TO BE IMPLEMENTED: PRIVATE FUNCTIONS                            */
    /* These functions actually calculate the matrix C                           */
    /* ************************************************************************* */
private:
    double generateRecursive(long i, long j){
        //static long NoOfCalls = 1;
        //std::cout << NoOfCalls++ << std::endl;
        
	//YOUR IMPLEMENTATION HERE
    if (i > j) {
        return 0.0;
    }
    
    if (C[i][j] > 0) {
        return C[i][j];
    }
    
    double minCost = std::numeric_limits<double>::infinity();
    
    for (long r = i; r <= j; r++) {
        double cost = generateRecursive(i, r - 1) + generateRecursive(r + 1, j) + W[i][j];
        if (cost < minCost) {
            minCost = cost;
            R[i][j] = r;
        }
    }
    
    C[i][j] = minCost;
    return C[i][j];
    }

    double generateMemoized(long i, long j){
        //static long NoOfCalls = 1;
        //std::cout << NoOfCalls++ << std::endl;

       	//YOUR IMPLEMENTATION HERE
        if (i > j) {
        // Base case: empty subtree
        return 0.0;
    }

    if (C[i][j] > 0) {
        // The cost has already been computed and memoized
        return C[i][j];
    }

    double minCost = std::numeric_limits<double>::max();

    for (long r = i; r <= j; r++) {
        double cost = generateMemoized(i, r - 1) +
                      generateMemoized(r + 1, j) +
                      W[i][j];

        if (cost < minCost) {
            minCost = cost;
            R[i][j] = r;
        }
    }

    C[i][j] = minCost;
    return minCost;
    }

    double generateIterative(long n){
        //static long NoOfCalls = 1;
        //std::cout << NoOfCalls++ << std::endl;

	//YOUR IMPLEMENTATION HERE

        return C[0][n];
    }

    
 
    Node<T>* makeBST(short i,short j){
        Node<T> *d;
        if(i > j) return nullptr;
        d = CreateNode(R[i][j]);
        //Node<T> x = *d;
        *d->Left() = makeBST(i, R[i][j] - 1); //left subtree
        *d->Right() = makeBST(R[i][j]+1, j); //right subtree
        return d;
    }

    /* ************************************************************************* */
    /* PRIVATE FUNCTION TO DELETE THE TREE, THE PUBLIC INTERFACE IS OF THE SAME  */
    /* NAME (OVERLOADED)                                                         */
    /* ************************************************************************* */

    void Clear(Node<T> *t){
        if (!t) return;
        Clear(*t->Left());
        Clear(*t->Right());
        delete t;
    }

public:
    /* ************************************************************************* */
    /* CONSTRUCTORS AND DESTRUCTORS                                              */
    /* ************************************************************************* */
    optimalBSTree() {D=NULL;}
    optimalBSTree<T>(unsigned short n,T* Key, double *p, double *q, bst_mode x = ITERATIVE):D(nullptr){
         makeBST(n,Key,p, q, x);
    }
    ~optimalBSTree<T>() {Clear();}

    //returns 0 if inconsistent, else the cost measure
    double makeBST(unsigned short n,T *Key, double *p, double *q, bst_mode x = ITERATIVE){
        Clear();

        //first consistency check
        if (!Key || !p) {
            std::cout << "Error 001 in initialization\n";
            return 0;
        }

        //create space for values
        try{
            C = std::vector<std::vector<double>> (n+1, std::vector<double>(n+1, 0));
            W = std::vector<std::vector<double>> (n+1, std::vector<double>(n+1, 0));
            R = std::vector<std::vector<int>> (n, std::vector<int>(n, -1));
            KEY = std::vector<T>();

            for (int i = 0; i < n; i++) P.push_back(p[i]);

            if(q) for (int i = 0; i <= n; i++) Q.push_back(q[i]);
            else Q = std::vector<double>(n+1,0);

            for (unsigned i = 0; i < n; i++) KEY.push_back(Key[i]);
        }
        catch(...){
            std::cout << "Error 002 in initialization\n";
            Clear();
            return 0;
        }

        if(P.size() != n || P.size() != KEY.size() || P.size() != (Q.size()-1)) {
            Clear();
            std::cout << "Error 003 in initialization\n";
            return 0;
        }
        for (int i = 0; i<n; i++)
            if(P[i] < 0 || Q[i] < 0) {
                Clear();
                std::cout << "Error 004 in initialization\n";
                return 0;
            }
        if (Q[n] < 0) {
            Clear();
            std::cout << "Error 005 in initialization\n";
            return 0;
        }
        //consistency check over

        //rationalization of probabilities
        double sum = 0.0;
        for (int i = 0; i<n; i++) sum += P[i]+Q[i];
        sum += Q[n];
        for (int i = 0; i<n; i++) {P[i] /= sum; Q[i] /= sum;}
        Q[n] /=sum;
        //rationalization of probabilities over

        for (unsigned i = 0; i <= n; i++) {
            C.at(i).at(i) = q[i];
            W.at(i).at(i) = q[i];
        }


        if (x== RECURSIVE) generateRecursive(0,n);
        else if (x== MEMOIZED) generateMemoized(0,n);
        else if (x== ITERATIVE) generateIterative(n);

        D = makeBST(0,n-1);
        return C[0][n];
    }
    /* ************************************************************************* */
    /* USEFUL FUNCTIONS                                                          */
    /* ************************************************************************* */
private:
    Node<T>* CreateNode(int idx){
        Node<T> *x = new Node<T>;
        if (!x) throw myException("Memory allocation Error.");
        x->Value() = KEY[idx];
        x->Index() = idx;
        x->Probability() = P[idx]; //REMOVE THIS IF THE FIELD prob NOT IN NODE
        *(x->Left()) = nullptr;
        *(x->Right()) = nullptr;
        return x;
    }
public:
    std::vector<std::vector<double>> getW() { return W; }
    std::vector<std::vector<int>> getR() { return R; }
    std::vector<std::vector<double>> getC() { return C; }
    void Clear() {
        Clear(D);
        KEY.clear();
        P.clear();
        Q.clear();
        W.clear();
        R.clear();
        C.clear();
        D=nullptr;
    }

};
#endif // OPTIMALBST_H_INCLUDED
/* ***************************************************************************** */