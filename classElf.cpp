#include <iostream>
#include <iomanip>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "color.h"
#include "classElf.h"

#define DEBUG_PRINT

int Elf::idCount = 1;
////
static char *getRandName()
{
    static char cPoolFirst[] = { 'B', 'C', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'P', 'R', 'S', 'T', 'V', 'W', 'Y', 'Z' }; 
    static char cPoolSecond[]= { 'a', 'e', 'i', 'o', 'u' };
    static char cPoolThird[] = { 'b', 'c', 'd', 'f', 'g', 'k', 'l', 'm', 'n', 'p', 'r', 's', 't', 'v', 'x', 'z' };

    char *pName = new char[4];
    pName[0] = cPoolFirst[rand()%sizeof(cPoolFirst)]; 
    pName[1] = cPoolSecond[rand()%sizeof(cPoolSecond)]; 
    pName[2] = cPoolThird[rand()%sizeof(cPoolThird)];
    pName[3] = '\0'; 

    return pName; 
}
////

static const string sAction[] = { "N", "M", "D" };
static const string sStatus[] = { "P", "Y", "A", "D" };
static const string sColorAction[] = { LBLA, LYEL, LGRE };
static const string sColorStatus[] = { LBLA, LPUR, LBLU, LRED };
static const string sColorValue[] = { LBLA, LCYA, LPUR, LYEL, LRED };
static const string sColorAncestor[] = { LBLA, LRED, LGRE, LYEL, LBLU, LPUR, LCYA, LWHI }; 
static const string sColorPoint[] = { LBLA, LCYA, LPUR, LYEL, LRED };

static int maxPointNow = 2 * (MAXIM_POPULATION - 1);
static int maxPointAll = MAXIM_AGE * maxPointNow;

ostream &operator<<(ostream &output, const Elf &elf)
{
    int elements = elf.elements.gold+elf.elements.wood+elf.elements.dust+elf.elements.agua+elf.elements.fire;

    output<<((elf.gender)?LYEL:LGRE)<<setw(7)<<elf.index
          <<setw(5)<<elf.name
          <<setw(4)<<elf.nameTribe
          <<setw(3)<<((elf.gender)?"M":"F")<<CDEF
          <<((elf.age>=20)?sColorValue[4]:sColorValue[elf.age/5])<<setw(3)<<elf.age<<CDEF 
          <<((elf.kid>=7)?sColorValue[4]:sColorValue[(elf.kid+1)/2])<<setw(3)<<elf.kid<<CDEF
          <<sColorValue[(elements-1)/MAXIM_VALUE]<<setw(5)<<elements<<CDEF 
          <<((elf.points.pointAll>=maxPointAll/2)?sColorPoint[4]:sColorPoint[elf.points.pointAll*8/maxPointAll])<<setw(5)<<elf.points.pointAll<<CDEF
          <<((elf.points.pointNow>=maxPointNow)?sColorPoint[4]:sColorPoint[elf.points.pointNow*4/maxPointNow])<<setw(4)<<elf.points.pointNow<<CDEF;
    output<<"  |  ";
    output<<sColorValue[elf.elements.gold*4/MAXIM_VALUE]<<setw(5)<<elf.elements.gold<<CDEF
          <<sColorValue[elf.elements.wood*4/MAXIM_VALUE]<<setw(5)<<elf.elements.wood<<CDEF
          <<sColorValue[elf.elements.dust*4/MAXIM_VALUE]<<setw(5)<<elf.elements.dust<<CDEF
          <<sColorValue[elf.elements.agua*4/MAXIM_VALUE]<<setw(5)<<elf.elements.agua<<CDEF
          <<sColorValue[elf.elements.fire*4/MAXIM_VALUE]<<setw(5)<<elf.elements.fire<<CDEF;
    output<<"  |  ";
    output<<setw(5)<<elf.powers.health
          <<setw(5)<<elf.powers.energy;
    output<<"  |  ";
    output<<sColorAction[elf.action]<<setw(3)<<sAction[elf.action]<<CDEF
          <<sColorStatus[elf.status]<<setw(3)<<sStatus[elf.status]<<CDEF;
#ifdef DEBUG_PRINT
    output<<"  |  ";
    output<<sColorAncestor[elf.ancestors.idPaPa%8]<<setw(7)<<elf.ancestors.idPaPa<<CDEF
          <<sColorAncestor[elf.ancestors.idPaMa%8]<<setw(7)<<elf.ancestors.idPaMa<<CDEF
          <<sColorAncestor[elf.ancestors.idMaPa%8]<<setw(8)<<elf.ancestors.idMaPa<<CDEF
          <<sColorAncestor[elf.ancestors.idMaMa%8]<<setw(7)<<elf.ancestors.idMaMa<<CDEF
          <<sColorAncestor[elf.ancestors.idPa%8]<<setw(8)<<elf.ancestors.idPa<<CDEF
          <<sColorAncestor[elf.ancestors.idMa%8]<<setw(7)<<elf.ancestors.idMa<<CDEF
          <<sColorAncestor[elf.ancestors.idI%8]<<setw(8)<<elf.ancestors.idI<<CDEF;
#endif
    return output; 
}

