#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED
#include <cmath>
#include <iostream>
#include <ostream>
#include <vector>

#define MAX(a,b) ((a) > (b)) ? (a) : (b)

class Node{

    int V;// Key Value
    Node *L; //LEFT CHILD POINTER
    Node *R; //RIGHT CHILD POINTER

public:
    Node(): V(0), L(nullptr), R(nullptr) {}
    Node(int x): V(x), L(nullptr), R(nullptr) {}
    Node(int x, Node *left, Node *right): V(x), L(left), R(right) {}
    Node(Node &x): V(x.V), L(x.L), R(x.R) {}

    Node& operator = (Node x) {
        V = x.V;
        L = x.L;
        R = x.R;
        return *this;
    }

    friend std::ostream& operator >> (std::ostream& os, Node &x) {
        return os << x.V;
    }

    int& Value() { return V;}
    Node** Left() { return &L;}
    Node** Right() { return &R;}
};

class allBSTree{
    std::vector<Node *> D; //The BST's
    allBSTree() {}

    Node* CreateNode(int v){
        Node *x = new Node;
        x->Value() = v;
        *(x->Left()) = nullptr;
        *(x->Right()) = nullptr;
        return x;
    }

    
std::vector<Node *> generateBST(long i, long j){
        std::vector<Node *> Temp;
        if (i > j) Temp.push_back(NULL);
        for (long m = i; m <= j; m++) {
            std::vector<Node*> lst  = generateBST(i, m - 1); // Left Sub tree
            std::vector<Node*> rst = generateBST(m + 1, j);
            for (long n = 0; n < long(lst.size()); n++) { //j= n
                Node* lc = lst[n];                           // left child
                for (long k = 0; k < long(rst.size()); k++) {
                    Node* rc = rst[k];                       // right child
                    Node* Data = CreateNode(m);                    // m as root
                    *Data->Left() = lc;                      // left child subtree
                    *Data->Right() = rc;                    // right child subtree
                    Temp.push_back(Data);                       // add to D
                }
            }
        }
        return Temp;
    }

public:
    allBSTree(unsigned short n){
        //DO NOT USE FOR MORE THAN 10, n is the number of keys
        D = generateBST(1,n);
    }

    void makeBSTree(unsigned short n) {
        D.clear();
        D = generateBST(0,n-1);
    }

    unsigned long numberBST() {
        return (unsigned long)(D.size());
    }
private:
    int treeHeight(Node* Data){
        if (Data == NULL) return 0;
        int a = treeHeight(*Data->Left());
        int b = treeHeight(*Data->Right());
        return int(MAX(a,b)) + 1;
    }

    int Column(int A){
        if (A  == 1) return A;
        return Column(A - 1) + Column(A - 1)  + 1;
    }
    void pTree(int **Layout, Node *Data, int column, int  row, int height) {
        if (Data == NULL) return;
        Layout[row][column] = Data->Value();
        pTree(Layout, *Data->Left(), column - pow(2, height - 2), row + 1, height - 1);
        pTree(Layout, *Data->Right(), column + pow(2, height - 2), row + 1, height - 1);
    }

    void Printer(Node *Data, std::ostream& os = std::cout) {
        int h = treeHeight(Data);
        int column = Column(h);
        int **Layout = new int*[h];
        for (int i = 0; i < h; i++) Layout[i] = new int[column];
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < column; j++) Layout[i][j] = 0;
        }
        pTree(Layout, Data, column / 2, 0, h);
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < column; j++) {
                if (Layout[i][j] == 0) std::cout << " " << " ";
                else std::cout << Layout[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
    void preorder(Node *d){
        if (d != NULL) {
            std::cout << d->Value() << " ";
            preorder(*d->Left());
            preorder(*d->Right());
        }
    }
public:
    void Print(unsigned long i, std::ostream& os = std::cout){//print ith tree
        if (D.size() == 0 || i < 1 || i > D.size() ) {
            os << "{ NULL }";
            return;
        }
        Printer(D[i-1]);
    }
    void preorder(){
        for (long i = 0; i < long(D.size()); i++) {
            preorder(D[i]);
            std::cout << std::endl;
        }
    }
    long C(int n){//Catalan number
        if (n < 0) return 0;
        else if (n==0 || n == 1) return 1;
        else return 2*(2*n-1) * C(n-1) / (n+1);
    }
};

#endif // TREE_H_INCLUDED