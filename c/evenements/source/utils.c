#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Vide le buffer si l'utilisateur a saisi plus de caractères que prévu.
void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

// Lire de manière sécurisée la saisie de l'utilisateur.
bool lire(char *chaine, int longueur)
{
    char *positionEntree = NULL;

    if (fgets(chaine, longueur, stdin) != NULL)
    {
        positionEntree = strchr(chaine, '\n');

        if (positionEntree != NULL)
        {
            *positionEntree = '\0';
        }
        else
        {
            viderBuffer();
        }

        return true;
    }
    else
    {
        viderBuffer();
        return false;
    }
}
