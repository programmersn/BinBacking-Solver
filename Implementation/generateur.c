/** INF24 PROJET PACKING
 * 	DIALLO-SOUIKI, 2011/2012
 * 
 * Generateur pseudo-aléatoire des instances de problèmes.
 * *******************************************************
 * 
 * Une instance est un objet rectangulaire.
 * On s'interdit qu'un objet puisse avoir une taille (largeur ou hauteur) 
 *  nulle.
 * 
 * Utilisation en ligne de commande : 
 * 	./generateur <largeur_conteneur> <hauteur_conteneur> <nombre objets>
 *  				     <largeur minimale objet> <largeur maximale objet> 
 *     			     <hauteur minimale objet> <hauteur maximale objet> 
 *							 [<semence>]
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (int argc, char *argv[]) 
{
  int i;
  int largeur_conteneur, hauteur_conteneur;
  int intervalle_largeur, intervalle_hauteur;
  int l_min, l_max, h_min, h_max, nb_obj;
  int semence = time(NULL);
	
  /* Gestion des erreurs de saisie. */
  if(argc > 9 || argc < 8) {
    fprintf(stderr, "%s : erreur nombre arguments.\n", argv[0]);
    fprintf(stderr, "Syntaxe :\n" 
	    "./generateur <largeur conteneur> <hauteur conteneur>\n"
	    "             <nombre objets>\n"
	    "             <largeur minimale objet> <largeur maximale objet>\n" 
	    "             <hauteur minimale objet> <hauteur maximale objet>\n"
	    "             [<semence>]\n\n"
	    "La semence vaut par défaut la date de géneration.\n");
    exit(EXIT_FAILURE);
  }
	
  /* Test de la validité des arguments : si ce sont bien 
     des entiers strictement positifs. */
  for (i = 1; argv[i] != NULL; i++)
    if (atoi (argv[i]) <= 0) {
      fprintf (stderr, "%s : argument \"%s\" incorrect.\n"
	       "Les arguments doivent être des entiers strictement "
	       "positifs.\n", argv[0], argv[i]);
      exit (EXIT_FAILURE);
    }
	
  /* Affectation des arguments */
  largeur_conteneur = atoi (argv[1]);
  hauteur_conteneur = atoi (argv[2]);
  nb_obj            = atoi (argv[3]); 
  l_min             = atoi (argv[4]);
  l_max             = atoi (argv[5]);
  h_min             = atoi (argv[6]);
  h_max             = atoi (argv[7]);
  if (argv[8] != NULL)
    semence         = atoi (argv[8]);
	
  /* Les tailles min doivent être inférieures aux tailles max */
  if (l_min > l_max || h_min > h_max) {
    fprintf(stderr, "%s : saisir tailles minimales strictement "
	    "inférieures à tailles maximales.\n", argv[0]);
    exit(EXIT_FAILURE);
  }
	
  /* Intervalles des tailles des objets */
  intervalle_largeur = l_max - l_min;
  intervalle_hauteur = h_max - h_min;
	
  /* Géneration des données du problème et affichage */
  srand(semence);
  printf ("%d %d\n", largeur_conteneur, hauteur_conteneur);
  printf ("%d\n", nb_obj); 
  for (i = 0; i < nb_obj; i++) {
    int val_l = intervalle_largeur == 0 ?
      l_min : (rand() % intervalle_largeur + 1) + l_min;
    int val_h = intervalle_hauteur == 0 ?
      h_min : (rand() % intervalle_hauteur + 1) + h_min;
    printf ("o%d %d %d\n", i, val_l, val_h);
  }
	
  return EXIT_SUCCESS;
}
