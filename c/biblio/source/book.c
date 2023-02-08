#include <stdio.h>
#include <stdlib.h>
#include <stddef.h> // Pour NULL
#include <string.h>
#include "../include/book.h"

Book *createBook()
{
    char *title, *author;
    Book *book = malloc(sizeof(Book));
    printf("Création d'un nouveau livre\n");
    printf("Titre : ");
    scanf("%s", &title);
    book->title = title;
    printf("Auteur : ");
    scanf("%s", &author);
    book->author = author;
    book->borrowed = 0;
    book->borrowedBy = NULL;
    book->next = NULL;
    return book;
}

void addBook(BookList *books, Book *book)
{
    if (books->first == NULL)
    {
        books->first = book;
    }
    else
    {
        Book *current = books->first;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = book;
    }
}

void borrowBook()
{
    // TODO: À implémenter
    printf("Fonction manquante\n");
}

void returnBook()
{
    // TODO: À implémenter
    printf("Fonction manquante\n");
}

void listBooks(BookList *books)
{
    if (books == NULL)
    {
        printf("Aucun livre n'a été trouvé.\n");
    }

    Book *current = books->first;

    while (current != NULL)
    {
        printf("%s - %s\n", current->title, current->author);
        current = current->next;
    }
}