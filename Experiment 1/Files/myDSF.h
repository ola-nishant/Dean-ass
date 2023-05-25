#ifndef MYDSF_H_INCLUDED
#define MYDSF_H_INCLUDED
#include <unordered_map>
#include <vector>
#include <iostream>

template <class T>
struct Node;    //forward reference

template <class T>
std::ostream& operator << (std::ostream& os, const Node<T>& x); //forward reference

template <class T>
bool operator == (const Node<T>& x, const Node<T>& y); //forward reference

template <class T>
struct Node{
    T Data;
    int Parent; // The index of the parent node in the DSF vector
    int idx; //The index where it shall be stored by the DSF vector
    int Value; //to store rank or size
    Node():Data((T)(NULL)), Parent(-1), idx(-1), Value(-1){}
    Node(const T x): Data(x), Parent(-1), idx(-1), Value(-1){}
    explicit Node(T x, int Index): Data(x), Parent(-1), idx(Index), Value(-1){}
    Node(const Node<T>& x): Data(x.Data), Parent(x.Parent), idx(x.idx), Value(x.Value){}
    friend std::ostream& operator <<<>(std::ostream& os, const Node<T>& x);
    friend bool operator == <>(const Node<T>& x, const Node<T>& y);
    Node<T>& operator = (const Node<T>& y);

};

/* ************************************************** */
/* IMPLEMENTATION NODE STRUCTURE                      */
/* ************************************************** */
template <class T>
Node<T>& Node<T>::operator = (const Node<T>& y){
    Data = y.Data;
    Parent = y.Parent;
    idx = y.idx;
    Value = y.Value;
    return *this;
}

template <class T>
bool operator == (const Node<T>& x, const Node<T>& y){
    if (x.Parent == -1) return false;
    if (y.Parent == -1) return false;
    return x.Parent == y.Parent;
}

template <class T>
std::ostream& operator << (std::ostream& os, const Node<T>& x){
    return os << "[" << x.Data << ", " << x.Parent << ", " << x.idx << ", " << x.Value << "]";
}
/* ************************************************** */
typedef enum myDSF_MODE{ BYSIZE, BYRANK} myDSF_MODE;

template <class T>
class myDSF;    //Forward reference

template <class T>
std::ostream& operator << (std::ostream& os,  myDSF<T>& ds); //forward reference

template <class T>
class myDSF{
    /* The key is the data of the element.While the value is the index
        at which the element shall be stored in the vector             */
    std::unordered_map<T,int> myMap;
    /*  The elements are stored here indexed by value of the map       */
    std::vector<Node<T>> myForest;
    myDSF_MODE mode;
    public:
        explicit myDSF(myDSF_MODE m=BYSIZE): myMap(), myForest(), mode(m){}; 
//Make forest empty
        explicit myDSF(T x, int Index,myDSF_MODE m=BYSIZE) : myMap(), myForest(), mode(m) { }; 
//make forest with one element
        /* Returns true if inserted as a singleton set
                   false if already exists                             */
        bool operator += (Node<T> x);   //Implements Make Set
        /* Index of where the parent is stored, -1 if not stored       */
        int myParent(Node<T> x);
        int myParent(const T x);
        /* Returns -1 if the node is not a member else returns
           the idx to the representative element                       */
        int mySet(const Node<T>& x); //Implements Find Set with path compression
        int mySet(T x);  //Implements Find Set with path compression
        /* returns true if the union was performed and false if it
          could not. This can happen if one of the elements was not in
          the forest                                                   */
        int Union( Node<T> x, const Node<T> y);
        friend std::ostream& operator <<<> (std::ostream& os,  myDSF<T>& ds);
        Node<T> operator [] (int i) { //does no range checking
            return myForest[i];
        }
};/* ************************************************** */
/* IMPLEMENTATION myDSF CLASS                         */
/* ************************************************** */

//YOUR IMPLEMENTATUION CODE HERE

#endif // MYDSF_H_INCLUDED	
/* **************************************************************************** */

