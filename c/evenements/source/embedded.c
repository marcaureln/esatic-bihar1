#include <stdio.h>
#include <stdlib.h>
#include <python3.10/Python.h>
#include "../include/embedded.h"

/// @brief Exécute un script Python.
/// @param chemin
void executerCodePython(char *chemin)
{
    FILE *fichier;
    fichier = fopen("script/stats.py", "r");

    if (fichier == NULL)
    {
        printf("Impossible d'ouvrir le fichier %s", chemin);
        return;
    }

    printf("Fichier ouvert...\n");
    Py_Initialize();
    printf("Python initialisé !\n");
    PyRun_SimpleFile(fichier, "script/stats.py");
    printf("Script exécuté !\n");
    Py_Finalize();
}

// void executerCodePython(char *chemin)
// {
//     Py_Initialize();

//     FILE *fichier;
//     fichier = fopen(chemin, "r");
//     char ligne[256];
//     size_t longueurLigne = 0;
//     ssize_t ligneActuelle;

//     if (fichier == NULL)
//     {
//         printf("Impossible d'ouvrir le fichier %s", chemin);
//         return;
//     }

//     while ((ligneActuelle = getline(&ligne, &longueurLigne, fichier)) != -1)
//     {
//         PyRun_SimpleString(ligne);
//     }

//     Py_Finalize();
// }
