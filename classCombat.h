#ifndef CLASS_COMBAT_H
#define CLASS_COMBAT_H

#include "defines.h"
#include "classElf.h"

using namespace std;

typedef struct _Dragon
{
    char *name;
    Power powers;
    int maxHealth;
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
    bool getTurnResult();
    Elf *getFinalResult();
    void printTitle();
    void printTurn();
    Elf *autoRun();
private:
    Dragon dragonA;
    Dragon dragonB;
};

#endif
