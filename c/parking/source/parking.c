#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <mysql/mysql.h>
#include "../include/parking.h"
#include "../include/vehicule.h"

Parking creerParking(int nbPlacesMoto, int nbPlacesVoiture, int nbPlacesCamion)
{
    Parking parking = {nbPlacesMoto, nbPlacesVoiture, nbPlacesCamion, "vehicule"};
    return parking;
}

void afficherCapaciteParking(Parking *parking)
{
    // À faire : Récupérer les véhicules présent dans le parking via la base de données
    printf("Capacité du parking :\n");
    printf("Nombre de places pour moto : 0/%d\n", parking->nbPlacesMoto);
    printf("Nombre de places pour voiture : 0/%d\n", parking->nbPlacesVoiture);
    printf("Nombre de places pour camion : 0/%d\n", parking->nbPlacesCamion);
}

void afficherTarifs()
{
    printf("Tarifs :\n");
    printf("Moto : 200 FCFA/h\n");
    printf("Voiture : 500 FCFA/h\n");
    printf("Camion : 1000 FCFA/h\n");
}

void stationnerVehicule(Parking *parking, Vehicule *vehicule)
{
    // À faire : Vérifier les places disponibles

    printf("Stationnement du véhicule immatriculé %s...\n", vehicule->immatriculation);

    MYSQL *con = mysql_init(NULL);

    // S'assurer que la fonction mysql_init s'est bien exécutée
    if (con == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        return;
    }

    // Connection à la base de données
    if (!mysql_real_connect(con, "db", "root", "example", "parking", 0, NULL, 0))
    {
        printf("Impossible de se connecter à la base de données. Erreur: %s\n", mysql_error(con));
        return;
    }

    // Insertion d'un véhicule dans la base de données
    char requete[100];

    sprintf(requete, "insert into `%s` (`immatriculation`, `type`) values ('%s', %d)", parking->nomTable, vehicule->immatriculation, vehicule->type);

    if (mysql_query(con, requete))
    {
        printf("Impossible d'exécuter cette requête. Erreur: %s\n", mysql_error(con));
        return;
    }

    mysql_close(con);

    printf("Véhicule stationné avec succès !");
}

void libererPlace(Parking *parking)
{
    // À faire : Afficher tout les véhicules présents et selectionner par son ID le véhicule à rétiter
    // À faire : Rétirer le véhicule de la base données
    // À faire : Calculer le temps total passé dans le parking et retourner la facture
}