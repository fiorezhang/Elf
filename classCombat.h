#ifndef CLASS_COMBAT_H
#define CLASS_COMBAT_H

#include "defines.h"
#include "classElf.h"

using namespace std;

typedef struct _Warrior
{
    char *name;
    Power power;
    Element elements;
}Warrior;

class Combat
{
public:
    Combat(const Elf&, const Elf&);
    ~Combat();

    //int getNextAction(Elf &);
    int getOneRoundResult();
    Elf &getFinalResult();
private:
    Warrior warriorA;
    Warrior warriorB;
};

#endif
