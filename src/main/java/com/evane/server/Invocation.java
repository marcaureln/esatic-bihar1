package com.evane.server;


import java.lang.reflect.Method;
import java.util.Scanner;

/**
 * Objet "invocateur" qu'on associe � un objet, objet sur lequel on
 * appelera dynamiquement des m�thodes � partir de leurs nom et
 * param�tres.
 */
public class Invocation {
	/**
	 * L'objet sur lequel on appelera les m�thodes
	 */
	protected Object cible;

	/**
	 * Invoque dynamiquement une m�thode sur l'objet cible
	 * 
	 * @param nomMethode le nom de la m�thode
	 * @param types      la liste des types des param�tres. Note : on ne
	 *                   d�termine pas automatiquement la liste des types � partir
	 *                   de la liste des param�tres puisqu'il faut pouvoir
	 *                   explicitement diff�rencier, par exemple, le cas entre la
	 *                   classe "Integer" et le type primitif "int" (repr�sent�
	 *                   alors par la valeur Integer.TYPE) et qu'on aura dans les 2
	 *                   cas
	 *                   une instance de la classe Integer en tant que param�tre.
	 * @param params     la liste des param�tres
	 * @exception Exception deux cas sont � diff�rencier :
	 *                      <ol>
	 *                      <li>Un probl�me a eu lieu pour appeler la m�thode
	 *                      (param�tres non corrects, acc�s interdit, pas de
	 *                      m�thode de ce nom l� ...) une exception
	 *                      <code>UncallableMethodException</code> est alors
	 *                      lev�e</li>
	 *                      <li>L'appel a bien eu lieu correctement mais la m�thode
	 *                      a
	 *                      lev� une exception, cette exception est alors lev�e �
	 *                      nouveau (d'o� le type g�n�rique <code>Exception</code>
	 *                      dans la signature de la m�thode puisqu'on ne peut lever
	 *                      n'importe quelle exception)</li>
	 *                      </ol>
	 *                      .
	 */
	public Object invoquer(String nomMethode, Class types[], Object params[]) throws Exception {

		Method met = null;
		Object result = null;
		Class cl;

		// recupere la classe de l'objet a invoquer
		cl = cible.getClass();

		// recupere la methode a appeler si elle existe
		// sinon renvoie une exception
		try {
			met = cl.getMethod(nomMethode, types);
		} catch (java.lang.NoSuchMethodException e) {
			throw new UncallableMethodException("Methode inexistante [" + e.getMessage() + "]");
		}

		try {
			// la m�thode est trouv�e, on l'invoque dynamiquement
			result = met.invoke(cible, params);
		} catch (java.lang.IllegalAccessException e) {
			throw new UncallableMethodException("Acces interdit a la methode [" +
					e.getMessage() + "]");
		} catch (java.lang.reflect.InvocationTargetException e) {
			// la methode a leve une exception, on la leve
			// System.out.println("Exception levee : "+e.getCause()+" type =
			// "+e.getCause().getClass());
			throw (Exception) e.getCause();
		}

		return result;
	}

	/**
	 * @param cible l'objet sur lequel on appelera les m�thodes
	 */
	public Invocation(Object cible) {
		this.cible = cible;
	}

	// petit programme de test
	/**
	 * @param argv
	 */
	public static void main(String argv[]) {
		Invocation invoc = new Invocation(new DataManager());
		int enter = 1;

		// addPersonne
		// getId
		// getPersonne

		while (enter  == 1) {
			
			Scanner option = new Scanner(System.in);
			System.out.println("Choisissez une Option du Menu : \n (1):addPersonne \n (2):getId \n (3):getPersonne \n =>");
			int ops = option.nextInt();
	
			switch (ops) {
				case 1:
					try {
						/* client */
						Scanner sai_name = new Scanner(System.in);
						System.out.println("Nom : ");
						String name = sai_name.nextLine();

						Scanner sai_age = new Scanner(System.in);
						System.out.println("Age : ");
						int age = sai_age.nextInt();

						/* appel du serveur */
						Personne p = new Personne(age, name);

						String nom = "addPersonne";
						Object param[] = { p };
						Class types[] = { p.getClass() };
	
						Object res = invoc.invoquer(nom, types, param);
						System.out.println(" Resultat : " + res);
						/* fin appel du serveur */

					} catch (Exception e) {
						System.err.println("Erreur : " + e);
					}
					break;
				case 2:
					try {
						Scanner sai_name = new Scanner(System.in);
						System.out.println("Nom : ");
						String name = sai_name.nextLine();

						Scanner sai_age = new Scanner(System.in);
						System.out.println("Age : ");
						int age = sai_age.nextInt();

						Personne p = new Personne(age, name);

						String nom = "getId";
						Object param[] = { p };
						Class types[] = { p.getClass() };
	
						Object res = invoc.invoquer(nom, types, param);
						System.out.println(" Resultat : " + res);
					} catch (Exception e) {
						System.err.println("Erreur : " + e);
					}
					break;
				case 3:
					try {
						Scanner sai_name = new Scanner(System.in);
						System.out.println("Nom : ");
						String name = sai_name.nextLine();

						Scanner sai_age = new Scanner(System.in);
						System.out.println("Age : ");
						int age = sai_age.nextInt();

						Personne p = new Personne(age, name);	
						Object param[] = { p };
						Class types[] = { p.getClass() };
	
						param = new Object[1];
						param[0] = Integer.valueOf(0);
						types = new Class[1];
						types[0] = Integer.TYPE;
						Object res = invoc.invoquer("getPersonne", types, param);
						System.out.println(" Resultat : " + res);
					} catch (Exception e) {
						System.err.println("Erreur : " + e);
					}
					break;
	
				default:
					break;
			}

			Scanner exit = new Scanner(System.in);
			System.out.println("Voulez-Vous continuez ? : \n (0):non \n (1):oui \n =>");
			int ext = exit.nextInt();

			if (ext == 1) {
				enter = 1;
			} else {
				enter = 0;
			}

		}
	}
}
