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
    pElfA = new Elf("Gol", true,  YOUNG_AGE, 100, 100, 100, 100, 100);
    pElfB = new Elf("Ven", false, YOUNG_AGE, 100, 100, 100, 100, 100);

    Combat *pCombat = NULL;
    pCombat = new Combat(*pElfA, *pElfB);
    pCombat->autoRun();

while(1);
    return 0;
}


int main()
{
    Tribe tribeElf[MAXIM_TRIBES]; 
    int round = 0; 


    srand((unsigned)time(NULL));
    
    testCombat();

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

            if (tribeElf[i].getCount() == 0) 
                break; 
        }
        //getchar(); 
        usleep(1000 * SLEEP_MS);
    }

        //tribeElf.list(); 

    return 0; 
}
