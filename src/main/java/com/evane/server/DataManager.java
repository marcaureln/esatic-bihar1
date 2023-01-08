package com.evane.server;

import java.util.Vector;

/**
 * Classe qui g�re un ensemble de Personne via 3 op�rations.
 */
public class DataManager {

    /**
     * Vecteur qui contient les personnes
     */
    protected static Vector<Personne> personneVector = new Vector<Personne>();

    /**
     * Ajoute une personne dans la liste et retourne son
     * identificateur. Si la personne existait d�j�, retourne
     * l'identificateur qu'elle avait dans la liste.
     * 
     * @param p la personne � ajouter dans la liste
     * @return l'identificateur de la personne
     */
    public synchronized int addPersonne(Personne p) {
        if (!personneVector.contains(p))
            personneVector.add(p);
        return (personneVector.indexOf(p));
    }

    /**
     * R�cup�re une personne dans la liste � partir de son
     * identifiant.
     * 
     * @param id l'idenfiant de la personne � r�cup�rer
     * @throws InvalidIdException dans le cas o� l'identifiant
     *                            n'est attribu� � aucune personne
     */
    public synchronized Personne getPersonne(int id) throws InvalidIdException {
        if (id >= personneVector.size())
            throw new InvalidIdException("invalid index value : " + id);
        return (personneVector.elementAt(id));
    }

    /**
     * R�cup�re l'identifiant d'une personne.
     * 
     * @param p la personne dont on veut r�cup�rer l'identifiant
     * @return l'identificateur de la personne. Si la personne n'est
     *         pas dans la liste, retourne -1.
     */
    public synchronized int getId(Personne p) {
        return personneVector.indexOf(p);
    }

    public synchronized int getSize() {
        return personneVector.size();
    }

    /**
     * Programme qui permet de tester le fonctionnement de la classe
     * <code>DataManager</code> et de ses op�rations de gestion de
     * personnes.
     */
    public static void main(String argv[]) {
        DataManager dm = new DataManager();
        Personne p;
        int id;

        System.out.println("\n** Remplissage de la liste **\n");

        p = new Personne(29, "Gérard");
        id = dm.addPersonne(p);
        System.out.println("- Ajout de % " + p + " % avec identifiant = " + id);

        p = new Personne(20, "Marie");
        id = dm.addPersonne(p);
        System.out.println("- Ajout de % " + p + " % avec identifiant = " + id);

        p = new Personne(42, "Saturnin");
        id = dm.addPersonne(p);
        System.out.println("- Ajout de % " + p + " % avec identifiant = " + id);

        p = new Personne(40, "Evane");
        id = dm.addPersonne(p);
        System.out.println("- Ajout de % " + p + " % avec identifiant = " + id);

        /*System.out.println("\n**************************************************\n");
        System.out.println("\n** Interrogation de la liste **\n");
        try {
            p = dm.getPersonne(dm.getId(new Personne(40, "Evane")));
            System.out.println("- Personne d'identificateur 40 = " + p);
        } catch (InvalidIdException e) {
            System.err.println("[Erreur] Personne d'identificateur 2 : " + e);
        }

        System.out.println("\n**************************************************\n");

        System.out.println("- Identificateur de Gérard, 29 ans = " + dm.getId(new Personne(29, "Gérard")));
        System.out.println("- Identificateur de Saturnin, 42 ans = " + dm.getId(new Personne(42, "Saturnin")));
        System.out.println("- Identificateur de Marie, 20 ans = " + dm.getId(new Personne(20, "Marie")));
        System.out.println("- Identificateur de Evane, 40 ans = " + dm.getId(new Personne(40, "Evane")));*/

        for (Object o : personneVector) {
            System.out.print(o + "\n");
        }
    }
}
