#ifndef TICKET_H
#define TICKET_H

#include "database.h"

typedef struct Ticket Ticket;

struct Ticket
{
    int id;
    int seanceId;
};

void vendreTicket(BD *, int);

#endif