#include <stdio.h>
#include <stdlib.h>
#include "../include/vehicule.h"

Vehicule creerVehicule()
{
    Vehicule vehicule;
    Vehicule *pointeur = &vehicule;

    printf("Renseignez les informations du véhicule :\n");
    printf("Type de véhicule (1 = moto, 2 = voiture, 3 = camion) : ");
    scanf("%d", &pointeur->type);
    printf("Immatriculation (ex : 1234AB12) : ");
    scanf("%s", pointeur->immatriculation);
    return vehicule;
}