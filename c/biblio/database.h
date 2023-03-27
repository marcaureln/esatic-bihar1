#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED
#include <mysql/mysql.h>
#include "bibliotheque.h"
MYSQL *connect_to_database(const char *host, const char *user, const char *password, const char *database);
void ajouter_adherents_mysql(adherent *adherents, int taille_tableau, MYSQL *con);
void ajouter_livres_mysql(livre* livres, int nb_livres, MYSQL* mysql_conn)
#endif // DATABASE_H_INCLUDED
