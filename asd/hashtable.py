"""ASD - Interrogation N°1 - Exo 1"""
import random
random.seed(42)


class HashTable:
    """Représentation de la table de hachage"""

    def __init__(self, size):
        self.size = size
        self.table = [None] * size

    def insert(self, key, value):
        """Inserer une valeur dans la table"""
        self.table[key] = value

    def get(self, key):
        """Récupérer une valeur dans la table"""
        return self.table[key]

    def __str__(self):
        to_print = ''
        table_index = 0
        for elt in self.table:
            to_print += str(table_index) + ': ' + str(elt) + '\n'
            table_index += 1
        return to_print


def hash_fn1(table: HashTable, key):
    """Fonction de hachage pour table à adressage ouvert avec sondage linéaire"""
    i = 0
    index = key % table.size

    while table.get(index) is not None and i < table.size:
        i += 1
        index = ((key % table.size) + i) % table.size

    if i == table.size:
        # print(key, ': None')
        return None

    # print(key, ':', index, '(i =', i, ')')
    return index, i


def hash_fn2(table: HashTable, key):
    """Fonction de hachage pour table à adressage ouvert avec sondage quadratique"""
    i = 0
    index = key % table.size

    while table.get(index) is not None and i < table.size:
        i += 1
        index = ((key % table.size) + i**2) % table.size

    if i == table.size:
        # print(key, ': None')
        return None

    # print(key, ':', index, '(i =', i, ')')
    return index, i


class HashTableWithChains():
    """Représentation de la table de hachage avec chaînage séparé"""

    def __init__(self, size):
        self.size = size
        self.table = [[] for i in range(size)]

    def hash_fn(self, key):
        """Fonction de hachage interne"""
        return key % self.size

    def insert(self, key):
        """Inserer une valeur dans la table"""
        index = self.hash_fn(key)
        self.table[index].append(key)

    def get(self, key):
        """Récupérer une valeur dans la table"""
        index = self.hash_fn(key)
        for element in self.table[index]:
            if element == key:
                return element
        return 'NIL'

    def __str__(self):
        to_print = ''
        table_index = 0
        for elt in self.table:
            to_print += str(table_index) + ': ' + str(elt) + '\n'
            table_index += 1
        return to_print


if __name__ == '__main__':
    # Question 1
    M = 100
    T1, T2 = HashTable(M), HashTable(M)
    total_collisions_fn1, total_collisions_fn2 = 0, 0
    keys = [random.randint(0, 100) for i in range(50)]

    # print(keys)

    for k in keys:
        (i, collisions) = hash_fn1(T1, k)
        total_collisions_fn1 += collisions
        T1.insert(i, k)

        (i, collisions) = hash_fn2(T2, k)
        total_collisions_fn2 += collisions
        T2.insert(i, k)

    print('Table de hachage avec fonction n° 1 :')
    print(T1)
    print('Total collisions :', total_collisions_fn1)
    print('\nTable de hachage avec fonction n° 2 :')
    print(T2)
    print('Total collisions :', total_collisions_fn2)

    # La meilleure fonction de hachage doit éviter le maximum de collisions.
    if total_collisions_fn1 < total_collisions_fn2:
        print('\nLa meilleure fonction de hachage est la fonction 1 (sondage linéaire)')
    else:
        print('\nLa meilleure fonction de hachage est la fonction 2 (sondage quadratique)')

    # Question 2
    TC = HashTableWithChains(10)
    for k in keys:
        TC.insert(k)

    print('\nTable de hachage avec chaînage séparé :')
    print(TC)
