#include <iostream>
#include <iomanip>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "color.h"
#include "classElf.h"
#include "classTribe.h"

Tribe::Tribe()
{
    pHead = NULL; 
    count = 0;

    ////
    Elf *pElf = NULL; 
    pElf = new Elf("Gol", true,  YOUNG_AGE, BASIC_VALUE+rand()%BASIC_VALUE, BASIC_VALUE, BASIC_VALUE, BASIC_VALUE, BASIC_VALUE);    insert(pElf);
    pElf = new Elf("Ven", false, YOUNG_AGE, BASIC_VALUE+rand()%BASIC_VALUE, BASIC_VALUE, BASIC_VALUE, BASIC_VALUE, BASIC_VALUE);    insert(pElf);
    pElf = new Elf("Wod", true,  YOUNG_AGE, BASIC_VALUE, BASIC_VALUE+rand()%BASIC_VALUE, BASIC_VALUE, BASIC_VALUE, BASIC_VALUE);    insert(pElf);
    pElf = new Elf("Jup", false, YOUNG_AGE, BASIC_VALUE, BASIC_VALUE+rand()%BASIC_VALUE, BASIC_VALUE, BASIC_VALUE, BASIC_VALUE);    insert(pElf);
    pElf = new Elf("Wat", true,  YOUNG_AGE, BASIC_VALUE, BASIC_VALUE, BASIC_VALUE+rand()%BASIC_VALUE, BASIC_VALUE, BASIC_VALUE);    insert(pElf);
    pElf = new Elf("Mer", false, YOUNG_AGE, BASIC_VALUE, BASIC_VALUE, BASIC_VALUE+rand()%BASIC_VALUE, BASIC_VALUE, BASIC_VALUE);    insert(pElf);
    pElf = new Elf("Fir", true,  YOUNG_AGE, BASIC_VALUE, BASIC_VALUE, BASIC_VALUE, BASIC_VALUE+rand()%BASIC_VALUE, BASIC_VALUE);    insert(pElf);
    pElf = new Elf("Mar", false, YOUNG_AGE, BASIC_VALUE, BASIC_VALUE, BASIC_VALUE, BASIC_VALUE+rand()%BASIC_VALUE, BASIC_VALUE);    insert(pElf);
    pElf = new Elf("Dus", true,  YOUNG_AGE, BASIC_VALUE, BASIC_VALUE, BASIC_VALUE, BASIC_VALUE, BASIC_VALUE+rand()%BASIC_VALUE);    insert(pElf);
    pElf = new Elf("Sat", false, YOUNG_AGE, BASIC_VALUE, BASIC_VALUE, BASIC_VALUE, BASIC_VALUE, BASIC_VALUE+rand()%BASIC_VALUE);    insert(pElf);
    ////
}

Tribe::~Tribe()
{
    Elf *pElf = NULL; 
    while (pHead != NULL)
    {
        pElf = pHead; 
        remove(pElf); 
        delete pElf; 
    }
}

bool ifRelative(Ancestor ancPa, Ancestor ancMa)
{
    bool ret = false; 
    for (unsigned int i=0; i<(sizeof(Ancestor)/sizeof(int)); i++)
    {
        for (unsigned int j=0; j<(sizeof(Ancestor)/sizeof(int)); j++)
        {
            if (*(((unsigned int *)(&ancPa)) + i) == *(((unsigned int *)(&ancMa)) + j) && 
                *(((unsigned int *)(&ancPa)) + i) != 0)
            {
                ret = true; 
                break; 
            }
        }
    }
    return ret; 
}

