import random
import pydot

random.seed(42)

class Graphe:

  def __init__(self, nbr_sommets):
    self.nbr_sommets = nbr_sommets  # Nombre de sommets
    self.dict = {i: [] for i in range(nbr_sommets)}  # Liste d'adjacence

  def __str__(self):
    repr = ''
    for sommet, aretes in self.dict.items():
      repr += str(sommet) + ' -> ' + ', '.join(map(str, aretes)) + '\n'
    return repr

  def ajouter_arete(self, x, y):
    self.dict[x].append(y)
    self.dict[y].append(x)

  def delta(self):
    degres = {i: len(aretes) for i, aretes in self.dict.items()}
    delta = sorted(degres.values(), reverse=True)[0]
    return delta

  def viz(self):
    print('À faire')

def gen_graphe(nbr_sommets=2, max_aretes=1):
  g = Graphe(nbr_sommets)

  for i in range(max_aretes):
    # Choisir aléatoirement un sommet
    x = random.randint(0, nbr_sommets - 1)
    # Choisir aléatoirement le second sommet dans une séquence privée du sommet pris précédement et de ses sommets adjacents
    sommets_adj_x = [x] + g.dict[x]
    
    try:
      y = random.choice([i for i in range(nbr_sommets) if i not in sommets_adj_x])
      g.ajouter_arete(x, y)
    except IndexError:
      # Arrive lorsque le sommet x choisi est déjà relié à tout les autres sommets
      continue
  
  return g