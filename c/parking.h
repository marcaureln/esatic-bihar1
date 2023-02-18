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
int is_space_available(int type);
double occupancy_rate_by_type(int vehicule_type);
int calculate_parking_cost(const char* immatriculation);
void print_invoice(Vehicule *v, int cost);
void delete_vehicle_by_registration(MYSQL* conn, const char* immatriculation);
Vehicule* get_vehicle_data(MYSQL_ROW row);


#endif