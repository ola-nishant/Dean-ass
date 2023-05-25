#ifndef MYLIST_H_INCLUDED
#define MYLIST_H_INCLUDED
#include <iostream>
#include <cstdlib>

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
class myList; //Forward reference

template <class T>
myList<T> operator + ( myList<T>&a,  myList<T>&b); // Forward reference

template <class T>
ostream& operator << (ostream& os, const myList<T>&List); // Forward reference

template <class T>
class myList{
protected:
    Head<T> H;
public:
    //Constructors
    explicit myList(): H() {}
    explicit myList(T x);
    explicit myList(Node<T>& x);
    myList(const myList<T>& x);
    //Destructor
    virtual ~myList() { Clear(); }
    /* ******************************************************** */
    /* Operational functions                                    */
    /* ******************************************************** */
    Node<T>* First();
    Node<T>* Last();
    bool isEmpty();
    int SizeOf();
    Node<T>* Contains(T x);
    Node<T>* Remove(T x);//only removes the node if it exists, remember to delete once used up
    Node<T>* RemoveLast(); //only removes the node if it exists, remember to delete once used up
    Node<T>* RemoveFirst(); //only removes the node if it exists, remember to delete once used up
    Node<T>* addFront(T x);
    Node<T>* addFront(Node<T>* x);//assumes x was dynamically allocated
    Node<T>* addLast(T x);
    Node<T>* addLast(Node<T>* x); // attaches the node x, make x from dynamic memory
    Node<T>* addAfter(T x, T y);
    Node<T>* addAfter(T x, Node<T> *y);
    void Clear(); // Resets the list
    myList<T>& operator = (myList<T> x); //overload assignment

    /* ************************************************************ */
    /* Friend Functions                                             */
    /* ************************************************************ */
    friend myList<T> operator + <>( myList<T>&a,  myList<T>&b);
        //returns c = a+b
    friend ostream& operator <<<>(ostream& os, const myList<T>&List);
};

