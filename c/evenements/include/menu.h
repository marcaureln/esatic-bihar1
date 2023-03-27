#ifndef MENU_H
#define MENU_H

#include "database.h"

typedef struct Menu Menu;
typedef struct Plat Plat;

struct Menu
{
    int id;
    char titre[256];
    int evenementId;
};

struct Plat
{
    int id;
    char nom[256];
    int prix;
    int menuId;
};

void ajouterPlat(BD *, int);
void afficherPlats(BD *, int);
void afficherMenu(BD *, int);
Menu recupererMenu(BD *, int);

#endif