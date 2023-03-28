#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "database.h"

typedef struct Seance Seance;

struct Seance
{
    int id;
    char date[11]; // Format : JJ/MM/AAAA
    int idEvenement;
};

void afficherProgramme(BD *, int);
void ajouterSeance(BD *, int);

#endif