/* ********************************************************** */
/* Implementation                                             */
/* ********************************************************** */
template <class T>
myList<T>::myList(T x): H() {
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
myList<T>::myList(Node<T>& x): H() {
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
myList<T>::myList(const myList<T>& x) {
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
Node<T>* myList<T>::First() {
    return H.Front;
}

template <class T>
Node<T>* myList<T>::Last() {
    return H.Tail;
}

template <class T>
bool myList<T>::isEmpty() {
    return H.Size == 0;
}

template <class T>
int myList<T>::SizeOf(){
    return H.Size;
}

template <class T>
Node<T>* myList<T>::Contains(T x) {
    Node<T> *t = H.Front;
    while (t ) {
        if (t->Data == x) { return t;}
        t =  t->Next;
    }
    return NULL;
}

template <class T>
Node<T>* myList<T>::Remove(T x) {//only removes the node if it exists, remember to delete once used up
    Node<T> *t = H.Front;
    if (t->Data == x) return RemoveFirst();
    while (t->Next && t->Next->Data != x) t =  t->Next;
    if(t->Next) {
        Node<T> *p = t->Next;
        t->Next = p->Next;
        H.Size--;
        p->Parent = NULL;
        p->Next = NULL;
        return p;
    }
    return t->Next;
}

template <class T>
Node<T>* myList<T>::RemoveLast() {//only removes the node if it exists, remember to delete once used up
    Node<T> *t = H.Front;
    if (!t) return t; // no item present
    if (H.Size == 1) RemoveFirst();
    while (t->Next->Next) t = t->Next;
    Node<T> *p = t->Next;
    t->Next = p->Next;
    H.Tail = t ;
    p->Parent = NULL;
    p->Next = NULL;
    H.Size--;
    return p;
}

template <class T>
Node<T>* myList<T>::RemoveFirst() {//only removes the node if it exists, remember to delete once used up
    Node<T> *t = H.Front;
    if (!t) return t; // no item present
    H.Front = t->Next;
    H.Size--;
    t->Parent = NULL;
    t->Next = NULL;
    return t;
}

template <class T>
Node<T>* myList<T>::addFront(T x) {
    Node<T> *t = new Node<T>;
    if (!t) {
        cout << "4. Memory Allocation Error.\n";
        exit(1);
    }
    if (H.Front == NULL) H.Tail = t;
    t->Next = H.Front;
    t->Parent = &H;
    t->Data = x;
    H.Front = t;
    H.Size++;
    return t;
}

template <class T>
Node<T>* myList<T>::addFront(Node<T>* x)  {//assumes x was dynamically allocated
    if (H.Front == NULL) H.Tail = x;
    x->Next = H.Front;
    x->Parent = &H;
    H.Front = x;
    H.Size++;
    return x;
}

template <class T>
Node<T>* myList<T>::addLast(T x) {
    if (H.Front == NULL) return addFront(x);
    Node<T> *t = new Node<T>;
    if (!t) {
        cout << "5. Memory Allocation Error.\n";
        exit(1);
    }
    t->Parent = &H;
    t->Data = x;
    H.Tail->Next = t;
    t->Next = NULL;
    H.Tail = t;
    H.Size++;
    return t;
}

template <class T>
Node<T>* myList<T>::addLast(Node<T>* x)  {// attaches the node x, make x from dynamic memory
    if (H.Front == NULL) return addFront(x);
    x->Parent = &H;
    H.Tail->Next = x;
    x->Next = NULL;
    H.Tail = x;
    H.Size++;
    return x;
}

template <class T>
Node<T>* myList<T>::addAfter(T x, T y) {
    Node<T> *t = H.Front;
    if (t == NULL) return t;
    while (t->Next) {
        if (t->Data == x) break;
        t =  t->Next;
    }
    if (!t->Next) return NULL;
    Node<T> *tmp = new Node<T>;
    if (!tmp) {
        cout << "6. Memory Allocation Error.\n";
        exit(1);
    }
    tmp->Next = t->Next;
    tmp->Parent = t->Parent;
    tmp->Data = y;
    t->Next = tmp;
    H.Size++;
    return tmp;
}

template <class T>
Node<T>* myList<T>::addAfter(T x, Node<T> *y) {
    Node<T> *t = H.Front;
    if (t == NULL) return t;
    while (t->Next) {
        if (t->Data == x) break;
        t =  t->Next;
    }
    if (!t->Next) return NULL;
    y->Next = t->Next;
    y->Parent = t->Parent;
    t->Next = y;
    H.Size++;
    return y;
}

template <class T>
void myList<T>::Clear() {
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

template <class T>
myList<T>& myList<T>::operator = (myList<T> x) {
    Clear();
    //cout << "X " << x;
    Node<T> *t = x.H.Front,p;
    Node<T> *f = NULL;
    for (int i = 0; i < x.H.Size; i++){
        Node<T>* y = new Node<T>();
        if (!y) {
            cout << "7. Memory Allocation Error.\n";
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
    return *this;
}
/* ***************************************************** */
template <class T>
myList<T> operator + ( myList<T>&a,  myList<T>&b){
    myList<T> c; //= new myList<T>;
    Node<T> *t;
    if (a.SizeOf() > b.SizeOf()) {
        c = a;
        t = b.H.Front;
    }
    else {
        c = b;
        t = a.H.Front;
    }
    //cout << "A = " << a << "B = " << b << "C = " << c;
    while(t) {
        c.addLast(t->Data);
        t= t->Next;
    }
    cout << "C = " << c;
    return c;
}

template <class T>
ostream& operator << (ostream& os, const myList<T>&List) {
    Node<T> *t = List.H.Front;
    if (!t) return os << "{ }" << endl;
    os << "{ " ;
    while (t->Next) {
        os << t->Data << ", ";
        t = t->Next;
    }
    return os << t->Data << " }" << endl;
}

#endif // MYLIST_H_INCLUDED
