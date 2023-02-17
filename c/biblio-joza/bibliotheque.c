#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bibliotheque.h"
#define MAX_LIVRES 100
#define MAX_ADHERENTS 100
void ajouter_livre(livre livres[], int *nb_livres) {
    if (*nb_livres == MAX_LIVRES) {
        printf("La biblioth�que est pleine.\n");
        return;
    }

    printf("Titre du livre : ");
    scanf(" %[^\n]", livres[*nb_livres].titre);
    printf("Auteur du livre : ");
    scanf(" %[^\n]", livres[*nb_livres].auteur);
    livres[*nb_livres].disponible = 1;

    printf("Le livre %s a �t� ajout�.\n", livres[*nb_livres].titre);

    *nb_livres += 1;
}

void emprunter_livre(livre livres[], int nb_livres, adherent adherents[], int *nb_adherents) {
    int i, choix;
    char nom_adherent[100], prenom_adherent[100];

    // Afficher la liste des livres disponibles
    printf("Livres disponibles :\n");
    for (i = 0; i < nb_livres; i++) {
        if (livres[i].disponible) {
            printf("%d. %s (%s)\n", i+1, livres[i].titre, livres[i].auteur);
        }
    }

    // Demander � l'utilisateur de choisir un livre
    do {
        printf("Choisissez un livre : ");
        scanf("%d", &choix);
        choix--;
    } while (choix < 0 || choix >= nb_livres || !livres[choix].disponible);

    // Marquer le livre comme emprunt�
    livres[choix].disponible = 0;


    // Demander � l'utilisateur son nom et pr�nom
    printf("Nom de l'adh�rent : ");
    scanf(" %[^\n]", nom_adherent);
    printf("Pr�nom de l'adh�rent : ");
    scanf(" %[^\n]", prenom_adherent);

    // Ajouter l'adh�rent � la liste si n�cessaire
    for (i = 0; i < *nb_adherents; i++) {
        if (strcmp(adherents[i].nom, nom_adherent) == 0 && strcmp(adherents[i].prenom, prenom_adherent) == 0) {
            break;
        }
    }
    if (i == *nb_adherents) {
        strcpy(adherents[i].nom, nom_adherent);
        strcpy(adherents[i].prenom, prenom_adherent);
        adherents[i].livre_emprunte=&livres[choix];
        *nb_adherents += 1;
    }

    // Afficher un message de confirmation
    printf("Le livre %s a �t� emprunt� par %s %s.\n", livres[choix].titre, nom_adherent, prenom_adherent);
}

void retour_livre(livre livres[], int nb_livres, adherent adherents[], int nb_adherents) {
    int i, choix;
    char nom_adherent[100], prenom_adherent[100];

    // Demander � l'utilisateur de choisir un livre
    printf("Livres emprunt�s :\n");
    for (i = 0; i < nb_livres; i++) {
        if (!livres[i].disponible) {
            printf("%d. %s (%s)\n", i+1, livres[i].titre, livres[i].auteur);
        }
    }
    do {
        printf("Choisissez un livre : ");
        scanf("%d", &choix);
        choix--;
    } while (choix < 0 || choix >= nb_livres || livres[choix].disponible);

    // Demander � l'utilisateur son nom et pr�nom
    printf("Nom de l'adh�rent : ");
    scanf(" %[^\n]", nom_adherent);
    printf("Pr�nom de l'adh�rent : ");
    scanf(" %[^\n]", prenom_adherent);

    // V�rifier si l'adh�rent a bien emprunt� ce livre
    for (i = 0; i < nb_adherents; i++) {
        if (strcmp(adherents[i].nom, nom_adherent) == 0 && strcmp(adherents[i].prenom, prenom_adherent) == 0) {
                printf("adh�rent trouver");
            if (adherents[i].livre_emprunte == &livres[choix]) {
                adherents[i].livre_emprunte = NULL;
                livres[choix].disponible = 1;
                printf("Le livre %s a �t� retourn� par %s %s.\n", livres[choix].titre, nom_adherent, prenom_adherent);
                return;
            }
        }
    }

    // Si on arrive ici, l'adh�rent n'a pas emprunt� ce livre
    printf("%s %s n'a pas emprunt� le livre %s.\n", nom_adherent, prenom_adherent, livres[choix].titre);
}

void lister_adherents(adherent adherents[], int nb_adherents) {
    int i;

    printf("Liste des adh�rents :\n");
    for (i = 0; i < nb_adherents; i++) {
        printf("%s %s\n", adherents[i].nom, adherents[i].prenom);
    }
}
