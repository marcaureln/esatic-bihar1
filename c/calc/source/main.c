#include <stdio.h>
#include <stdlib.h>
#include "../header/addition.h"
#include "../header/soustraction.h"
#include "../header/division.h"
#include "../header/produit.h"

int main(int argc, char *argv[]) {
	int a = atoi(argv[1]);
	int b = atoi(argv[3]);
	int resultat;

	switch (argv[2][0]) {
		case '+':
			resultat = addition(a, b);
			break;
		case '-':
			resultat = soustraction(a, b);
			break;
		case 'x':
			resultat = produit(a, b);
			break;
		case '/':
			resultat = division(a, b);
			break;
		default:
			printf("Opérateur invalide !\n");

	}

	printf("Résultat : %d\n", resultat);

	return 0;
}
