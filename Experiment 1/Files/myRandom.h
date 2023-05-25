#ifndef __MYRANDOM_H_INCLUDED__
#define __MYRANDOM_H_INCLUDED__

class myRandom{
    static const unsigned long a = 1664525L, c = 1664525L;
    static unsigned long x;
public:
    myRandom(unsigned long s=8462817L) { x = s;}
    static void setSeed(unsigned long s){ x = s;}
    static unsigned long getVal() { return x = a*x + c;}
    static unsigned long getCurVal(){ return x;}
};
#endif // MYRANDOM_H_INCLUDED
