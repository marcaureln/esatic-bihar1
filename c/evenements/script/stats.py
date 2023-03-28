from mysql import connector
bd = connector.connect(host='localhost', user='root', password='example', db='evenements')
requete = 'SELECT evenement.titre, CONCAT(\'Séance n°\', seance.id), DATE_FORMAT(date, \'%d/%m/%Y\'), COUNT(ticket.id) FROM evenement, seance, ticket WHERE evenement.id = seance.idEvenement AND seance.id = ticket.idSeance GROUP BY seance.id;'
curseur = bd.cursor()
curseur.execute(requete)
resultat = curseur.fetchall()
print('(Nom événement, N° Séance, Date, Tickets vendus)')
print('\n'.join([str(ligne) for ligne in resultat]))
