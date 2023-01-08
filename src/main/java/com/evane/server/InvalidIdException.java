package com.evane.server;

/**
 * Exception qui est lev�e quand on demande � r�cup�rer une personne �
 * partir d'un identifiant incorrect (c'est-�-dire quand aucune
 * personne ne poss�de cet identifiant).
 */
public class InvalidIdException extends Exception {
    /**
     * Cr�e une nouvelle exception
     * 
     * @param message le message d�crivant l'erreur
     */
    public InvalidIdException(String message) {
        super(message);
    }
}
