package com.evane.server;

/**
 * Classe qui d�crit une personne. Impl�mente
 * <code>java.io.Serializable</code> car doit transiter � travers
 * des sockets et des flux.
 */
public class Personne implements java.io.Serializable {
    /**
     * Age de la personne
     */
    protected int age;

    /**
     * Nom de la personne
     */
    protected String nom;

    /**
     * Cr�e une nouvelle personne
     * 
     * @param a son age
     * @param n son nom
     */
    public Personne(int a, String n) {
        age = a;
        nom = n;
    }

    public String toString() {
        return ("nom : " + nom + ", age : " + age);
    }

    /**
     * Ne pas oublier de r�d�finir la m�thode <code>equals</code> pour
     * que la comparaison de personne fonctionne aussi sur des copies
     * d'objets (comme c'est le cas par principe quand ils transitent
     * � travers le r�seau et des flux)
     */
    public boolean equals(Object obj) {
        if (obj == null)
            return false;
        if (!(obj instanceof Personne))
            return false;

        Personne p = (Personne) obj;
        return ((age == p.age) && (nom.equals(p.nom)));
    }
}
