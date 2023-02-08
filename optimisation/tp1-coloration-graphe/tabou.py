"""
    METHODE TABOU
"""
import math
import random

#fonction d'initialisation de la premiere solution
def initialisation():
    T = [random.randint(0, 7) for  i in range(8)]
    """
    for i in range(8):
      T[i] = random.randint(0, 7) 
    """
    return T

#fonction de conflit
def conflit (c):
    compteur = 0
    for i in range(8):
        for j in range(8):
            #print(i)
            if ((c[i] == c[j]) and (i != j)):
                compteur = compteur + 1
            if (( abs(c[i] - c[j]) == abs (i - j)) and (i != j)):
                compteur = compteur + 1
    return compteur

#fonction de voisinage
def voisinage(c0, nombreVoisin = 3):
    c1 = [ 0, 0, 0, 0, 0, 0, 0, 0]
    T = []
    while len(T) < nombreVoisin:
        for i in range(8):
            c1[i] = c0[i] + 2*random.randint(0, 7)
            if c1[i] > 7 :
                c1[i] = c1[i]%7
        T.append(c1)
        c1 = [ 0, 0, 0, 0, 0, 0, 0, 0]
    return T

#tri des voisin par le plus petit conflit
def tri_selection(tab, tab2):
    for i in range(len(tab)):
      # Trouver le min
       min = i
       for j in range(i+1, len(tab)):
           if tab[min] > tab[j]:
               min = j  
       tmp = tab[i]
       tab[i] = tab[min]
       tab[min] = tmp
       
       tmp2 = tab2[i]
       tab2[i] = tab2[min]
       tab2[min] = tmp2
    #print("solution generer ord ", tab2)
    #print("conflit ", tab)
    return {"solution" : tab2[0], "conflit": tab[0]}

#
def select(T):
    taille = []
    for i in T:
        taille.append(conflit(i))
    return tri_selection(taille, T)

def TABOU(s0):
    s = s0
    conflitInit = conflit(s0)
    print("SOLUTION INITIAL : ", s0,)
    print("LE CONFLIT DE LA SOLUTION INITIAL: ", conflitInit)
    TabTabou=[]
    while conflitInit!=0:
        ns = voisinage(s, 5)
        voisin = select(ns)
        conflitVoisin = voisin.get('conflit')
        if conflitVoisin < conflitInit:
            s = voisin.get('solution')
            conflitInit = conflitVoisin 
            TabTabou.append(s)
    print("SOLUTIONS TABOU : ", TabTabou)
    solution = TabTabou [len(TabTabou) - 1]
    return solution

solution = TABOU(initialisation())

print("LA SOLUTION OPTIMAL : ", solution)
print("LE CONFLIT DE LA SOLUTION OPTIMAL : ", conflit(solution))