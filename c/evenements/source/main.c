#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/database.h"
#include "../include/event.h"
#include "../include/menu.h"
#include "../include/schedule.h"
#include "../include/ticket.h"
#include "../include/utils.h"

int main(int argc, char *argv[])
{
    if (argc < 5)
    {
        printf("Veuillez renseigner les paramètres de connexion à la base de données comme argument !\n");
        printf("./evenements <hote> <utilisateur> <mdp> <nom>\n");
        printf("Exemple : ./evenements localhost root s3cr3t events\n");
        return 1;
    }

    char *hoteBD = argv[1];
    char *utilisateurBD = argv[2];
    char *mdpBD = argv[3];
    char *nomBD = argv[4];

    BD bd = {hoteBD, utilisateurBD, mdpBD, nomBD};

    // bool baseDeDonneesInitialisee = initBD(&bd);

    // if (!baseDeDonneesInitialisee)
    // {
    //     // Affichage d'un message d'erreur si les tables n'ont pas pu être créées ou si la connection à la base de données a échoué.
    //     // Ensuite arrêt du programme.
    //     printf("Erreur lors de l'initialisation de la base de données !\n");
    //     return 1;
    // }

    // Nettoyer la console lorsque tout s'est bien passé.
    printf("\e[1;1H\e[2J");

    // Déclaration de la variable de choix pour le menu
    char saisie[3];
    int choix;

    // Affichage du menu
    printf("Bienvenue dans votre application de gestion d'évènements !\n");

    while (1)
    {
        printf("\nVeuillez choisir un évènement dans la liste :\n");
        int nombreEvenements = afficherEvenements(&bd);
        printf("a. Ajouter un évènement\n");
        printf("q. Quitter\n");
        printf("> ");
        lire(saisie, sizeof(saisie));

        // Si l'utilisateur a saisi "a", on exécute la fonction de création d'évènement.
        if (saisie[0] == 'a')
        {
            printf("\nAjout d'un évènement\n");
            creerEvenement(&bd);
            continue;
        }
        // Si l'utilisateur a saisi "q", on quitte le programme, sinon on convertit la saisie en entier.
        else if (saisie[0] == 'q')
        {
            printf("\nAu revoir !\n");
            break;
        }
        else
        {
            choix = atoi(saisie);
        }

        // Le choix doit être compris entre 0 et le nombre d'évènements. Si ce n'est pas le cas, on affiche un message d'erreur.
        if (choix > 0 && choix <= nombreEvenements)
        {
            Evenement evenement = recupererEvenement(&bd, choix);

            if (evenement.id == 0)
            {
                printf("\nErreur lors de la récupération de l'évènement !\n");
                continue;
            }

            while (1)
            {
                printf("\nÉvènement : %s\n", evenement.titre);
                printf("Que voulez-vous faire ?\n");
                printf("1. Voir le menu\n");
                printf("2. Ajouter un plat au menu\n");
                printf("3. Voir le programme\n");
                printf("4. Ajouter une séance au programme\n");
                printf("5. Vendre un ticket\n");
                printf("6. Retour\n");
                printf("> ");
                lire(saisie, sizeof(saisie));
                choix = atoi(saisie);
                printf("\n");

                switch (choix)
                {
                case 1:
                    afficherMenu(&bd, evenement.id);
                    continue;

                case 2:
                    Menu menu = recupererMenu(&bd, evenement.id);
                    ajouterPlat(&bd, menu.id);
                    continue;

                case 3:
                    afficherProgramme(&bd, evenement.id);
                    continue;

                case 4:
                    ajouterSeance(&bd, evenement.id);
                    continue;

                case 5:
                    afficherProgramme(&bd, evenement.id);
                    printf("Veuillez choisir une séance dans la liste :\n");
                    printf("> ");
                    lire(saisie, sizeof(saisie));
                    choix = atoi(saisie);
                    printf("\n");
                    vendreTicket(&bd, choix);
                    continue;

                case 6:
                    break;

                default:
                    printf("Veuillez choisir une option dans la liste !\n");
                    continue;
                }

                break;
            }
        }
        else
        {
            printf("Veuillez choisir une option dans la liste !\n");
            continue;
        }
    }

    return 0;
}