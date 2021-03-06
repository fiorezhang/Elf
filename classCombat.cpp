#include <iostream>
#include <iomanip>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "color.h"
#include "classCombat.h"

#define DEBUG_PRINT
#define DEBUG_PRINT_L2

Combat::Combat(Elf &elfA, Elf &elfB)
{
    dragonA.name = new char[strlen(elfA.getName()) + 1]; 
    strcpy(dragonA.name, elfA.getName());
    dragonA.powers = elfA.getPowers();
    dragonA.maxHealth = dragonA.powers.health;
    dragonA.elements = elfA.getElements(); 
    dragonA.pElements = (int *)&(dragonA.elements);
    dragonA.nextStep = NUM_ELEMENTS;
    dragonA.nextDamage = 0;
    dragonA.pElf = &elfA;
    //cout<<elfA<<"\n";

    dragonB.name = new char[strlen(elfB.getName()) + 1]; 
    strcpy(dragonB.name, elfB.getName());
    dragonB.powers = elfB.getPowers();
    dragonB.maxHealth = dragonB.powers.health;
    dragonB.elements = elfB.getElements(); 
    dragonB.pElements = (int *)&(dragonB.elements);
    dragonB.nextStep = NUM_ELEMENTS;
    dragonB.nextDamage = 0;
    dragonB.pElf = &elfB;
    //cout<<elfB<<"\n";

    /*
    #ifdef DEBUG_PRINT
    elfA.printTitle();
    cout<<elfA<<"\n";
    cout<<elfB<<"\n";
    cout<<"\n";
    #endif
    */
}

Combat::~Combat()
{
   delete []dragonA.name; 
   delete []dragonB.name; 
}

static int getRandByBothElements(Element elementsSelf, Element elementsRiva)
{
    int ret = NUM_ELEMENTS;
    int * pElementsSelf = (int *)&elementsSelf;
    int * pElementsRiva = (int *)&elementsRiva;
    int * pElements = new int[5];

    int sumElements = 0; 
    //cout<<"\n";
    for (int i=0; i<NUM_ELEMENTS; i++)
    {
        // Consider rival's elements. For example, self wants to use gold, then the rival's gold, wood, fire is negative, but dirt, agua is positive. So here judge the next step by: self.(gold * rival.dirt * rival.agua) / (rival.gold * rival.wood * rival.fire), the 1000 is just to make sure the integor big enough to calculate the odd
        pElements[i] = 1000 * pElementsSelf[i] / pElementsRiva[i] * pElementsRiva[(i+2)%NUM_ELEMENTS] / pElementsRiva[(i+4)%NUM_ELEMENTS] * pElementsRiva[(i+3)%NUM_ELEMENTS] / pElementsRiva[(i+1)%NUM_ELEMENTS];
        //cout<<pElements[i]<<" - ";
        sumElements += (int)(pElements[i]);
    }
    //cout<<"\n";

    int dice = rand()%sumElements;
    //int copyDice = dice; //TEST ONLY
    for (int i=0; i<NUM_ELEMENTS; i++)
    {
        if (dice < pElements[i])
        {
            ret = i; 
            break; 
        }
        else
            dice -= pElements[i]; 
    }
    /*
    for (int i=0; i<NUM_ELEMENTS; i++)
        cout<<setw(5)<<pElements[i];
    cout<<setw(8)<<copyDice<<setw(6)<<ret<<"\n";
    */
    delete pElements;
    return ret;
}


static int getRandByElements(Element elements)
{
    int ret = NUM_ELEMENTS;
    int * pElements = (int *)&elements;

    int sumElements = 0; 
    for (int i=0; i<NUM_ELEMENTS; i++)
        sumElements += (int)(pElements[i]);

    int dice = rand()%sumElements;
    //int copyDice = dice; //TEST ONLY
    for (int i=0; i<NUM_ELEMENTS; i++)
    {
        if (dice < pElements[i])
        {
            ret = i; 
            break; 
        }
        else
            dice -= pElements[i]; 
    }
    /*
    for (int i=0; i<NUM_ELEMENTS; i++)
        cout<<setw(5)<<pElements[i];
    cout<<setw(8)<<copyDice<<setw(6)<<ret<<"\n";
    */
    return ret;
}

static int getRand()
{
    int ret = rand()%NUM_ELEMENTS;
    return ret;
}

void Combat::getNextAction()
{
    dragonA.nextStep = getRand();
    dragonB.nextStep = getRand();
    //cout<<"dragonA.nextStep: "<<dragonA.nextStep<<"\n";
    //cout<<"dragonB.nextStep: "<<dragonB.nextStep<<"\n";
}