void Tribe::mate()
{
    Elf *pElfPa = NULL; 
    Elf *pElfMa = NULL; 
    Elf *pElfCd = NULL; 
    int cnt = 0;
    int loop = 0;  
    int countOld = count; 

    ////cout<<"MATE++++++++\n"; 

    while (loop++ < countOld && count < MAXIM_POPULATION)
    {
        ////cout<<"mate loop: "<<loop<<"\n"; 
        // find a male
        cnt = 0; 
        pElfPa = findRand(); 
        ////cout<<(*pElfPa)<<"\n"; 
        while ((pElfPa->getStatus() == PUPAE || 
                pElfPa->getGender() != true || 
                pElfPa->getAction() != NONE || 
                pElfPa->getKid() >= MAXIM_KINDER) && cnt < count)
        {
            pElfPa = findNext(pElfPa); 
            cnt++; 
            ////cout<<(*pElfPa)<<"\n"; 
        }
        if (cnt == count)
            continue; 
    
        // find a female, and not
        cnt = 0; 
        pElfMa = findRand(); 
        ////cout<<(*pElfMa)<<"\n"; 
        while ((pElfMa->getStatus() == PUPAE || 
                pElfMa->getGender() != false || 
                pElfMa->getAction() != NONE || 
                pElfMa->getKid() >= MAXIM_KINDER || 
                ifRelative(pElfPa->getAncestors(), pElfMa->getAncestors())) && cnt < count)
        {
            pElfMa = findNext(pElfMa); 
            cnt++; 
            ////cout<<(*pElfMa)<<"\n"; 
        }
        if (cnt == count)
            continue; 

        // generate the child
        pElfCd = new Elf(*pElfPa, *pElfMa); 
        insert(pElfCd); 
        ////cout<<(*pElfCd)<<"\n"; 
    }

    ////cout<<"MATE--------\n"; 
}

void Tribe::ding()
{
    int loop = 0; 
    Elf *pElf = pHead; 

    if (pElf == NULL) return; 

    while (loop++ < count)
    {
        if (pElf->getAction() == NONE)
        {
            pElf->ding(); 
        }
        pElf = findNext(pElf); 
    }
}

void Tribe::grow()
{
    int loop = 0; 
    Elf *pElf = pHead; 

    if (pElf == NULL) return; 

    while (loop++ < count)
    {
        pElf->grow(); 
        pElf = findNext(pElf); 
    }
}

typedef struct _Statis
{
    int value;
    int count;
}Statis;

void sortStatis(int *testValue, Statis *pStat, int sizeArray)
{
    /*for (int i=0; i<sizeArray; i++)
        cout<<testValue[i]<<" ";
    cout<<"\n";*/

    for (int i=0; i<sizeArray; i++)
    {
        for (int j=i; j<sizeArray; j++)
        {
            if (testValue[i] < testValue[j])
            {
                int temp = testValue[i];
                testValue[i] = testValue[j];
                testValue[j] = temp;
            }
        }
    }

    /*for (int i=0; i<sizeArray; i++)
        cout<<testValue[i]<<" ";
    cout<<"\n";*/

    //Statis *pStat = new Statis[sizeArray];
    memset(pStat, 0, sizeof(pStat[0])*sizeArray);
    int j = 0;
    pStat[0].value = testValue[0];
    for (int i=0; i<sizeArray; i++)
    {
        if (testValue[i] == 0)
            break;
        else if (pStat[j].value == testValue[i])
            pStat[j].count++;
        else
        {
            pStat[++j].value = testValue[i];
            pStat[j].count++;
        }
    }
    for (int i=0; i<sizeArray; i++)
    {
        for (int j=i; j<sizeArray; j++)
        {
            if (pStat[i].count <= pStat[j].count)
            {
                Statis temp = pStat[i];
                pStat[i] = pStat[j];
                pStat[j] = temp;
            }
        }
    }
    /*for (int j=0; j<sizeArray; j++)
        cout<<setw(3)<<pStat[j].value<<"  "<<setw(3)<<pStat[j].count<<"\n";*/
    //delete []pStat;
}

static const string sColorAncestor[] = { LBLA, LRED, LGRE, LYEL, LBLU, LPUR, LCYA, LWHI };

