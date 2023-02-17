#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "../include/parking.h"
#include "../include/vehicule.h"

int main(int argc, char *argv[])
{
    // Création d'un parking
    Parking parking = creerParking(5, 10, 5);

    // Déclaration de la variable de choix pour le menu
    int choice;

    // Affichage du menu
    printf("Bienvenue dans votre application de gestion de parking\n");

    while (1)
    {
        printf("\nQue voulez-vous faire ?\n");
        printf("1. Afficher la capacité du parking\n");
        printf("2. Stationner un véhicule\n");
        printf("3. Libérer une place et générer la facture\n");
        printf("4. Afficher les tarifs\n");
        printf("5. Quitter\n");
        printf("> ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice)
        {
        case 1:
            afficherCapaciteParking(&parking);
            break;

        case 2:
            Vehicule vehicule = creerVehicule();
            stationnerVehicule(&parking, &vehicule);
            break;

        case 3:
            libererPlace(&parking);
            break;

        case 4:
            afficherTarifs();
            break;

        case 5:
            printf("Au revoir !\n");
            exit(0);

        default:
            printf("Veuillez choisir une option dans la liste !\n");
            break;
        }
    }

    return 0;
}