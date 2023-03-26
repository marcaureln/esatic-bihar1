# MongoDB - Travaux Pratiques

Télécharger la collection [ici](http://b3d.bdpedia.fr/mongodb_tp.html) et importer la dans la base de données de votre choix mais dans une collection nommée « public ».

1. Liste de tous les livres (type « Book ») ;

```bash
db.public.find({type: "Book"})
```

2. Liste des publications depuis 2011 ;

```bash
db.public.find({type: "Book", year: { $gte:2011} })
```

3. Liste des livres depuis 2014 ;

```bash
db.public.find({type: "Book", year: { $gte:2014} })
```

4. Liste des publications de l’auteur « Toru Ishida » ;

```bash
db.public.find({authors: "Toru Ishida" })
```

5. Liste de tous les éditeurs (type « publisher »), distincts ;

```bash
db.public.distinct("publisher")
```

6. Liste de tous les auteurs distincts ;

```bash
db.public.distinct("authors")
```

7. Trier les publications de « Toru Ishida » par titre de livre et par page de début ;

```bash
db.public.find().sort({ age: 1, nom: -1 })
```

8. Projeter le résultat sur le titre de la publication, et les pages ;
9. Compter le nombre de ses publications ;
10. Compter le nombre de publications depuis 2011 et par type ;
11. Compter le nombre de publications par auteur et trier le résultat par ordre croissant ;
