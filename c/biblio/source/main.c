#include <stdio.h>
#include <stdlib.h>
#include "../include/book.h"
#include "../include/member.h"

int main(int argc, char *argv[])
{
    int choice;

    // Création d'un premier livre - 1984 de George Orwell
    Book ninetyEightyFour;
    ninetyEightyFour.title = "1984";
    ninetyEightyFour.author = "George Orwell";
    ninetyEightyFour.borrowed = 0;

    // Création d'une liste de livres
    BookList books;
    books.first = &ninetyEightyFour;

    // Création d'un premier adhérent - John Doe
    Member johnDoe = {"John Doe"};

    // Création d'une liste d'adhérents
    MemberList members;
    members.first = &johnDoe;

    // Affichage du menu
    printf("Bienvenue dans votre application de gestion de bibliothèque\n");

    while (1)
    {
        printf("\nQue voulez-vous faire ?\n");
        printf("1. Afficher la liste des livres\n");
        printf("2. Ajouter un livre\n");
        printf("3. Emprunter un livre\n");
        printf("4. Retourner un livre\n");
        printf("5. Afficher la liste des adhérents\n");
        printf("6. Quitter\n");
        printf("> ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice)
        {
        case 1:
            printf("Liste des livres :\n");
            listBooks(&books);
            break;

        case 2:
            printf("Ajouter un livre :\n");
            Book *book = createBook();
            addBook(&books, book);
            break;

        case 3:
            printf("Emprunter un livre :\n");
            borrowBook();
            break;

        case 4:
            printf("Retourner un livre :\n");
            returnBook();
            break;

        case 5:
            printf("Liste des adhérents :\n");
            listMembers(&members);
            break;

        case 6:
            printf("Au revoir !\n");
            exit(0);

        default:
            printf("Veuillez choisir une option dans la liste !\n");
            break;
        }
    }

    return 0;
}