void Combat::getNextAction(Strategy strategyA, Strategy strategyB)
{
    switch (strategyA)
    {
        case RANDOM:
            dragonA.nextStep = getRand();
            break;
        case CONSIDER_SELF:
            dragonA.nextStep = getRandByElements(dragonA.elements);
            break;
        case CONSIDER_BOTH:
            dragonA.nextStep = getRandByBothElements(dragonA.elements, dragonB.elements);
            break; 
        default: 
            dragonA.nextStep = getRand();
    }

    switch (strategyB)
    {
        case RANDOM:
            dragonB.nextStep = getRand();
            break;
        case CONSIDER_SELF:
            dragonB.nextStep = getRandByElements(dragonB.elements);
            break;
        case CONSIDER_BOTH:
            dragonB.nextStep = getRandByBothElements(dragonB.elements, dragonA.elements);
            break; 
        default: 
            dragonB.nextStep = getRand();
    }
    //cout<<"dragonA.nextStep: "<<dragonA.nextStep<<"\n";
    //cout<<"dragonB.nextStep: "<<dragonB.nextStep<<"\n";
}
//return false if combat not finished(health all 
bool Combat::getTurnResult() 
{
    if (dragonA.nextStep < 0 || dragonA.nextStep >= NUM_ELEMENTS || dragonB.nextStep < 0 || dragonB.nextStep >= NUM_ELEMENTS)
    {
        cout<<"\nCOMBAT: ERROR1\n"; //debug only
        return false; 
    }

    dragonA.nextDamage = 0;
    dragonB.nextDamage = 0;

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
    if (dragonA.powers.health > dragonA.maxHealth) dragonA.powers.health = dragonA.maxHealth; 
    if (dragonB.powers.health > dragonB.maxHealth) dragonB.powers.health = dragonB.maxHealth; 

    // to revent both die together, randomly select one live
    if (dragonA.powers.health == 0 && dragonB.powers.health == 0)
    {
        if (rand()%2)
            dragonA.powers.health = 1;
        else
            dragonB.powers.health = 1;
    }
    // combat finish if one of them die
    if (dragonA.powers.health == 0 || dragonB.powers.health == 0)
        return true;

    return false;     
}

void Combat::printTurn()
{
    #ifdef DEBUG_PRINT
    cout  <<setw(5)<<dragonA.name;
    cout  <<"  |  ";

    for (int i=0; i<NUM_ELEMENTS; i++)
    {
        if (i == dragonA.nextStep)
        {
            if (dragonA.nextDamage > 0)
                cout<<LRED<<setw(5)<<dragonA.nextDamage<<CDEF;
            else if (dragonA.nextDamage < 0)
                cout<<LGRE<<setw(5)<<-dragonA.nextDamage<<CDEF;
            else
                cout<<LBLA<<setw(5)<<dragonA.nextDamage<<CDEF;
        }
        else
            cout<<LBLA<<setw(5)<<"_____"<<CDEF;
    }
    cout  <<"  |  ";

    int percentHealthA = 100 * dragonA.powers.health / dragonA.maxHealth;
    if (percentHealthA >= 100)
        cout<<LGRE;
    else if (percentHealthA < 100 && percentHealthA >= 50)
        cout<<LBLU;
    else if (percentHealthA < 50 && percentHealthA >= 20)
        cout<<LYEL; 
    else if (percentHealthA < 20 && percentHealthA > 0)
        cout<<LPUR; 
    else
        cout<<LRED;
    cout  <<setw(5)<<dragonA.powers.health<<CDEF;

    switch ((NUM_ELEMENTS + dragonA.nextStep - dragonB.nextStep) % NUM_ELEMENTS)
    {
        case 0: 
            cout<<" __/__\\__ ";
            break;
        case 1: 
            cout<<" __/_____ ";
            break;
        case 2: 
            cout<<" _____/__ ";
            break;
        case 3: 
            cout<<" __\\_____ ";
            break;
        case 4: 
            cout<<" _____\\__ ";
            break;
    }

    int percentHealthB = 100 * dragonB.powers.health / dragonB.maxHealth;
    if (percentHealthB >= 100)
        cout<<LGRE;
    else if (percentHealthB < 100 && percentHealthB >= 50)
        cout<<LBLU;
    else if (percentHealthB < 50 && percentHealthB >= 20)
        cout<<LYEL; 
    else if (percentHealthB < 20 && percentHealthB > 0)
        cout<<LPUR; 
    else
        cout<<LRED;
    cout  <<setw(5)<<dragonB.powers.health<<CDEF;
    cout  <<"  |  ";

    for (int i=0; i<NUM_ELEMENTS; i++)
    {
        if (i == dragonB.nextStep)
        {
            if (dragonB.nextDamage > 0)
                cout<<LRED<<setw(5)<<dragonB.nextDamage<<CDEF;
            else if (dragonB.nextDamage < 0)
                cout<<LGRE<<setw(5)<<-dragonB.nextDamage<<CDEF;
            else
                cout<<LBLA<<setw(5)<<dragonB.nextDamage<<CDEF;
        }
        else
            cout<<LBLA<<setw(5)<<"_____"<<CDEF;
    }
    cout  <<"  |  ";

    cout  <<setw(5)<<dragonB.name;

    cout<<"\n";
/*
    cout<<setw(5)<<dragonA.name<<" cast "<<setw(4)<<dragonA.nextStep<<" hurt "<<setw(3)<<dragonA.nextDamage<<", self health "<<setw(5)<<dragonA.powers.health<<"; ";
    cout<<setw(5)<<dragonB.name<<" cast "<<setw(4)<<dragonB.nextStep<<" hurt "<<setw(3)<<dragonB.nextDamage<<", self health "<<setw(5)<<dragonB.powers.health<<"\n";
*/
    #endif
}


