#include <iostream>
#include <iomanip>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "color.h"
#include "classCombat.h"

Combat::Combat(Elf &elfA, Elf &elfB)
{
    dragonA.name = new char[strlen(elfA.getName()) + 1]; 
    strcpy(dragonA.name, elfA.getName());
    dragonA.powers = elfA.getPowers();
    dragonA.elements = elfA.getElements(); 
    dragonA.pElements = (int *)&(dragonA.elements);
    dragonA.nextStep = NUM_ELEMENTS;
    dragonA.nextDamage = 0;
    dragonA.pElf = &elfA;
    cout<<elfA<<"\n";

    dragonB.name = new char[strlen(elfB.getName()) + 1]; 
    strcpy(dragonB.name, elfB.getName());
    dragonB.powers = elfB.getPowers();
    dragonB.elements = elfB.getElements(); 
    dragonB.pElements = (int *)&(dragonB.elements);
    dragonB.nextStep = NUM_ELEMENTS;
    dragonB.nextDamage = 0;
    dragonB.pElf = &elfB;
    cout<<elfB<<"\n";

    cout<<"dragonA.name:  "<<dragonA.name<<"["<<dragonA.powers.health<<"]"<<" =="<<dragonA.powers.energy<<"== "<<dragonA.pElements[0]<<" "<<dragonA.pElements[1]<<" "<<dragonA.pElements[2]<<" "<<dragonA.pElements[3]<<" "<<dragonA.pElements[4]<<"""""\n";
    cout<<"dragonB.name:  "<<dragonB.name<<"["<<dragonB.powers.health<<"]"<<" =="<<dragonB.powers.energy<<"== "<<dragonB.pElements[0]<<" "<<dragonB.pElements[1]<<" "<<dragonB.pElements[2]<<" "<<dragonB.pElements[3]<<" "<<dragonB.pElements[4]<<"""""\n";
}

Combat::~Combat()
{
   delete []dragonA.name; 
   delete []dragonB.name; 
}

void Combat::getNextAction()
{
    dragonA.nextStep = rand()%NUM_ELEMENTS;
    dragonB.nextStep = rand()%NUM_ELEMENTS;
    //cout<<"dragonA.nextStep: "<<dragonA.nextStep<<"\n";
    //cout<<"dragonB.nextStep: "<<dragonB.nextStep<<"\n";
}

//return false if combat not finished(health all 
bool Combat::getOneRoundResult() 
{
    if (dragonA.nextStep < 0 || dragonA.nextStep >= NUM_ELEMENTS || dragonB.nextStep < 0 || dragonB.nextStep >= NUM_ELEMENTS)
    {
        cout<<"\nCOMBAT: ERROR1\n"; //debug only
        return false; 
    }


    switch ((NUM_ELEMENTS + dragonA.nextStep - dragonB.nextStep) % NUM_ELEMENTS)
    {
        case 0:
        dragonA.nextDamage = dragonA.powers.energy * dragonA.pElements[dragonA.nextStep] / dragonB.pElements[dragonB.nextStep];
        dragonB.nextDamage = dragonB.powers.energy * dragonB.pElements[dragonB.nextStep] / dragonA.pElements[dragonA.nextStep];
        dragonA.powers.health -= dragonB.nextDamage; 
        dragonB.powers.health -= dragonA.nextDamage;
        break;

        case 1: 
        dragonB.nextDamage = dragonB.powers.energy * dragonB.pElements[dragonB.nextStep] / dragonA.pElements[dragonA.nextStep];
        dragonA.powers.health -= dragonB.nextDamage; 
        break;

        case 2: 
        dragonA.nextDamage = - dragonA.powers.energy * dragonA.pElements[dragonA.nextStep] / dragonB.pElements[dragonB.nextStep];
        dragonB.powers.health -= dragonA.nextDamage;
        break;
        
        case 3: 
        dragonB.nextDamage = - dragonB.powers.energy * dragonB.pElements[dragonB.nextStep] / dragonA.pElements[dragonA.nextStep];
        dragonA.powers.health -= dragonB.nextDamage;
        break;

        case 4: 
        dragonA.nextDamage = dragonA.powers.energy * dragonA.pElements[dragonA.nextStep] / dragonB.pElements[dragonB.nextStep];
        dragonB.powers.health -= dragonA.nextDamage;
        break;

        default:
        cout<<"\nCOMBAT: ERROR2\n"; //debug only
        return false; 
    }

    if (dragonA.powers.health < 0) dragonA.powers.health = 0;
    if (dragonB.powers.health < 0) dragonB.powers.health = 0;

    /*
    // to revent both die together, randomly select one live
    if (dragonA.powers.health == 0 && dragonB.powers.health == 0)
    {
        if (rand()%2)
            dragonA.powers.health = 1;
        else
            dragonB.powers.health = 1;
    }
    */

    // print
    cout<<dragonA.name<<"   <<"<<dragonA.nextStep<<">>    "<<dragonA.nextDamage<<"    [ "<<dragonA.powers.health<<" ]"<<"\n";
    cout<<dragonB.name<<"   <<"<<dragonB.nextStep<<">>    "<<dragonB.nextDamage<<"    [ "<<dragonB.powers.health<<" ]"<<"\n";
    cout<<"\n";
    
    // set back to default value before next turn
    dragonA.nextStep = NUM_ELEMENTS;
    dragonA.nextDamage = 0;
    dragonB.nextStep = NUM_ELEMENTS;
    dragonB.nextDamage = 0;

    // combat finish if one of them die
    if (dragonA.powers.health == 0 || dragonB.powers.health == 0)
        return true;

    return false;     
}

Elf * Combat::getFinalResult()
{
    if (dragonA.powers.health == 0 && dragonB.powers.health == 0)
        return NULL; 
    else if (dragonA.powers.health == 0)
    {
        cout<<"WINNER - "<<dragonB.name<<"\n";
        return dragonB.pElf; 
    }
    else if (dragonB.powers.health == 0)
    {
        cout<<"WINNER - "<<dragonA.name<<"\n";
        return dragonA.pElf; 
    }
    return NULL;  
}

Elf * Combat::autoRun()
{
    for (int i=0; i<MAXIM_COMBAT_TURN; i++)
    {
        //usleep(1000 * 3000);
        cout<<"Round: "<<i<<"\n";
        getNextAction();
        
        if (getOneRoundResult())
            break;
    }
    Elf *pElf = getFinalResult();
    if (pElf == NULL)
        cout<<"EQUALIZE\n";
    return pElf;
}
