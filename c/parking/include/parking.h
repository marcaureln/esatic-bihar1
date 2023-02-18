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
void afficherTarifs();
void afficherCapaciteParking(Parking *);
void stationnerVehicule(Parking *, Vehicule *);
void libererPlace(Parking *);

#endif