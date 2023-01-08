class Enregistrement:
    def __init__(self, nom, prenom, numero, moyenne):
        self.nom = nom
        self.prenom = prenom
        self.numero = numero
        self.moyenne = moyenne
        self.suivant = None

    def copie(self):
        return Enregistrement(self.nom, self.prenom, self.numero, self.moyenne)

    def __str__(self):
        return '%s %s (Matricule : %s | Moyenne : %2.2f)' % (self.nom, self.prenom, self.numero, self.moyenne)


class Liste:
    def __init__(self):
        self.premier = None

    def ajout(self, enregistrement):
        if self.premier is None:
            self.premier = enregistrement
        else:
            enregistrement_actuel = self.premier
            while enregistrement_actuel.suivant is not None:
                enregistrement_actuel = enregistrement_actuel.suivant
            enregistrement_actuel.suivant = enregistrement

    def ajout_premier(self, enregistrement):
        if self.premier is None:
            self.premier = enregistrement
        else:
            enregistrement.suivant = self.premier
            self.premier = enregistrement

    def supprimer(self, enregistrement):
        if self.premier is None:
            print("La liste est vide")
        else:
            enregistrement_actuel = self.premier
            enregistrement_precedent = None
            while enregistrement_actuel.suivant is not None:
                if enregistrement_actuel == enregistrement:
                    break
                enregistrement_precedent = enregistrement_actuel
                enregistrement_actuel = enregistrement_actuel.suivant
            if enregistrement_precedent is not None:
                enregistrement_precedent.suivant = enregistrement_actuel.suivant
            else:
                self.premier = enregistrement_actuel.suivant
            del enregistrement

    def tri(self):
        permutation = True
        while permutation is True:
            permutation = False
            enregistrement_precedent = None
            enregistrement_actuel = self.premier
            while enregistrement_actuel is not None and enregistrement_actuel.suivant is not None:
                enregistrement_suivant = enregistrement_actuel.suivant
                if min(enregistrement_actuel.nom, enregistrement_suivant.nom) == enregistrement_suivant.nom:
                    permutation = True
                    if enregistrement_precedent is not None:
                        enregistrement_precedent.suivant = enregistrement_suivant
                    else:
                        self.premier = enregistrement_suivant
                    enregistrement_actuel.suivant = enregistrement_suivant.suivant
                    enregistrement_suivant.suivant = enregistrement_actuel
                enregistrement_precedent = enregistrement_actuel
                enregistrement_actuel = enregistrement_actuel.suivant
        return self

    def inverse(self):
        liste_inverse = Liste()
        enregistrement_actuel = self.premier
        while enregistrement_actuel is not None:
            liste_inverse.ajout_premier(enregistrement_actuel.copie())
            enregistrement_actuel = enregistrement_actuel.suivant
        return liste_inverse

    def promo_finale(self, moyenne=12):
        promo_finale = Liste()
        enregistrement_actuel = self.premier
        while enregistrement_actuel is not None:
            if enregistrement_actuel.moyenne >= moyenne:
                promo_finale.ajout(enregistrement_actuel.copie())
            enregistrement_actuel = enregistrement_actuel.suivant
        return promo_finale

    def fusion(self, autre_liste):
        if self.premier is None:
            return autre_liste
        if autre_liste is None:
            return self

        fusion = Liste()
        enregistrement_actuel = self.premier
        while enregistrement_actuel is not None:
            fusion.ajout(enregistrement_actuel.copie())
            enregistrement_actuel = enregistrement_actuel.suivant
        enregistrement_actuel = autre_liste.premier
        while enregistrement_actuel is not None:
            fusion.ajout(enregistrement_actuel.copie())
            enregistrement_actuel = enregistrement_actuel.suivant

        return fusion

    def __str__(self):
        s = ''
        enregistrement_actuel = self.premier
        while enregistrement_actuel is not None:
            s += str(enregistrement_actuel) + '\n'
            enregistrement_actuel = enregistrement_actuel.suivant
        return s


if __name__ == '__main__':
    # Création de la liste et de quelques enregistrements
    liste = Liste()
    john_doe = Enregistrement('Doe', 'John', 'E001', 11.0)
    jane_doe = Enregistrement('Doe', 'Jane', 'E002', 18.0)
    joza = Enregistrement('Joker', 'Joza', 'E003', 15)
    nelly = Enregistrement('Nemo', 'Nelly', 'E004', 15)

    # Ajout des enregistrements dans la liste
    liste.ajout(joza)
    liste.ajout(nelly)
    liste.ajout(john_doe)
    liste.ajout(jane_doe)
    print('Liste : ', liste, sep='\n')

    # Suppression d'un enregistrement
    liste.supprimer(john_doe)
    print('Liste après suppression : ', liste, sep='\n')

    # Liste triée
    print('Liste triée : ', liste.tri(), sep='\n')

    # Liste inversée
    print('Liste inversée : ', liste.inverse(), sep='\n')

    # Promotion finale : étudiants ayant une moyenne supérieure ou égale à 12
    promo_finale = liste.promo_finale()
    print('Promo finale : ', promo_finale, sep='\n')

    # Fusion promotion finale avec la liste des recrutements
    recrutements = Liste()
    recrutements.ajout(Enregistrement('Manu', 'Pixou', 'P001', 15))
    fusion = promo_finale.fusion(recrutements)
    print('Liste fusionnée : ', fusion, sep='\n')