Elf * Combat::getFinalResult()
{
    if (dragonA.powers.health == 0 && dragonB.powers.health == 0)
        return NULL; 
    else if (dragonA.powers.health == 0)
    {
        return dragonB.pElf; 
    }
    else if (dragonB.powers.health == 0)
    {
        return dragonA.pElf; 
    }
    return NULL;  
}

void Combat::printTitle()
{
    cout  <<setw(5)<<"Name";
    cout  <<"  |  ";
    cout  <<LYEL<<setw(5)<<"Gold"<<CDEF
          <<LGRE<<setw(5)<<"Wood"<<CDEF
          <<LBLA<<setw(5)<<"Dust"<<CDEF
          <<LBLU<<setw(5)<<"Agua"<<CDEF
          <<LRED<<setw(5)<<"Fire"<<CDEF;
    cout  <<"  |  ";
    cout  <<setw(5)<<"Hea";
    cout  <<"    ||    ";
    cout  <<setw(5)<<"Hea";
    cout  <<"  |  ";
    cout  <<LYEL<<setw(5)<<"Gold"<<CDEF
          <<LGRE<<setw(5)<<"Wood"<<CDEF
          <<LBLA<<setw(5)<<"Dust"<<CDEF
          <<LBLU<<setw(5)<<"Agua"<<CDEF
          <<LRED<<setw(5)<<"Fire"<<CDEF;
    cout  <<"  |  ";
    cout  <<setw(5)<<"Name";
    cout  <<"\n";
}

Elf * Combat::autoRun()
{
    #ifdef DEBUG_PRINT
    cout<<setw(7)<<"Turn";
    printTitle();
    #endif
   
    bool bEnd = false; 
    int round = 0;
    for (round=1; round<=MAXIM_COMBAT_TURN; round++)
    {
        //usleep(1000 * 3000);

        //print the number of the turn
        #ifdef DEBUG_PRINT
        cout<<setw(7)<<round;
        #endif

        getNextAction((Strategy)COMBAT_STRATEGY_A, (Strategy)COMBAT_STRATEGY_B);
        bEnd = getTurnResult();
        printTurn();

        if (bEnd) break;
    }
    Elf *pElf = getFinalResult();

    #ifdef DEBUG_PRINT_L2
    dragonA.pElf->printTitle();
    cout<<*(dragonA.pElf)<<"\n";
    cout<<*(dragonB.pElf)<<"\n";

    if (pElf == NULL)
        cout<<LRED<<"DRAW\n"<<CDEF;
    else
        cout<<LBLA<<setw(7)<<"WINNER"
            <<LYEL<<setw(5)<<pElf->getName()<<CDEF
            <<LBLA<<setw(7)<<"ROUND"
            <<LGRE<<setw(3)<<round<<CDEF
            <<"\n";
    cout<<"\n";
    #endif

    if (pElf == NULL)
    {
        // CANT RETURN A NULL, SO, HAVE TO RANDOM ONE
        if (rand()%2)
            pElf = dragonA.pElf; 
        else
            pElf = dragonB.pElf;
    }
    return pElf;
}
