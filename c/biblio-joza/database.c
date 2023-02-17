#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "database.h"
#include "bibliotheque.h"

MYSQL *connect_to_database(const char *host, const char *user, const char *password, const char *database)
{
    MYSQL *conn = mysql_init(NULL);

    if (conn == NULL)
    {
        fprintf(stderr, "Error initializing MySQL: %s\n", mysql_error(conn));
        return NULL;
    }

    if (mysql_real_connect(conn, host, user, password, database, 0, NULL, 0) == NULL)
    {
        fprintf(stderr, "Error connecting to database: %s\n", mysql_error(conn));
        mysql_close(conn);
        return NULL;
    }

    return conn;
}

void ajouter_adherents_mysql(adherent *adherents, int nb_adherents, MYSQL *con)
{
    char requete[300];
    int i;
    MYSQL_RES *res;
    MYSQL_ROW row;

    for (i = 0; i < nb_adherents; i++)
    {
        sprintf(requete, "INSERT INTO adherents (nom, prenom, livre_emprunte) VALUES ('%s', '%s', '%s')", adherents[i].nom, adherents[i].prenom, adherents[i].livre_emprunte->titre);

        if (mysql_query(con, requete))
        {
            fprintf(stderr, "%s\n", mysql_error(con));
            exit(1);
        }
    }
}
