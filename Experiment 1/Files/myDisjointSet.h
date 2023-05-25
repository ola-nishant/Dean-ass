#ifndef MYDISJOINTSET_H_INCLUDED
#define MYDISJOINTSET_H_INCLUDED
#include <iostream>
#include <cstdlib>
#include <sstream>

using namespace std;

template <class T>
class Head; //forward declaration

template <class T>
struct Node{
    public:
    Head<T> *Parent;
    Node<T> *Next;
    T Data;
    Node() { Parent = NULL; Next = NULL; }
};

template <class T>
struct Head{
    Node<T> *Front;
    Node<T> *Tail;
    int Size;
    Head() { Front = Tail = NULL; Size = 0; }
};

template <class T>
class myDS; // Forward reference

template <class T>
myDS<T> operator + ( myDS<T>&a,  myDS<T>&b); // Forward reference

template <class T>
myDS<T> operator - ( myDS<T>&a,  myDS<T>&b); // Forward reference

template <class T>
myDS<T> operator * ( myDS<T>&a,  myDS<T>&b); // Forward reference

template <class T>
ostream& operator << (ostream& os, const myDS<T>&S);

template <class T>
class myDS{
private:
    Head<T> H;
public:
    myDS(): H() {}
    myDS(T x);
    myDS(Node<T>& x);
    myDS(const T* x, long Size);
    myDS(const myDS<T>& x);
    //Destructor
    virtual ~myDS() { Clear(); }

    T* First();
    T* Last();
    bool isEmpty();
    int SizeOf();
    bool Contains(T x);

    friend ostream& operator <<<> (ostream& os, const myDS<T>&S);
    friend myDS<T> operator + <>(myDS<T>&a,  myDS<T>&b);
    friend myDS<T> operator - <>(myDS<T>&a,  myDS<T>&b);
    friend myDS<T> operator * <>(myDS<T>&a,  myDS<T>&b);

    myDS<T> operator += (T x);
    myDS<T> operator += (myDS<T> x);
    myDS<T> operator -= (T x);
    myDS<T> operator -= (myDS<T> x);
    myDS<T> operator *= (myDS<T> x);

    string Name();
    void Clear();
};
/* ********************************************************** */
/* Implementation                                             */
/* ********************************************************** */

template <class T>
myDS<T>::myDS(T x): H(){
    Node<T> *t = new Node<T>;
    if (!t) {
        cout << "1. Memory Allocation Error.\n";
        exit(1);
    }
    t->Parent = &H;
    t->Next = NULL;
    t->Data = x;
    H.Front = H.Tail = t;
    H.Size = 1;
}
template <class T>
myDS<T>::myDS(Node<T>& x): H() {
    Node<T> *t = new Node<T>;
    if (!t) {
        cout << "2. Memory Allocation Error.\n";
        exit(1);
    }
    t->Parent = &H;
    t->Next = NULL;
    t->Data = x.Data;
    H.Front = H.Tail = t;
    H.Size = 1;
}

template <class T>
myDS<T>::myDS(const T* x, long Size):H(){
    for (long i = 0; i< Size; i++) *this +=x[i];
}

template <class T>
myDS<T>::myDS(const myDS<T>& x) {
    Node<T> *t = x.H.Front,p;
    Node<T> *f = NULL;
    for (int i = 0; i < x.H.Size; i++) {
        Node<T>* y = new Node<T>();
        if (!y) {
            cout << "3. Memory Allocation Error.\n";
            exit(1);
        }
        y->Data = t->Data;
        y->Parent = &H;
        if (H.Front == NULL) H.Front = y;
        else if (i == x.H.Size - 1) {
            f->Next = y;
            y->Next = NULL;
            H.Tail = y;
            H.Size = x.H.Size;
        }
        else f->Next = y;
        t = t->Next;
        f = y;
    }
}

template <class T>
T* myDS<T>::First() {
    if (H.Front) return &(H.Front->Data);
    return NULL;
}

template <class T>
T* myDS<T>::Last() {
    if (H.Size != 0) return &(H.Tail->Data);
    else return NULL;
}

template <class T>
bool myDS<T>::isEmpty() {
    return H.Size == 0;
}

template <class T>
int myDS<T>::SizeOf(){
    return H.Size;
}

template <class T>
bool myDS<T>::Contains(T x) {
    Node<T> *t = H.Front;
    while (t ) {
        if (t->Data == x) { return true;}
        t =  t->Next;
    }
    return false;
}

template <class T>
ostream& operator << (ostream& os, const myDS<T>&S) {
    Node<T> *t = S.H.Front;
    if (!t) return os << "{ }";;
    os << "{ " ;
    while (t->Next) {
        os << t->Data << ", ";
        t = t->Next;
    }
    return os << t->Data << " }";
}

template <class T>
myDS<T> operator + (myDS<T>&a,  myDS<T>&b){
//Remember the sets are disjoint, no check required
    myDS<T> c;
    Node<T> *t;
    if (a.SizeOf() > b.SizeOf()) {
        c = a;
        t = b.H.Front;
    }
    else {
        c = b;
        t = a.H.Front;
    }
    while(t) {
        //if (!a.Contains(t->Data))
            c += (t->Data);
        t= t->Next;
    }
    return c;
}

template <class T>
myDS<T> operator - (myDS<T>&a,  myDS<T>&b){
    return a;
}

template <class T>
myDS<T> operator * (myDS<T>&a,  myDS<T>&b){
    myDS<T> c;
    return c;
}

template <class T>
myDS<T> myDS<T>::operator += (T x) {
    //if (Contains(x)) return NULL;

    Node<T> *t = new Node<T>;
    if (!t) {
        cout << "5. Memory Allocation Error.\n";
        exit(1);
    }

    if (H.Front == NULL) H.Front = t;
    else H.Tail->Next = t;

    t->Parent = &H;
    t->Data = x;
    t->Next = NULL;
    H.Tail = t;
    H.Size++;
    return *this;
}

template <class T>
myDS<T> myDS<T>::operator += (myDS<T> x){
    Node<T> *t = H.Front;
    while (t) {
        *this += t->Data;
        t = t->Next;
    }
    return *this;
}

template <class T>
myDS<T> myDS<T>::operator -= (T x){
    if (Contains(x)) Remove(x);
    return *this;
}

template <class T>
myDS<T> myDS<T>::operator -= (myDS<T> x){
    Node<T> *t = x.H.Front;
    while (t) {
        if (Contains(t->Data)) Remove(t->Data);
        t = t->Next;
    }
    return *this;
}

template <class T>
myDS<T> myDS<T>::operator *= (myDS<T> x){
    myDS<T> c;
    return c;
}

template <class T>
string myDS<T>::Name() {
    if (H.Size == 0) return "PHI";
    else{
        ostringstream ss;
        ss << H.Front->Data;
        return ss.str();
    }
}

template <class T>
void myDS<T>::Clear() {
    Node<T> *t=H.Front,*p;
    if (!t) return;
    while(t->Next) {
        p = t;
        t = t->Next;
        delete p;
    }
    delete t;
    H.Front = H.Tail = NULL;
    H.Size = 0;
}
#endif // MYDISJOINTSET_H_INCLUDED
