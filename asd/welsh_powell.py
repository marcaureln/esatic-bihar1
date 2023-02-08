def color_graph(graph, num_colors):
    # Trier les sommets du graphe par ordre décroissant de leur degré
    sorted_vertices = sorted(graph, key=lambda x: len(graph[x]), reverse=True)

    # Initialiser les couleurs disponibles (une liste de num_colors couleurs)
    available_colors = [i for i in range(num_colors)]

    # Initialiser le dictionnaire de couleurs avec une couleur par défaut (-1) pour chaque sommet
    vertex_colors = {}
    for vertex in graph:
        vertex_colors[vertex] = -1

    # Pour chaque sommet du graphe, parcourir ses voisins et trouver la couleur la moins utilisée
    for vertex in sorted_vertices:
        used_colors = []
        for neighbor in graph[vertex]:
            if vertex_colors[neighbor] != -1:
                used_colors.append(vertex_colors[neighbor])

        # Assigner la couleur la moins utilisée au sommet courant
        for color in available_colors:
            if color not in used_colors:
                vertex_colors[vertex] = color
                break

    # Retourner le dictionnaire de couleurs
    return vertex_colors

# Exemple d'utilisation de l'algorithme de Welsh-Powell

# Créer un graphe sous forme de dictionnaire {sommet: [voisins]}
graph = {
    0: [1, 2],
    1: [0, 2],
    2: [0, 1, 3],
    3: [2]
}

# Appliquer l'algorithme de Welsh-Powell avec 3 couleurs disponibles
vertex_colors = color_graph(graph, 3)

# Afficher les couleurs assignées à chaque sommet
print(vertex_colors)
# {0: 0, 1: 1, 2: 2, 3: 0}