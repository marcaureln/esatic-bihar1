# import des modules nécessaires
from math import sqrt
 
# Fonction pour calculer la distance euclidienne
def distance(a, b):
    return sqrt( (a[0] - b[0])**2 + (a[1] - b[1])**2 )
 
# Fonction pour le problème du voyageur de commerce
def tsp(graph):
 
    # Initialisation du tableau des distances
    distances = [[distance(x, y) for y in graph] for x in graph]
 
    # Initialisation du tableau des chemins
    paths = [[0] * len(graph) for _ in range(1 << len(graph))]
 
    # Initialisation du tableau des résultats
    results = [float('inf')] * (1 << len(graph))
 
    # Initialisation de la distance pour le premier chemin
    results[1] = 0
 
    # Pour chaque sous-ensemble de points
    for subset in range(1, 1 << len(graph)):
 
        # Pour chaque point
        for point in range(len(graph)):
 
            # Si le point n'a pas encore été visité
            if subset & (1 << point) != 0:
 
                # Pour chaque point qui n'a pas encore été visité
                for next_point in range(len(graph)):
 
                    # Si le point n'a pas encore été visité
                    if subset & (1 << next_point) == 0:
 
                        # Calcul de la distance entre le point et le prochain point
                        dist = distances[point][next_point]
 
                        # Calcul de la somme des distances
                        total = results[subset | (1 << next_point)] + dist
 
                        # Si la somme des distances est inférieure à la distance actuelle
                        if total < results[subset]:
 
                            # Mise à jour de la distance
                            results[subset] = total
 
                            # Mise à jour du chemin
                            paths[subset][point] = next_point
 
    # Initialisation du chemin optimal
    path = [0]
 
    # Initialisation de la valeur de l'ensemble
    subset = (1 << len(graph)) - 1
 
    # Pour chaque point
    for point in range(len(graph) - 1):
 
        # Récupération du prochain point
        next_point = paths[subset][path[-1]]
 
        # Mise à jour du chemin
        path.append(next_point)
 
        # Mise à jour de l'ensemble
        subset = subset & ~(1 << next_point)
 
    # Mise à jour du chemin
    path.append(0)
 
    # Renvoi du chemin et de la distance
    return path, results[(1 << len(graph)) - 1]
 
# Exemple
graph = [(0, 0), (3, 4), (2, 3), (1, 1)]

# Appel de la fonction
print(tsp(graph))