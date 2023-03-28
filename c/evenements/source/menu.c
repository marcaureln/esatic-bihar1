#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "../include/menu.h"
#include "../include/utils.h"
#include "../include/database.h"

/// @brief Ajoute un plat au menu.
/// @param bd
/// @param idMenu
void ajouterPlat(BD *bd, int idMenu)
{
    Plat plat;
    Plat *p_plat = &plat;
    p_plat->idMenu = idMenu;
    printf("Ajout d'un plat au menu\n");
    printf("Nom : ");
    lire(p_plat->nom, 256);
    printf("Prix : ");
    char saisiePrix[10];
    lire(saisiePrix, sizeof(saisiePrix));
    p_plat->prix = atoi(saisiePrix);

    printf("\nEnregistrement du plat en cours...\n");

    MYSQL *con = connectionBD(bd->hote, bd->utilisateur, bd->mdp, bd->nom);

    if (con == NULL)
    {
        printf("Erreur lors de la création du plat !\n");
        return;
    }

    char requete[384];

    // Insertion du plat dans la base de données
    if (0 > snprintf(requete, sizeof(requete), "INSERT INTO evenements.plat(`nom`, `prix`, `idMenu`) VALUES (\"%s\", %d, %d)", p_plat->nom, p_plat->prix, p_plat->idMenu))
    {
        printf("Erreur lors du formatage de la requête !\n");
    }
    else
    {
        if (mysql_query(con, requete))
        {
            printf("Erreur lors de l'insertion dans la base de données !\n");
            erreurBD(con);
        }
        else
        {
            printf("Le plat a bien été créé !\n");
        }
    }

    mysql_close(con);
}

/// @brief Affiche les plats d'un menu.
/// @param bd
/// @param idMenu
void afficherPlats(BD *bd, int idMenu)
{
    MYSQL *con = connectionBD(bd->hote, bd->utilisateur, bd->mdp, bd->nom);

    char requete[128];

    if (0 > snprintf(requete, sizeof(requete), "SELECT nom, prix FROM evenements.plat WHERE idMenu = %d", idMenu))
    {
        printf("Erreur lors du formatage de la requête !\n");
        return;
    }

    // S'assurer que la connection à la base de données s'est bien exécutée
    if (con == NULL)
    {
        printf("Erreur lors de la connection à la base de données !\n");
    }
    else
    {
        if (mysql_query(con, requete))
        {
            erreurBD(con);
        }
        else
        {
            MYSQL_RES *result = mysql_store_result(con);

            if (result == NULL)
            {
                erreurBD(con);
            }

            MYSQL_ROW row;

            while ((row = mysql_fetch_row(result)))
            {
                printf("* %s (%s F CFA)\n", row[0], row[1]);
            }

            mysql_free_result(result);
        }

        mysql_close(con);
    }
}

/// @brief Réccupère le menu d'un évènement.
/// @param bd
/// @param idEvenement
/// @return Menu
Menu recupererMenu(BD *bd, int idEvenement)
{
    Menu menu = {0, "", idEvenement};
    Menu *p_menu = &menu;

    MYSQL *con = connectionBD(bd->hote, bd->utilisateur, bd->mdp, bd->nom);

    char requete[128];

    if (0 > snprintf(requete, sizeof(requete), "SELECT id, titre FROM evenements.menu WHERE idEvenement = %d", idEvenement))
    {
        printf("Erreur lors du formatage de la requête !\n");
        return menu;
    }

    // S'assurer que la connection à la base de données s'est bien exécutée
    if (con == NULL)
    {
        printf("Erreur lors de la connection à la base de données !\n");
    }
    else
    {
        if (mysql_query(con, requete))
        {
            erreurBD(con);
        }
        else
        {
            MYSQL_RES *result = mysql_store_result(con);

            if (result == NULL)
            {
                erreurBD(con);
            }

            MYSQL_ROW row = row = mysql_fetch_row(result);

            if (row)
            {
                p_menu->id = atoi(row[0]);
                strcpy(p_menu->titre, row[1]);
            }

            mysql_free_result(result);
        }

        mysql_close(con);
    }

    return menu;
}

/// @brief Affiche le menu d'un évènement.
/// @param bd
/// @param idEvenement
void afficherMenu(BD *bd, int idEvenement)
{
    MYSQL *con = connectionBD(bd->hote, bd->utilisateur, bd->mdp, bd->nom);

    char requete[128];

    if (0 > snprintf(requete, sizeof(requete), "SELECT id, titre FROM evenements.menu WHERE idEvenement = %d", idEvenement))
    {
        printf("Erreur lors du formatage de la requête !\n");
        return;
    }

    // S'assurer que la connection à la base de données s'est bien exécutée
    if (con == NULL)
    {
        printf("Erreur lors de la connection à la base de données !\n");
    }
    else
    {
        if (mysql_query(con, requete))
        {
            erreurBD(con);
        }
        else
        {
            MYSQL_RES *result = mysql_store_result(con);

            if (result == NULL)
            {
                erreurBD(con);
            }

            MYSQL_ROW row = row = mysql_fetch_row(result);

            if (row)
            {
                printf("%s :\n", row[1]);
                afficherPlats(bd, atoi(row[0]));
                printf("\n", row[1]);
            }

            mysql_free_result(result);
        }

        mysql_close(con);
    }
}