void Tribe::list()
{
    int loop = 0; 
    int sum = 0; 
    int sizeArray = MAXIM_POPULATION * 7; 
    int Ancient[MAXIM_POPULATION * 7]; 
    Statis Result[MAXIM_POPULATION * 7]; 
    int cntAnc = 0; 
    Elf *pElf = pHead; 

    memset(Ancient, 0, sizeof(Ancient[0]) * sizeArray); 
    memset(Result, 0, sizeof(Result[0]) * sizeArray); 

    if (pElf == NULL) return; 

    pElf->printTitle(); 

    pElf = findNext(pElf); //the head always point to the last one, so shift one
    while (loop++ < count)
    {
        cout<<(*pElf)<<"\n"; 
        sum+=pElf->getElements().gold + pElf->getElements().wood + pElf->getElements().dust + pElf->getElements().agua + pElf->getElements().fire; 
        Ancient[cntAnc++] = pElf->getAncestors().idPaPa; Ancient[cntAnc++] = pElf->getAncestors().idPaMa; 
        Ancient[cntAnc++] = pElf->getAncestors().idMaPa; Ancient[cntAnc++] = pElf->getAncestors().idMaMa; 
        Ancient[cntAnc++] = pElf->getAncestors().idPa; Ancient[cntAnc++] = pElf->getAncestors().idMa; 
        Ancient[cntAnc++] = pElf->getAncestors().idI; 
        pElf = findNext(pElf); 
    }
    sortStatis(Ancient, Result, sizeArray); 
    cout<<"Count: "<<setw(2)<<count<<", value(avarage): "<<setw(4)<<sum/count<<", Ancestors: "; 
    cout<<sColorAncestor[Result[0].value%8]<<setw(7)<<Result[0].value<<" >"<<LRED<<setw(2)<<Result[0].count<<CDEF<<", "; 
    cout<<sColorAncestor[Result[1].value%8]<<setw(7)<<Result[1].value<<" >"<<LYEL<<setw(2)<<Result[1].count<<CDEF<<", "; 
    cout<<sColorAncestor[Result[2].value%8]<<setw(7)<<Result[2].value<<" >"<<LBLU<<setw(2)<<Result[2].count<<CDEF<<", "; 
    cout<<sColorAncestor[Result[3].value%8]<<setw(7)<<Result[3].value<<" >"<<LPUR<<setw(2)<<Result[3].count<<CDEF<<", "; 
    cout<<"\n"; 
}

void Tribe::test()
{
    int loop = 0; 
    int sum = 0; 
    Elf *pElf = pHead; 

    if (pElf == NULL) return; 

    //pElf->printTitle(); 

    pElf = findNext(pElf); //the head always point to the last one, so shift one
    while (loop++ < count)
    {
        //cout<<(*pElf)<<"\n"; 
        sum+=pElf->getElements().gold + pElf->getElements().wood + pElf->getElements().dust + pElf->getElements().agua + pElf->getElements().fire; 
        pElf = findNext(pElf); 
    }
    cout<<"["<<setw(2)<<count<<", "<<setw(6)<<sum/count<<"]  "; 
}

void Tribe::buri()
{
    int loop = 0; 
    int countOld = count; 
    Elf *pElfCrn = NULL; 
    Elf *pElf = pHead; 

    if (pElf == NULL) return; 

    while (loop++ < countOld)
    {
        pElfCrn = pElf; 
        pElf = findNext(pElf); 

        pElfCrn->setActionNone();

        if (pElfCrn->getStatus() == DEATH)
        {
            remove(pElfCrn); 
            delete pElfCrn; 
        }
    }
}

void Tribe::insert(Elf *pElf)
{
    //cout<<"#1 insert"<<pElf->getIndex()<<"\n";
    if (count == 0)
    {
        pHead = pElf; 
        pElf->setPtrNext(pElf); //ring
        count++; 
    }
    else
    {
        Elf *pNext = pHead->getPtrNext(); 
        pHead->setPtrNext(pElf); 
        pElf->setPtrNext(pNext); 
        pHead = pElf; 
        count++; 
    }
}

void Tribe::remove(Elf *pElf)
{
    int loop = 0; 
    Elf *pCrnt = NULL; 
    Elf *pNext = NULL; 

    //cout<<"#2 remove"<<pElf->getIndex()<<"\n";

    if (count == 1)
    {
        pElf->setPtrNext(NULL); 
        pHead = NULL; 
        count--; 
        return; 
    }

    pCrnt = pHead; 
    while (loop++ < count)
    {
        pNext = pCrnt->getPtrNext(); 
        if (pNext == pElf)
        {
            pCrnt->setPtrNext(pNext->getPtrNext()); 
            pNext->setPtrNext(NULL); 
            count--; 
            break; 
        }
        pCrnt = pNext; 
    }
    if (pNext == pHead) 
    {
        pHead = pCrnt; 
    }
}

Elf *Tribe::findRand()
{
    int loop = 0; 
    Elf *pElf = pHead; 
    while (loop++ < (rand()%count))
    {
        pElf = pElf->getPtrNext(); 
    }
    return pElf; 
}

Elf *Tribe::findNext(Elf *pElf)
{
    return pElf->getPtrNext();  
}
