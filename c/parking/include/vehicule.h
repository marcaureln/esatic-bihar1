#ifndef VEHICULE_H
#define VEHICULE_H

typedef struct Vehicule Vehicule;

struct Vehicule
{
    int type;
    // Les plaques d'immatriculation Ivoiriennes, sont composées de 4 chiffres, 2 lettres et de 2 chiffres.
    // Exemple : 1234-AB-12
    char immatriculation[9];
};

Vehicule creerVehicule();

#endif
