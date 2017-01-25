#ifndef CLASS_COMBAT_H
#define CLASS_COMBAT_H

#include "defines.h"
#include "classElf.h"

using namespace std;

typedef struct _Dragon
{
    char *name;
    Power powers;
    Element elements;
    int * pElements;
    int nextStep; 
    int nextDamage;
    Elf *pElf;
}Dragon;

class Combat
{
public:
    Combat(Elf&, Elf&);
    ~Combat();

    void getNextAction();
    bool getOneRoundResult();
    Elf *getFinalResult();
    Elf *autoRun();
private:
    Dragon dragonA;
    Dragon dragonB;
};

#endif
