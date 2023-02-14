#include <stdio.h>
#include <string.h>
#include "bibliotheque.h"
#include <stdlib.h>


#define MAX_LIVRES 100
#define MAX_ADHERENTS 100


// Fonction principale
int main() {
    int choix, nb_livres = 0, nb_adherents = 0;
    livre livres[MAX_LIVRES];
    adherent adherents[MAX_ADHERENTS];

    do {
        // Afficher le menu
        printf("\nMenu :\n");
        printf("1. Ajouter un livre\n");
        printf("2. Emprunter un livre\n");
        printf("3. Retourner un livre\n");
        printf("4. Lister les adhérents\n");

        printf("5. Quitter\n");

        // Lire le choix de l'utilisateur
        printf("Entrez votre choix : ");
        scanf("%d", &choix);

        // Appeler la fonction correspondante
        switch (choix) {
            case 1:
                ajouter_livre(livres, &nb_livres);
                break;
            case 2:
                emprunter_livre(livres, nb_livres, adherents, &nb_adherents);
                break;
            case 3:
                retour_livre(livres, nb_livres, adherents, nb_adherents);
                break;

            case 4:
                lister_adherents(adherents, nb_adherents);
                break;

            case 5:
                printf("Au revoir !\n");
                break;

            default:
                printf("Choix invalide.\n");
        }
    } while (choix != 5);

    return 0;
}

