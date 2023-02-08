#include <stdio.h>
#include <stddef.h> // Pour NULL
#include "../include/member.h"

void listMembers(MemberList *members)
{
    if (members == NULL)
    {
        printf("Aucun adhérent n'a été trouvé.\n");
    }

    Member *current = members->first;

    while (current != NULL)
    {
        printf("%s\n", current->name);
        current = current->next;
    }
}