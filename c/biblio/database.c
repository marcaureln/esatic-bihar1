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

void ajouter_livres_mysql(livre* livres, int nb_livres, MYSQL* mysql_conn) {
    char query[200];
    MYSQL_RES *result;
    MYSQL_ROW row;

    // Boucle pour insérer chaque livre dans la table
    for (int i = 0; i < nb_livres; i++) {
        // Construction de la requête SQL
        sprintf(query, "INSERT INTO livres (titre, auteur, annee_publication, disponible) VALUES ('%s', '%s', %d, %d)",
                livres[i].titre, livres[i].auteur, livres[i].annee_publication, livres[i].disponible);

        // Exécution de la requête
        if (mysql_query(mysql_conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(mysql_conn));
        }
    }

    // Affichage des livres ajoutés
    if (mysql_query(mysql_conn, "SELECT * FROM livres")) {
        fprintf(stderr, "%s\n", mysql_error(mysql_conn));
    }
    result = mysql_store_result(mysql_conn);
    while ((row = mysql_fetch_row(result))) {
        printf("Livre ajouté : id=%s, titre=%s, auteur=%s, année=%s, disponible=%s\n",
                row[0], row[1], row[2], row[3], row[4]);
    }
    mysql_free_result(result);
}

//Cette fonction prend en paramètres le tableau "livres", sa taille "nb_livres" et une connexion MySQL "mysql_conn". Elle insère chaque livre dans la table "livres" et affiche les livres ajoutés. Notez que cette fonction nécessite la bibliothèque MySQL : #include <mysql/mysql.h>.

//Il est important de noter que cette fonction ne gère pas les erreurs de connexion à la base de données ou d'insertion de données. Il est donc important de prendre en compte ces cas d'erreur pour une utilisation en production.

