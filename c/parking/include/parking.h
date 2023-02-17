#ifndef PARKING_H
#define PARKING_H

#include "vehicule.h"

typedef struct Parking Parking;

struct Parking
{
    int nbPlacesMoto;
    int nbPlacesVoiture;
    int nbPlacesCamion;
    char nomTable[20];
};

Parking creerParking(int, int, int);
void afficherCapaciteParking(Parking *);
void afficherTarifs();
void stationnerVehicule(Parking *, Vehicule *);
void libererPlace(Parking *);

#endif