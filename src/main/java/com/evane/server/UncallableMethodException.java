package com.evane.server;

/**
 * Exception lev�e quand, pour une raison quelconque, on a pas pu
 * appeler une m�thode ou que son appel s'est mal pass�
 */
public class UncallableMethodException extends Exception {

    public UncallableMethodException(String msg) {
        super(msg);
    }

}
