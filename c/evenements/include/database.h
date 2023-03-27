#ifndef BD_H
#define BD_H

#include <mysql/mysql.h>
#include <stdbool.h>

typedef struct BD BD;

struct BD
{
    char *hote;
    char *utilisateur;
    char *mdp;
    char *nom;
};

bool initBD(BD *);
MYSQL *connectionBD(char *, char *, char *, char *);
void erreurBD(MYSQL *);

#endif