#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "classElf.h"
#include "classTribe.h"
#include "classCombat.h"

int testCombat()
{
    Elf *pElfA = NULL;
    Elf *pElfB = NULL;
    pElfA = new Elf("Gol", true,  YOUNG_AGE, 300, 300, 300, 300, 100);
    pElfB = new Elf("Ven", false, YOUNG_AGE, 260, 260, 260, 260, 260);

    while (1)
    {
        getchar(); 
        Combat *pCombat = NULL;
        pCombat = new Combat(*pElfA, *pElfB);
        pCombat->autoRun();
        delete pCombat;
        //usleep(1000 * 500);
    }

    delete pElfA; 
    delete pElfB;

    return 0;
}

int testCombat(Elf *pElfA, Elf *pElfB, int round)
{
    if (round == 0)
        round = (unsigned int)(-1);
    while (round--)
    {
        getchar(); 
        Combat *pCombat = NULL;
        pCombat = new Combat(*pElfA, *pElfB);
        pCombat->autoRun();
        delete pCombat;
        //usleep(1000 * 500);
    }
    return 0;
}

int main()
{
    Tribe tribeElf[MAXIM_TRIBES]; 
    int round = 0; 


    srand((unsigned)time(NULL));
    
    //testCombat();

    while (1)
    {
        cout<<"\nRound: "<<++round<<"\n"; 
        for (int i=0; i<MAXIM_TRIBES; i++)
        {

            tribeElf[i].mate(); 

            tribeElf[i].ding(); 

            tribeElf[i].grow(); 

            tribeElf[i].list(); 

            tribeElf[i].buri(); 

            testCombat(tribeElf[i].findRand(), tribeElf[i].findRand(), 1);

            if (tribeElf[i].getCount() == 0) 
                return 0; 
        }
        //getchar(); 
        //usleep(1000 * SLEEP_MS);
        getchar();
    }

        //tribeElf.list(); 

    return 0; 
}
