def little(sommets: list, matrice: list):
    sommets_ligne = sommets.copy()
    sommets_colonne = sommets.copy()
    tourne = []
    arbre_de_recherche = []
    pile = []
    destination = ""

    while True:
        # Total supprimé par lignes et par colonnes
        total_supprime = 0

        # Réduction de la matrice : lignes
        for i in range(len(matrice)):
            min_ligne = min([x for x in matrice[i] if x is not None])
            total_supprime += min_ligne

            for j in range(len(matrice)):
                if matrice[i][j] is None:
                    continue

                matrice[i][j] -= min_ligne

        # Réduction de la matrice : colonnes
        for i in range(len(matrice)):
            min_col = min([ligne[i] for ligne in matrice if ligne[i] is not None])
            total_supprime += min_col

            for j in range(len(matrice)):
                if matrice[j][i] is None:
                    continue

                matrice[j][i] -= min_col

        if len(arbre_de_recherche) > 1:
            noeud_parent = arbre_de_recherche[-2]
            arbre_de_recherche.append(noeud_parent + total_supprime)
        else:
            arbre_de_recherche.append(total_supprime)

        # Calcul des regrets dans toutes les cases de valeur 0
        regret_max, regret_i, regret_j = 0, 0, 0

        for i in range(len(matrice)):
            for j in range(len(matrice)):
                if matrice[i][j] == 0:
                    # Récupérer la ligne correspondante à la cellule actuelle et retirer l'élément en question
                    ligne = [x for x in matrice[i] if x is not None]
                    ligne.remove(matrice[i][j])
                    min_ligne = min(ligne)
                    # Récupérer la colonne correspondante à la cellule actuelle et retirer l'élément en question
                    colonne = [ligne[j] for ligne in matrice if ligne[j] is not None]
                    colonne.remove(matrice[i][j])
                    min_col = min(colonne)
                    # Calculer le regret
                    regret = min_ligne + min_col

                    # Garder en mémoire les coordonnées du sommet de regret maximal
                    if regret > regret_max:
                        regret_max = regret
                        regret_i = i
                        regret_j = j

        arbre_de_recherche.append(total_supprime + regret_max)
        tourne.append(sommets_ligne[regret_j] + sommets_colonne[regret_i])
        pile.append(len(arbre_de_recherche) - 1)

        # Supprimer la ligne et la colonne du noeud inclus
        sommets_ligne.pop(regret_j)
        sommets_colonne.pop(regret_i)
        matrice.pop(regret_j)
        colonne_supprime = [ligne.pop(regret_i) for ligne in matrice]

        # Supprimer tous les trajets aboutissent à des sous-tournées incomplètes
        for trajet in tourne:
            try:
                inverse_i, inverse_j = sommets_ligne.index(trajet[-1]), sommets_colonne.index(trajet[0])
                matrice[inverse_i][inverse_j] = None
            except ValueError:
                # Une des valeurs, trajet[-1] et/ou traject[0] est absente de la liste des sommets
                continue

        if len(matrice) <= 2:
            break

    # Création de chaîne du résultat à afficher
    destination += tourne[0]

    while len(destination) < len("-".join(tourne)):
        for noeud in tourne:
            if destination[-1] == noeud[0]:
                destination += '-' + noeud
                continue

    return destination


if __name__ == '__main__':
    villes = ['B', 'L', 'N', 'P', 'M', 'D']
    matrice_de_cout = [
        [None, 780, 320, 580, 480, 660],
        [780, None, 700, 460, 300, 200],
        [320, 700, None, 380, 820, 630],
        [580, 460, 380, None, 750, 310],
        [480, 300, 820, 750, None, 500],
        [660, 200, 630, 310, 500, None],
    ]

    print('Résultat algorithme de Little :', little(villes, matrice_de_cout), sep='\n')