void Elf::printTitle()
{
    cout  <<LWHI<<setw(7)<<"Index"
          <<setw(5)<<"Name"
          <<setw(4)<<"Trb"
          <<setw(3)<<"MF"
          <<setw(3)<<"Ag"
          <<setw(3)<<"Kd" 
          <<setw(5)<<"Elem"<<CDEF
          <<setw(5)<<"All"<<CDEF
          <<setw(4)<<"Now"<<CDEF;
    cout  <<"  |  ";
    cout  <<LYEL<<setw(5)<<"Gold"<<CDEF
          <<LGRE<<setw(5)<<"Wood"<<CDEF
          <<LBLA<<setw(5)<<"Dust"<<CDEF
          <<LBLU<<setw(5)<<"Agua"<<CDEF
          <<LRED<<setw(5)<<"Fire"<<CDEF;
    cout  <<"  |  ";
    cout  <<setw(5)<<"Hea"
          <<setw(5)<<"Eng";
    cout  <<"  |  ";
    cout  <<LWHI<<setw(3)<<"Ac"
          <<setw(3)<<"St"<<CDEF;
#ifdef DEBUG_PRINT
    cout  <<"  |  ";
    cout  <<LCYA<<setw(7)<<"Pa-Pa"<<CDEF
          <<LYEL<<setw(7)<<"Pa-Ma"<<CDEF
          <<LGRE<<setw(8)<<"Ma-Pa"<<CDEF
          <<LPUR<<setw(7)<<"Ma-Ma"<<CDEF
          <<LBLU<<setw(8)<<"Pa"<<CDEF
          <<LRED<<setw(7)<<"Ma"<<CDEF
          <<LWHI<<setw(8)<<"Self"<<CDEF;
#endif
    cout  <<"\n"; 
}

// create an elf with dedicated parameters
Elf::Elf(const char *n, const bool m, const int y, const int g, const int w, const int d, const int a, const int f)
{
    index = idCount;

    if (strlen(n))
    {
        name = new char[strlen(n) + 1];
        strcpy(name, n);
    }
    else
    {
        name = getRandName();
    }

    nameTribe = new char[1];
    gender = m; 
    age = y; 
    kid = 0; 

    powers.health = COMBAT_HEALTH_ELF;
    powers.energy = COMBAT_ENERGY_ELF;

    elements.gold = g; 
    elements.wood = w; 
    elements.dust = d; 
    elements.agua = a; 
    elements.fire = f; 

    ancestors.idPaPa = ancestors.idPaMa = ancestors.idMaPa = ancestors.idMaMa = ancestors.idPa = ancestors.idMa = 0; 
    ancestors.idI = index; 

    action = NONE; 
    status = age<YOUNG_AGE?PUPAE:age<ADULT_AGE?YOUNG:ADULT;  

    points.pointNow = 0;
    points.pointAll = 0;

    ++idCount;
}

static int getDeltaGenetic(int valPa, int valMa, Status stsPa, Status stsMa)
{
    int delPa = (valPa - BASIC_VALUE);
    int delMa = (valMa - BASIC_VALUE); 

    if (stsPa == YOUNG && stsMa == YOUNG)
    {
        return (rand()%2)?delPa:delMa;
    }
    else if (stsPa == YOUNG && stsMa == ADULT)
    {
        return delMa; 
    }
    else if (stsPa == ADULT && stsMa == YOUNG)
    {
        return delPa; 
    }
    else if (stsPa == ADULT && stsMa == ADULT)
    {
        return max(delPa, delMa);
    }
    else //should not get here
    {
        return 0; 
    }
}

