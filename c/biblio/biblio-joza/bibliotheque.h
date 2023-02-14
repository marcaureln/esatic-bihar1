#ifndef BIBLIOTHEQUE_H_INCLUDED
#define BIBLIOTHEQUE_H_INCLUDED
typedef struct {
    char titre[100];
    char auteur[100];
    int disponible;
} livre;

// Structure pour représenter un adhérent
typedef struct {
    char nom[100];
    char prenom[100];
    livre* livre_emprunte;
} adherent;


void ajouter_livre(livre livres[], int *nb_livres);
void emprunter_livre(livre livres[], int nb_livres, adherent adherents[], int *nb_adherents);
void retour_livre(livre livres[], int nb_livres, adherent adherents[], int nb_adherents);
void lister_adherents(adherent adherents[], int nb_adherents);


#endif // BIBLIOTHEQUE_H_INCLUDED
