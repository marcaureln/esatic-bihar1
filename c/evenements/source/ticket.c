#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "../include/database.h"
#include "../include/ticket.h"

void vendreTicket(BD *bd, int idSeance)
{
    Ticket ticket;
    Ticket *p_ticket = &ticket;
    p_ticket->idSeance = idSeance;

    printf("\nEnregistrement de la vente en cours...\n");

    MYSQL *con = connectionBD(bd->hote, bd->utilisateur, bd->mdp, bd->nom);

    if (con == NULL)
    {
        printf("Erreur lors de la création de la vente !\n");
        return;
    }

    char requete[128];

    // Insertion de la vente dans la base de données.
    if (0 > snprintf(requete, sizeof(requete), "INSERT INTO evenements.ticket(`idSeance`) VALUES (%d)", p_ticket->idSeance))
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
            printf("La vente a bien été enrégistrée !\n");
        }
    }

    mysql_close(con);
}