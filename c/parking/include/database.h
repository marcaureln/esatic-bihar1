#ifndef BD_H
#define BD_H

#include <mysql/mysql.h>

MYSQL *connectionBD();
void erreurBD(MYSQL *);

#endif