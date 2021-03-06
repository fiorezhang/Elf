#ifndef CLASS_ELF_H
#define CLASS_ELF_H

#include "defines.h"

using namespace std;

typedef struct _Power
{
    int health;
    int energy;
}Power;

typedef struct _Element
{
    int gold; 
    int wood; 
    int dust; 
    int agua; 
    int fire; 
}Element; 

typedef struct _Ancestor
{
    int idPaPa; 
    int idPaMa; 
    int idMaPa; 
    int idMaMa; 
    int idPa; 
    int idMa;
    int idI; 
}Ancestor;

typedef struct _Point
{
    int pointNow;
    int pointAll;
}Point;

typedef enum _Status
{
    PUPAE, 
    YOUNG, 
    ADULT, 
    DEATH
}Status; 

typedef enum _Action
{
    NONE, 
    MATE, 
    DING
}Action;


class Elf
{
    friend ostream &operator<<(ostream &, const Elf &);
public:
    Elf(const char *, const bool, const int, const int, const int, const int, const int, const int);
    Elf(Elf &, Elf &);
    ~Elf();

    int getIndex() const { return index; }
    char *getName() const { return name; }
    bool getGender() const { return gender; }
    Action getAction() const { return action; }
    void setActionMate() { action = MATE; }
    void setActionNone() { action = NONE; }
    Status getStatus() const { return status; }
    void setPoint(Point);
    void addPoint() { points.pointNow++; points.pointAll++;}
    Point getPoint() const { return points; }

    Power getPowers() const { return powers; }
    Element getElements() const { return elements; }
    int getAge() const { return age; }
    int getKid() const { return kid; }
    void addKid() { kid++; }
    Ancestor getAncestors() const { return ancestors; }

    void setNameTribe(const char*);

    void ding();
    void grow();

    //Elf *getPtrLast() const { return pLast; }
    Elf *getPtrNext() const { return pNext; }
    //void setPtrLast(Elf * pE) { pLast = pE; }
    void setPtrNext(Elf * pE) { pNext = pE; }

    static void printTitle(); 
private:
    static int idCount;
    int index; 
    char *name; 
    bool gender; 
    int age;
    int kid; 
    Power powers;
    Element elements; 
    Element genetics; 
    Ancestor ancestors;
    Action action; 
    Status status; 
    Point points;

    //Elf *pLast;
    Elf *pNext;

    char *nameTribe;
};

#endif//CLASS_ELF_H
