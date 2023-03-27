#ifndef EVENT_H
#define EVENT_H

#include "database.h"

typedef struct Evenement Evenement;
typedef struct TypeEvenement TypeEvenement;

struct Evenement
{
    int id;
    char titre[256];
    int nbPlaces;
    int typeId;
};

struct TypeEvenement
{
    int id;
    char libelle[256];
};

Evenement creerEvenementNull();
Evenement creerEvenement(BD *);
Evenement recupererEvenement(BD *, int);
void afficherTypeEvenement(BD *);
int afficherEvenements(BD *);

#endif