// create an elf from parents
Elf::Elf(Elf &elfPa, Elf &elfMa)
{
    index = idCount; 
    
    name = getRandName();
    nameTribe = new char[1];

    gender = (rand() % 2 == 0)?false:true; 
    age = 0;
    kid = 0; 

    powers.health = COMBAT_HEALTH_ELF;
    powers.energy = COMBAT_ENERGY_ELF;
    ////
    elements.gold = elements.wood = elements.dust = elements.agua = elements.fire = BASIC_VALUE; 
    genetics.gold = getDeltaGenetic(elfPa.getElements().gold, elfMa.getElements().gold, elfPa.getStatus(), elfMa.getStatus()); 
    genetics.wood = getDeltaGenetic(elfPa.getElements().wood, elfMa.getElements().wood, elfPa.getStatus(), elfMa.getStatus()); 
    genetics.dust = getDeltaGenetic(elfPa.getElements().dust, elfMa.getElements().dust, elfPa.getStatus(), elfMa.getStatus()); 
    genetics.agua = getDeltaGenetic(elfPa.getElements().agua, elfMa.getElements().agua, elfPa.getStatus(), elfMa.getStatus()); 
    genetics.fire = getDeltaGenetic(elfPa.getElements().fire, elfMa.getElements().fire, elfPa.getStatus(), elfMa.getStatus()); 
    ////
    elfPa.setActionMate(); elfPa.addKid(); 
    elfMa.setActionMate(); elfMa.addKid(); 

    ////
    ancestors.idPaPa = elfPa.getAncestors().idPa;
    ancestors.idPaMa = elfPa.getAncestors().idMa;
    ancestors.idMaPa = elfMa.getAncestors().idPa;
    ancestors.idMaMa = elfMa.getAncestors().idMa;
    ancestors.idPa   = elfPa.getIndex();
    ancestors.idMa   = elfMa.getIndex();
    ancestors.idI    = index; 
    ////

    action = NONE; 
    status = PUPAE;  

    points.pointNow = 0;
    points.pointAll = 0;

    ++idCount; 
}

Elf::~Elf()
{
    if (!name) 
        delete []name;
    if (!nameTribe)
        delete []nameTribe;
}

static int fuzzyNum(int num, int div)
{
    return num + num/div - rand()%(num*2/div+1); 
}

void Elf::setNameTribe(const char* n) 
{ 
    if (!nameTribe)
        delete []nameTribe;
    nameTribe = new char[strlen(n) + 1]; 
    strcpy(nameTribe, n);
}

void Elf::setPoint(Point p)
{
    points = p;
}

void Elf::ding()
{
    int *pElement = (int *)(&elements); 
    int *pGenetic = (int *)(&genetics);

    int genetic_deno = ODD_GENETIC_DENO; 
    int genetic_mole = ODD_GENETIC_MOLE; 

    if (status == PUPAE)
    {
        for (int i=0; i<NUM_ELEMENTS; i++)
        {
            if (rand()%genetic_deno < genetic_mole) // the odd the pupae get a growth from the genetic
                pElement[i] += fuzzyNum((pGenetic[i] / YOUNG_AGE), FUZZY_DING);
        }
    }
    else if (status == YOUNG)
    {
        pElement[rand()%NUM_ELEMENTS] += fuzzyNum(YOUNG_VALUE, FUZZY_DING);
    }
    else if (status == ADULT)
    {
        int maxEle = 0; 
        int cntEle = 0; 
        for (int i=0; i<NUM_ELEMENTS; i++)
        {
            if (pElement[i] > maxEle)
            {
                maxEle = pElement[i]; 
                cntEle = i; 
            }
            if (pElement[i] == maxEle && rand()%2)
                cntEle = i; 
        }
        int j = 7; // try to find a non-max parameter to ding
        while (pElement[cntEle] == MAXIM_VALUE && j--)
            cntEle = rand()%NUM_ELEMENTS;


        pElement[cntEle] += fuzzyNum(ADULT_VALUE, FUZZY_DING);

        pElement[rand()%NUM_ELEMENTS] += fuzzyNum(YOUNG_VALUE, FUZZY_DING);
    }

    for (int i=0; i<NUM_ELEMENTS; i++)
    {
        if (pElement[i] > MAXIM_VALUE)
            pElement[i] = MAXIM_VALUE; 
    }

    action = DING; 
}

void Elf::grow()
{
    if (age < YOUNG_AGE)
    {
        age++;
    }
    else if (age < ADULT_AGE)
    {
        status = YOUNG; 
        if (rand()%(MAXIM_AGE-YOUNG_AGE) + YOUNG_AGE < age)
            status = DEATH; 
        age++;
    }
    else
    {
        status = ADULT; 
        if (rand()%(MAXIM_AGE-ADULT_AGE) + ADULT_AGE < age)
            status = DEATH; 
        age++;
    }
}
