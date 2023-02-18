# Projet Gestion de Parking

## Prérequis

L'application a été développée et testée sur un système d'exploitation Linux (Ubuntu 22.04).
Pour des raisons de portabilité, nous avons utilisé **Docker**.
Ainsi, vous n'avez pas besoin d'installer aucune dépendances sur votre machine.
L'application et la base de données sont exécutées dans des conteneurs Docker. Le tout orchestré par **Docker Compose**.

Si vous n'avez pas Docker et Docker Compose, vous pouvez les installer avec les liens suivants :

- [Installer Docker](https://www.docker.com/)
- [Installer Docker Compose](https://docs.docker.com/compose/)

De plus, nous avons créé un Makefile pour simplifier l'exécution la compilation et l'exécution de l'application.
Si vous décidez de ne pas utiliser Docker, vous pouvez toujours utiliser le Makefile pour compiler et exécuter l'application.
Mais vous devez avoir une base de données MySQL et les librairies de développement C de MySQL installée sur votre machine.
Ensuite, vous devrez modifier le fichier `source/database.c` pour configurer la connexion à la base de données.
Une fois que vous avez configuré la connexion à la base de données, vous pouvez compiler et exécuter l'application avec la commande suivante :

```bash
# À la racine du projet
make # Compiler et exécuter l'application
```

## Comment utiliser l'application

```bash
# À la racine du projet
docker compose pull # Télécharger les images docker
docker compose build # Construire l'image docker de l'application
docker compose up -d # Démarrer les conteneurs
docker compose run --rm app make run # Démarrer un conteneur et exécuter l'application
# CTRL + D pour quitter le conteneur
```

Lorsque vous avez fini d'utiliser l'application, vous pouvez arrêter le conteneur de la base de données avec la commande suivante :

```bash
docker compose down # Arrêter le conteneur de la base de données, ajouter --volumes pour supprimer les données
```

Si vous effectuez des modifications sur le code, vous pouvez recompiler l'application avec la commande suivante :

```bash
docker compose run --rm app make build # Démarrer un conteneur et compiler l'application
docker compose run --rm app make run
# ou simplement
docker compose run --rm app make # Démarrer un conteneur, compiler et exécuter l'application
```
