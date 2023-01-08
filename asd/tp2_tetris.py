import random
import time

# Briques de bases, chacune définie par sa largeur et sa hauteur 
BRIQUES = [
    (3, 1),
    (2, 2),
    (1, 3),
    (2, 1),
    (1, 2),
]

# Couleurs correspondantes aux briques
COULEURS = ['bleu', 'jaune', 'violet', 'vert', 'rouge']


class Tetris:
    def __init__(self, largeur, hauteur):
        self.largeur = largeur
        self.hauteur = hauteur
        self.plateau = [[0] * largeur for _ in range(hauteur)]
        self.brique = self.nouvelle_piece()
        self.brique_suivante = self.nouvelle_piece()

    def nouvelle_piece(self):
        forme = random.choice(BRIQUES)
        couleur = random.choice(COULEURS)
        return {'forme': forme, 'couleur': couleur, 'x': self.largeur // 2, 'y': self.hauteur}

    def bouger_gauche(self):
        self.brique['x'] = max(0, self.brique['x'] - 1)

    def bouger_droite(self):
        self.brique['x'] = min(self.largeur - len(self.brique['forme'][0]), self.brique['x'] + 1)

    def bouger_bas(self):
        self.brique['y'] += 1
        if self.collisions():
            self.brique['y'] -= 1
            self.casser_ligne()
            self.brique = self.brique_suivante
            self.brique_suivante = self.nouvelle_piece()

    def collisions(self):
        forme = self.brique['forme']
        for y in range(len(forme)):
            for x in range(len(forme[y])):
                if forme[y][x] == 0:
                    continue
                if self.brique['y'] + y >= self.hauteur:
                    return True
                if self.brique['x'] + x < 0 or self.brique['x'] + x >= self.largeur:
                    return True
                if self.plateau[self.brique['y'] + y][self.brique['x'] + x] != 0:
                    return True
        return False

    def casser_ligne(self):
        new_plateau = [[0] * self.largeur for _ in range(self.hauteur)]
        y = self.hauteur - 1
        for old_y in range(self.hauteur - 1, -1, -1):
            if sum(self.plateau[old_y]) == 0:
                continue
            new_plateau[y] = self.plateau[old_y]
            y -= 1
        self.plateau = new_plateau

    def tracer(self):
        forme = self.brique['forme']
        couleur = self.brique['couleur']
        for y in range(len(forme)):
            for x in range(len(forme)):
                self.plateau[self.brique['y'] + y][self.brique['x'] + x] = couleur
        print('Suivant:')
        print('\n' + '-' * (self.largeur + 2))
        for row in self.plateau:
            print('|' + ''.join([str(cell or ' ') for cell in row]) + '|')
        print('-' * (self.largeur + 2))


if __name__ == '__main__':
    # On crée un plateau de 10x20 (largeur x hauteur)
    tetris = Tetris(10, 20)
    while True:
        tetris.tracer()
        move = input('Bouger (gauche, droite, bas): ')
        if move == 'gauche':
            tetris.bouger_gauche()
        elif move == 'droite':
            tetris.bouger_droite()
        elif move == 'bas':
            tetris.bouger_bas()
        time.sleep(0.5)


