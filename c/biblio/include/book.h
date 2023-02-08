#ifndef BOOK_H
#define BOOK_H

typedef struct Book Book;
typedef struct BookList BookList;

struct Book
{
    char *title;
    char *author;
    int borrowed;      // 0 = non, 1 = oui
    char *borrowedBy;  // nom de l'adhérent qui a emprunté le livre
    struct Book *next; // pointeur vers le prochain livre
};

struct BookList
{
    Book *first;
};

Book *createBook();
void addBook(BookList *books, Book *book);
void listBooks(BookList *books);
void borrowBook();
void returnBook();

#endif