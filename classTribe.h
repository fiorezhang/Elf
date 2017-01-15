#ifndef CLASS_TRIBE_H
#define CLASS_TRIBE_H

#include "defines.h"

using namespace std;

class Elf; 

class Tribe
{
public: 
    Tribe();
    ~Tribe();

    //void startTurn(); 
    void mate();
    void ding();
    void list();
    void test();
    void grow();
    void buri(); 

    void insert(Elf *); 
    void remove(Elf *);
    Elf *findRand();
    Elf *findNext(Elf *);

    int getCount() const { return count; }
private: 
    Elf *pHead; 
    int count;
};

#endif//CLASS_TRIBE_H
