#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>
#include <string.h>
#include "../include/database.h"
#include "../include/parking.h"
#include "../include/vehicule.h"

Parking creerParking(int nbPlacesMoto, int nbPlacesVoiture, int nbPlacesCamion)
{
    Parking parking = {nbPlacesMoto, nbPlacesVoiture, nbPlacesCamion, "vehicule"};
    return parking;
}

void afficherCapaciteParking(Parking *parking)
{
    MYSQL *con = connectionBD();

    char requete[100];

    snprintf(requete, sizeof(requete), "select type, count(*) from %s group by type order by type", parking->nomTable);

    if (mysql_query(con, requete))
    {
        return erreurBD(con);
    }

    MYSQL_RES *result = mysql_store_result(con);

    if (result == NULL)
    {
        return erreurBD(con);
    }

    MYSQL_ROW row;

    // Respectivement : nbMoto, nbVoiture, nbCamion
    int places[3] = {0, 0, 0};
    int i = 0;

    while ((row = mysql_fetch_row(result)))
    {
        places[i] = row[1] ? atoi(row[1]) : 0;
        i++;
    }

    mysql_free_result(result);
    mysql_close(con);

    int nbMoto = places[0];
    int nbVoiture = places[1] <= parking->nbPlacesVoiture ? places[1] : parking->nbPlacesVoiture;
    int nbCamion = places[1] <= parking->nbPlacesVoiture ? places[2] : places[2] + places[1] - parking->nbPlacesVoiture;

    printf("Capacité du parking :\n");
    printf("Nombre de places pour moto : %d/%d (%.2f%%)\n", nbMoto, parking->nbPlacesMoto, (float)nbMoto / parking->nbPlacesMoto * 100);
    printf("Nombre de places pour voiture : %d/%d (%.2f%%)\n", nbVoiture, parking->nbPlacesVoiture, (float)nbVoiture / parking->nbPlacesVoiture * 100);
    printf("Nombre de places pour camion : %d/%d (%.2f%%)\n", nbCamion, parking->nbPlacesCamion, (float)nbCamion / parking->nbPlacesCamion * 100);
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
    printf("Vérification des places disponibles...\n");

    MYSQL *con = connectionBD();

    char requete[100];

    snprintf(requete, sizeof(requete), "select type, count(*) from %s group by type order by type", parking->nomTable);

    if (mysql_query(con, requete))
    {
        return erreurBD(con);
    }

    MYSQL_RES *result = mysql_store_result(con);

    if (result == NULL)
    {
        return erreurBD(con);
    }

    MYSQL_ROW row;

    // Respectivement : nbMoto, nbVoiture, nbCamion
    int places[3] = {0, 0, 0};
    int i = 0;

    while ((row = mysql_fetch_row(result)))
    {
        places[i] = row[1] ? atoi(row[1]) : 0;
        i++;
    }

    mysql_free_result(result);
    mysql_close(con);

    // Vérifier si le type de véhicule est valide
    if (vehicule->type < 1 || vehicule->type > 3)
    {
        printf("Type de véhicule invalide !\n");
        return;
    }
    // Vérifier si le parking est complet pour les motos
    else if (vehicule->type == 1 && places[0] >= parking->nbPlacesMoto)
    {
        printf("Le parking est complet !\n");
        return;
    }
    // Vérifier si le parking est complet pour les voitures ET les places de camions sont occupées à plus de 80%
    else if (vehicule->type == 2 && (places[1] >= parking->nbPlacesVoiture && places[2] + places[1] - parking->nbPlacesVoiture > parking->nbPlacesCamion * 0.8))
    {
        printf("Le parking est complet !\n");
        return;
    }
    // Vérifier si le parking est complet pour les camions, sachant que les places de camions peuvent être utilisées pour les voitures
    else if (vehicule->type == 3 && (places[2] >= parking->nbPlacesCamion || (places[1] > parking->nbPlacesVoiture && (places[1] - parking->nbPlacesVoiture + places[2]) >= parking->nbPlacesCamion)))
    {
        printf("Le parking est complet !\n");
        return;
    }

    printf("Stationnement du véhicule immatriculé %s...\n", vehicule->immatriculation);

    con = connectionBD();

    requete[100];

    snprintf(requete, sizeof(requete), "insert into `%s` (`immatriculation`, `type`) values ('%s', %d)", parking->nomTable, vehicule->immatriculation, vehicule->type);

    if (mysql_query(con, requete))
    {
        return erreurBD(con);
    }

    mysql_close(con);

    printf("Véhicule stationné avec succès !\n");
}

void libererPlace(Parking *parking)
{
    MYSQL *con = connectionBD();

    char requete[100];

    snprintf(requete, sizeof(requete), "select * from %s", parking->nomTable);

    if (mysql_query(con, requete))
    {
        return erreurBD(con);
    }

    MYSQL_RES *result = mysql_store_result(con);

    if (result == NULL)
    {
        return erreurBD(con);
    }

    int num_fields = mysql_num_fields(result);

    MYSQL_ROW row;

    printf("Véhicules stationnés :\n\n");
    printf(" ------------------------------------------- \n");
    printf("| ID | Immatriculation | Type | Stationné à |\n");
    printf(" ------------------------------------------- \n");

    while ((row = mysql_fetch_row(result)))
    {
        printf("| ");

        for (int i = 0; i < num_fields; i++)
        {
            printf("%s | ", row[i] ? row[i] : "NULL");
        }

        printf("\n");
    }

    printf(" ------------------------------------------- \n");

    mysql_free_result(result);

    // Récupérer l'ID du véhicule à retirer du parking

    int idVehicule;

    printf("Veuillez entrer l'ID du véhicule à rétirer du parking (0 : pour annuler) : ");
    scanf("%d", &idVehicule);

    if (idVehicule == 0)
    {
        return;
    }

    // Calculer le temps total passé dans le parking et retourner la facture

    snprintf(requete, sizeof(requete), "select type, heureArrivee from %s where id=%d", parking->nomTable, idVehicule);

    if (mysql_query(con, requete))
    {
        return erreurBD(con);
    }

    result = mysql_store_result(con);

    if (result == NULL)
    {
        return erreurBD(con);
    }

    int typeVehicule;
    char *heureArrivee;

    if (row = mysql_fetch_row(result))
    {
        typeVehicule = row[0] ? atoi(row[0]) : 0;
        heureArrivee = row[1] ? row[1] : NULL;
    }

    mysql_free_result(result);

    if (typeVehicule == 0 || heureArrivee == NULL)
    {
        printf("Véhicule introuvable !\n");
        return;
    }

    // snprintf(requete, sizeof(requete), "delete from `%s` where id = %d", parking->nomTable, idVehicule);

    // if (mysql_query(con, requete))
    // {
    //     return erreurBD(con);
    // }

    time_t maintenant = time(NULL);
    char heureSortie[20];
    strftime(heureSortie, 20, "%Y-%m-%d %H:%M:%S", localtime(&maintenant));

    struct tm tm;
    strptime(heureArrivee, "%Y-%m-%d %H:%M:%S", &tm);

    char buf[255];
    strftime(buf, sizeof(buf), "%d %b %Y %H:%M", &tm);
    puts(buf);

    // printf("Heure d'arrivée : %s\n", ctime(&tm));
    printf("Heure de sortie : %s\n", heureSortie);
    printf("Type de véhicule : %s\n", typeVehicule == 1 ? "Moto" : (typeVehicule == 2 ? "Voiture" : "Camion"));
    printf("À payer : 0 F CFA\n");

    mysql_close(con);
}
