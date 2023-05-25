#ifndef MYSET_H_INCLUDED
#define MYSET_H_INCLUDED
#include "myList.h"
#include <sstream>
template <class T>
class mySet; // Forward reference

template <class T>
mySet<T> operator + ( mySet<T>&a,  mySet<T>&b); // Forward reference

template <class T>
mySet<T> operator - ( mySet<T>&a,  mySet<T>&b); // Forward reference

template <class T>
mySet<T> operator * ( mySet<T>&a,  mySet<T>&b); // Forward reference

template <class T>
class mySet: public myList<T> {
private:
    //myList functions not accessible to instances of mySet
public:
    mySet():myList<T>() {}
    mySet(T x):myList<T>(x) {}
    mySet(const T* x, long Size);
    mySet(mySet<T>& x):myList<T>(x) {}
    ~mySet(){Clear();}

    using myList<T>::First;
    using myList<T>::Last;
    using myList<T>::isEmpty;
    using myList<T>::SizeOf;
    using myList<T>::Contains;
    using myList<T>::Clear;
    using myList<T>::Remove;
    Node<T>* addLast(T x);

    string Name() {
        if (myList<T>::H.Size == 0) return "PHI";
        else{
            ostringstream ss;
            ss << myList<T>::H.Front->Data;
            return ss.str();
        }
    }

    friend mySet<T> operator + <>( mySet<T>&a,  mySet<T>&b);
    mySet<T> operator += (T x);
    mySet<T> operator += (mySet<T> x);

    mySet<T> operator -= (T x);
    mySet<T> operator -= (mySet<T> x);
    friend mySet<T> operator - <>( mySet<T>&a,  mySet<T>&b);

    mySet<T> operator *= (mySet<T> x);
    friend mySet<T> operator * <>( mySet<T>&a,  mySet<T>&b);
};

/* ********************************************************* */
/* Implementation                                            */
/* ********************************************************* */
template <class T>
mySet<T>::mySet(const T* x, long Size):myList<T>(){
    for (long i = 0; i< Size; i++) addLast(x[i]);
}

template <class T>
Node<T>* mySet<T>::addLast(T x) {
    if (Contains(x)) return NULL;

    Node<T> *t = new Node<T>;
    if (!t) {
        cout << "5. Memory Allocation Error.\n";
        exit(1);
    }

    if (myList<T>::H.Front == NULL) myList<T>::H.Front = t;
    else myList<T>::H.Tail->Next = t;

    t->Parent = &(myList<T>::H);
    t->Data = x;
    t->Next = NULL;
    myList<T>::H.Tail = t;
    myList<T>::H.Size++;
    return t;
}

template <class T>
mySet<T> mySet<T>::operator += (T x) {
    addLast(x);
    return *this;
}

template <class T>
mySet<T> mySet<T>::operator += (mySet<T> x){
    Node<T> *t = myList<T>::H.Front;
    while (t) {
        addLast(t->Data);
        t = t->Next;
    }
    return *this;
}

template <class T>
mySet<T> mySet<T>::operator -= (T x){
    if (Contains(x)) Remove(x);
    return *this;
}

template <class T>
mySet<T> mySet<T>::operator -= (mySet<T> x){
    Node<T> *t = x.H.Front;
    while (t) {
        if (Contains(t->Data)) Remove(t->Data);
        t = t->Next;
    }
    return *this;
}

template <class T>
mySet<T> mySet<T>::operator *= (mySet<T> x){
    mySet<T> c(*this);
    Node<T> *t = c.H.Front;
    while(t) {
        if (!x.Contains(t->Data)) Remove(t->Data);
        t = t->Next;
    }
    return *this;
}

/* FRIENDS */
template <class T>
mySet<T> operator - ( mySet<T>&a,  mySet<T>&b){
    mySet<T> c(a);
    c -= b;
    return c;
}

template <class T>
mySet<T> operator + ( mySet<T>&a,  mySet<T>&b){
    mySet<T> c;
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
        if (!a.Contains(t->Data)) c.addLast(t->Data);
        t= t->Next;
    }
    return c;
}

template <class T>
mySet<T> operator * ( mySet<T>&a,  mySet<T>&b){
    mySet<T> c,d;
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
        if (a.Contains(t->Data)) d.addLast(t->Data);
        t= t->Next;
    }
    return d;
}
#endif // MYSET_H_INCLUDED
