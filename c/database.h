#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED


MYSQL *connect_to_database(const char *host, const char *user, const char *password, const char *database);
void ajouter_adherents_mysql(adherent *adherents, int taille_tableau, MYSQL *con);
#endif // DATABASE_H_INCLUDED
