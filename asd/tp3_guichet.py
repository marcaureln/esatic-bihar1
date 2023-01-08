import random
from datetime import datetime

class Guichet:
    def __init__(self, interval_max, duree_traitement_max):
        self.interval_max = interval_max
        self.duree_traitement_max = duree_traitement_max
        self.journal = {}

    def simulation(self, num_clients):
        derniere_arrivee = datetime.now().timestamp()
        for i in range(num_clients):
            # Les clients arrivent à des dates aléatoires
            derniere_arrivee += self.arrivee()
            self.journal[derniere_arrivee] = 'Arrivée du client ' + str(i + 1)
            # Traitement du client
            depart = derniere_arrivee + self.traitement()
            self.journal[depart] = 'Fin du traitement et départ du client ' + str(i + 1)

        for timestamp in sorted(self.journal.keys()):
            date = datetime.fromtimestamp(timestamp)
            print(date, ':', self.journal[timestamp])

    def arrivee(self):
        # L'interval d'arrivée de deux clients successifs est compris entre O et interval_max (en seconde)
        return random.randrange(0, self.interval_max)

    def traitement(self):
        # Le traitement a une durée comprise entre 0 et duree_traitement_max (en seconde)
        return random.randrange(0, self.duree_traitement_max)


if __name__ == '__main__':
    # On crée un guichet avec la configuration suivante :
    # 2m d'interval max entre deux arrivées
    # 1m max pour le traitement d'un client
    guichet = Guichet(120, 60)
    guichet.simulation(10)
