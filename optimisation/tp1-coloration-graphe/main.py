from graphe import Graphe, gen_graphe
import sys
import math
import random


def coloriage_glouton(graphe: Graphe, couleurs):
  if len(couleurs) < graphe.delta():
    print('Le graphe ne peut pas être colorié avec moins de', graphe.delta(),
          'couleurs !')
    return

  coloriage = {
    i: [None] * len(graphe.dict[i])
    for i in range(graphe.nbr_sommets)
  }

  for sommet, voisins in graphe.dict.items():
    for i in range(len(voisins)):
      if coloriage[sommet][i] is None:
        colorie = False
        for couleur in couleurs:
          tentative_coloriage = colorier(graphe, coloriage, sommet, voisins[i],
                                         couleur)
          if (tentative_coloriage != False):
            coloriage = tentative_coloriage
            colorie = True
            break

        if colorie == False:
          print('Impossible de colorier l\'arête ({}, {})'.format(
            sommet, voisins[i]))

  return coloriage


def coloriage_recuit_simule(graphe: Graphe,
                            solution_initiale: dict,
                            couleurs=[],
                            temperature_initiale=100.,
                            alpha=.9,
                            iter_max=sys.maxsize):
  temperature = temperature_initiale
  solution = solution_initiale
  iter = 1

  while iter <= iter_max and temperature >= .0:
    while True:
      couleur_rand = random.choice(couleurs)
      sommet_a = random.randint(0, graphe.nbr_sommets - 1)
      sommet_b = random.choice(graphe.dict[sommet_a])
      solution_temp = colorier(graphe, solution, sommet_a, sommet_b,
                               couleur_rand)
      if solution_temp != False:
        break

    variation_energie = cout(solution_temp) - cout(solution)

    if variation_energie < 0 or random.random() < calculer_probabilite(
        variation_energie, temperature):
      solution = solution_temp

    iter += 1
    temperature -= alpha

  return solution


def colorier(graphe, graphe_colorier, sommet_a, sommet_b, couleur):
  index_b = graphe.dict[sommet_a].index(sommet_b)
  index_a = graphe.dict[sommet_b].index(sommet_a)
  if (couleur
      not in graphe_colorier[sommet_a]) and (couleur
                                             not in graphe_colorier[sommet_b]):
    graphe_colorier[sommet_a][index_b] = couleur
    graphe_colorier[sommet_b][index_a] = couleur
    return graphe_colorier

  return False


def calculer_probabilite(variation_energie, temperature):
  return math.exp(-variation_energie / temperature)


def cout(solution):
  couleurs_solution = []
  for sommet, couleurs in solution.items():
    for couleur in couleurs:
      if couleur not in couleurs_solution:
        couleurs_solution.append(couleur)
  return len(couleurs)


def coloriage_valide(solution):
  for sommet, couleurs in solution.items():
    if len(couleurs) != len(set(couleurs)):
      return False
  return True


if __name__ == '__main__':
  # 31 couleurs
  couleurs = [
    'Azure', 'Aqua', 'Brown', 'Bronze', 'Blue', 'Black', 'Yellow', 'White',
    'Wheat', 'Violet', 'Turquoise', 'Tomato', 'Teal', 'Silver', 'Salmon',
    'Red', 'Purple', 'Pink', 'Orange', 'Olive', 'Navy', 'Navy', 'Maroon',
    'Lime', 'Grey', 'Green', 'Gold', 'Dark', 'Cyan', 'Cyan', 'Chocolate'
  ]

  # On génére aléatoirement un graphe de 3 sommets et 10 arêtes maximum (le nombre d'arêtes final sera <= 10)
  g = gen_graphe(3, 10)

  print('Liste d\'adjacence du graphe :', g, sep='\n')

  res_glouton = coloriage_glouton(g, couleurs)
  print('Résulat de l\'algorithme glouton :', res_glouton, sep='\n')

  res_recuit = coloriage_recuit_simule(g, res_glouton, couleurs, 100, iter_max=2)
  print('Résulat du recuit simulé après 2 itérations :', res_recuit, sep='\n')

  print('L\'agorithme glouton a utilisé', cout(res_glouton), 'couleurs.\n'
        'Le recuit simulé a utilisé', cout(res_recuit), 'couleurs.')
