#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "defines.h"
#include "color.h"
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
    srand((unsigned)time(NULL));

    Tribe tribeElf[MAXIM_TRIBES]; 
    int count[MAXIM_TRIBES];
    int round = 0; 
    Elf *pElfAdopt = NULL;

    //testCombat();

    while (1)
    {
        cout<<"\nRound: "<<++round<<"\n"; 
        for (int i=0; i<MAXIM_TRIBES; i++)
        {
            count[i] = tribeElf[i].autoRun();
            //testCombat(tribeElf[i].findRand(), tribeElf[i].findRand(), 1);

            if (count[i] == 0) 
                return 0; 
        }

        for (int i=0; i<MAXIM_TRIBES; i++)
        {
            //TODO: test adoption
            if (count[i] < WARN_POPULATION)
            {
                int indexAdopt = i;
                while(indexAdopt == i)
                {
                    indexAdopt = rand()%MAXIM_TRIBES;
                }
                pElfAdopt = tribeElf[indexAdopt].findRand();
                tribeElf[indexAdopt].remove(pElfAdopt);
                tribeElf[i].insert(pElfAdopt);
                cout<<LRED<<"Adopt"<<LPUR<<" ["<<setw(3)<<pElfAdopt->getName()<<setw(5)<<pElfAdopt->getIndex()<<"] "<<CDEF<<"from "<<LYEL<<tribeElf[indexAdopt].getName()<<CDEF<<" to "<<LGRE<<tribeElf[i].getName()<<CDEF<<"\n";
            }
        }

        #if AUTO_MODE
            usleep(1000 * SLEEP_MS);
        #else
            usleep(1000 * 1);
            getchar();
        #endif
    }

        //tribeElf.list(); 

    return 0; 
}
