#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <mysql/mysql.h>
#include "../include/database.h"

bool initBD(BD *bd)
{
    char *requetes[] = {
        "DROP DATABASE IF EXISTS evenements",
        "CREATE DATABASE evenements",
        "CREATE TABLE evenements.typeEvenement (id INT PRIMARY KEY NOT NULL AUTO_INCREMENT, libelle VARCHAR(64) )",
        "INSERT INTO evenements.typeEvenement (libelle) VALUES (\"Mariage\"), (\"Anniversaire\"), (\"Cinéma\")",
        "CREATE TABLE evenements.evenement (id INT PRIMARY KEY NOT NULL AUTO_INCREMENT, titre VARCHAR(256), nbPlaces INT, typeId INT, FOREIGN KEY (typeId) REFERENCES evenements.typeEvenement(id));",
        "CREATE TABLE evenements.seance (id INT PRIMARY KEY NOT NULL AUTO_INCREMENT, date DATE, evenementId INT, FOREIGN KEY (evenementId) REFERENCES evenements.evenement(id))",
        "CREATE TABLE evenements.ticket (id INT PRIMARY KEY NOT NULL AUTO_INCREMENT, seanceId INT, FOREIGN KEY (seanceId) REFERENCES evenements.seance(id))",
        "CREATE TABLE evenements.menu (id INT PRIMARY KEY NOT NULL AUTO_INCREMENT, titre VARCHAR(256), evenementId INT, FOREIGN KEY (evenementId) REFERENCES evenements.evenement(id))",
        "CREATE TABLE evenements.plat (id INT PRIMARY KEY NOT NULL AUTO_INCREMENT, nom VARCHAR(256), prix INT, menuId INT, FOREIGN KEY (menuId) REFERENCES evenements.menu(id))",
    };

    MYSQL *con = connectionBD(bd->hote, bd->utilisateur, bd->mdp, NULL);

    // S'assurer que la connection à la base de données s'est bien exécutée
    if (con == NULL)
    {
        return false;
    }

    // Exécution des requêtes de création de la base de données et des tables
    for (int i = 0; i < sizeof(requetes) / sizeof(requetes[0]); i++)
    {
        printf("Exécution de la requête : %s\n", requetes[i]);

        if (mysql_query(con, requetes[i]))
        {
            erreurBD(con);
            continue;
        }
    }

    mysql_close(con);

    return true;
}

MYSQL *connectionBD(char *hote, char *utilisateur, char *mdp, char *nom)
{
    MYSQL *con = mysql_init(NULL);

    // S'assurer que la fonction mysql_init s'est bien exécutée
    if (con == NULL)
    {
        erreurBD(con);
        return NULL;
    }

    // Connection à la base de données
    if (!mysql_real_connect(con, hote, utilisateur, mdp, nom, 0, NULL, 0))
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