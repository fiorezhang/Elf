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

typedef enum _Strategy
{
    RANDOM, 
    CONSIDER_SELF, 
    CONSIDER_BOTH
}Strategy;

class Combat
{
public:
    Combat(Elf&, Elf&);
    ~Combat();

    void getNextAction();
    void getNextAction(Strategy, Strategy);
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
