#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "../include/utils.h"
#include "../include/database.h"
#include "../include/schedule.h"
#include "../include/event.h"

void afficherProgramme(BD *bd, int evenementId)
{
    Evenement evenement = recupererEvenement(bd, evenementId);

    MYSQL *con = connectionBD(bd->hote, bd->utilisateur, bd->mdp, bd->nom);

    char requete[256];

    if (0 > snprintf(requete, sizeof(requete), "SELECT seance.id, DATE_FORMAT(date, '%%d/%%m/%%Y'), COUNT(ticket.id) FROM seance LEFT OUTER JOIN ticket ON ticket.seanceId = seance.id WHERE evenementId = %d GROUP BY seance.id", evenementId))
    {
        printf("Erreur lors du formatage de la requête !\n");
        return;
    }

    printf("%s\n", requete);

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

            printf("Programme :\n");

            while ((row = mysql_fetch_row(result)))
            {
                printf("%s. %s (capacité: %s/%d)\n", row[0], row[1], row[2], evenement.nbPlaces);
            }

            mysql_free_result(result);
        }

        mysql_close(con);
    }
}

void ajouterSeance(BD *bd, int evenementId)
{
    Seance seance;
    Seance *p_seance = &seance;
    p_seance->evenementId = evenementId;
    printf("Ajout d'une séance au programme\n");
    printf("Date (JJ/MM/AAAA) : ");
    lire(p_seance->date, sizeof(p_seance->date));

    printf("\nEnregistrement de la séance en cours...\n");

    MYSQL *con = connectionBD(bd->hote, bd->utilisateur, bd->mdp, bd->nom);

    if (con == NULL)
    {
        printf("Erreur lors de la création de la séance !\n");
        return;
    }

    char requete[128];

    // Insertion de la séance dans la base de données
    if (0 > snprintf(requete, sizeof(requete), "INSERT INTO evenements.seance(`date`, `evenementId`) VALUES (STR_TO_DATE('%s', '%%d/%%m/%%Y'), %d)", p_seance->date, p_seance->evenementId))
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
            printf("La séance a bien été créé !\n");
        }
    }

    mysql_close(con);
}
