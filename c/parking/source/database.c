#include <stdio.h>
#include <stddef.h>
#include <mysql/mysql.h>
#include "../include/database.h"

MYSQL *connectionBD()
{
    MYSQL *con = mysql_init(NULL);

    // S'assurer que la fonction mysql_init s'est bien exécutée
    if (con == NULL)
    {
        erreurBD(con);
        return NULL;
    }

    // Connection à la base de données
    if (!mysql_real_connect(con, "db", "root", "example", "parking", 0, NULL, 0))
    {
        erreurBD(con);
        return NULL;
    }

    return con;
}

void erreurBD(MYSQL *con)
{
    fprintf(stderr, "Une erreur s'est produite lors de l'interaction avec la base de données. Erreur : %s\n", mysql_error(con));
    mysql_close(con);
}