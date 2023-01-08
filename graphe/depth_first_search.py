# Implémentation en Python de l'algorithme de parcours en profondeur d'un graphe
from collections import defaultdict

# Réprésentation d'un graphe orienté avec sa matrice d'adjacence
class Graphe:

  # Constructeur
  def __init__(self):

    # Initialisation d'un graphe
    self.graph = defaultdict(list)

  # Fonction d'ajout d'un arc (u, v) au graphe
  def ajouterArc(self, u, v):
    self.graph[u].append(v)

  # Fonction d'exploration
  def explorer(self, v, visited):
    
    # Marquer le sommet v
    visited.add(v)
    
    # Afficher le sommet marqué
    print(v, end=' -> ')

    # Explorer récursivement tous les sommets adjacents au sommet marqué
    for neighbour in self.graph[v]:
      if neighbour not in visited:
        self.explorer(neighbour, visited)
    print('FIN')
    
  # Fonction principale
  def parcoursProfondeur(self, v):
    visited = set()
    self.explorer(v, visited)


if __name__ == "__main__":
  # Création d'un graphe
  g = Graphe()
  # Sommet 1
  g.ajouterArc(1, 2)
  g.ajouterArc(1, 5)
  g.ajouterArc(1, 9)
  # Sommet 2
  g.ajouterArc(2, 3)
  g.ajouterArc(2, 5)
  g.ajouterArc(2, 6)
  # Sommet 3
  g.ajouterArc(3, 6)
  # Sommet 4
  g.ajouterArc(4, 3)
  g.ajouterArc(4, 8)
  # Sommet 5
  g.ajouterArc(5, 6)
  # Sommet 6
  g.ajouterArc(6, 10)
  # Sommet 7
  g.ajouterArc(7, 4)
  g.ajouterArc(7, 6)
  # Sommet 8
  g.ajouterArc(8, 7)
  g.ajouterArc(8, 10)
  # Sommet 9
  g.ajouterArc(9, 5)
  g.ajouterArc(9, 6)
  # Sommet 10
  g.ajouterArc(10, 7)
  g.ajouterArc(10, 9)

  print("Résultat du parcours en profondeur à partir du sommet 1 :")
  g.parcoursProfondeur(1)
