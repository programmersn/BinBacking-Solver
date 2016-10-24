/** INF24 PROJET PACKING
 * 	 DIALLO-SOUIKI, 2011/2012
 * 
 * Procédure utiles.
 * *****************
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "utiles.h"
#include "lecture_probleme.h"
#include "recherche_remplissage.h"
#include "remplir_bande.h"

void AfficherUsage ()
{
  fprintf(stderr, 
	  "Usage : ./remplir_conteneur -help\n"
	  "        ./remplir_conteneur [-occs [k]] [-pivot] [-hmin] [-coupes] [-sac] "
	  "[imbrique]\n\n"
	  "Avec :\n"
	  "      -help : affiche cette usage et se termine.\n"
	  "      -tri  : tri les objets de l'instance selon leurs largeurs.\n"
	  "      -occs : remplit des bandes dont les largeurs correspondent aux "
	  "dimensions des objets les plus fréquentes (par défaut remplit des "
	  "largeurs de dix, vingt et trente).\n");
  fprintf(stderr,
	  "       	 k : largeur d'exploration pour le remplissage par occurrences."
	  " (entier strictement positif), par défaut 3.\n"
	  "              A T T E N T I O N ! : ce dernier arguement ne peut être "
	  "saisi que comme complément à l'argument `-occs'.\n\n"
	  "       -sac : remplit chaque bande par un algorithme de sac à dos.\n");
  fprintf(stderr,
	  "  -imbrique : réalise un remplissage de bandes par alternance, en "
	  "imbriquant les bandes deux par deux au fur et à mesure.\n"
	  "      -hmin : favorise la hauteur minimale d'un objet, au moment de "
	  "son placement dans une bande.\n"
	  "     -pivot : pivote les objets si nécessaire.\n"
	  "    -coupes : applique certaines propriétés de coupure (coupe sur le "
	  "remplissage partiel, coupe sur le remplissage total).\n");
}

int AnalyserCommande (int argc, char *argv[])
{	
  int largeur_exploration = 3, i = 1;
	
  if(argc > 8) {
    fprintf(stderr, "%s : erreur de syntaxe\n\n", argv[0]);
    AfficherUsage ();
    exit(EXIT_FAILURE);
  }
  if(argc == 2 && strcmp(argv[1], "-help") == 0) {
    AfficherUsage ();
    exit(EXIT_SUCCESS);
  }

  while (argv[i] != NULL) {
    if (strcmp (argv[i], "-pivot") == 0)
      pivot = 1;
    else if (strcmp (argv[i], "-tri") == 0)
      tri = 1;
    else if (strcmp (argv[i], "-hmin") == 0)
      hmin = 1;
    else if (strcmp (argv[i], "-sac") == 0)
      sac = 1;
    else if (strcmp (argv[i], "-coupes") == 0)
      coupes = 1;
    else if (strcmp (argv[i], "-imbrique") == 0)
      imbrique = 1;
    else if (strcmp (argv[i], "-occs") == 0) {
      occs = 1; 
      if (argv[i+1]) {
	if (atoi (argv[i+1]) <= 0) { 
	  i++; 
	  continue;
	}
	else { 
	  largeur_exploration = atoi (argv[i+1]);
	  i++;
	}
      }
    }
    else {
      fprintf(stderr, "%s : \"%s\" : argument invalide\n\n", argv[0], argv[i]);
      AfficherUsage ();
      exit(EXIT_FAILURE);
    }
    i++;
  }
	
  return largeur_exploration;
}

int* AllouerTableaux ()
{
  int i, j, *O = NULL;

  /* Ensemble des objets libres */
  O = malloc (nb_obj * sizeof *O);
  assert (O);
	
  /* Piles */
  Pile_Objets_Pris = malloc (nb_obj * sizeof *Pile_Objets_Pris); 
  assert (Pile_Objets_Pris != NULL);
	
  Pile_C = malloc (nb_obj * sizeof *Pile_C); 
  assert (Pile_C);
	
  /* Tableaux des objets constituant le meilleur remplissage */
  Meilleur_Remplissage = malloc (nb_obj * sizeof *Meilleur_Remplissage); 
  assert (Meilleur_Remplissage);
	
  /* Coordonnées d'un objet dans le conteneur */
  Coordonnees = malloc (nb_obj * sizeof *Coordonnees);
  assert (Coordonnees);

  /* Tableau des occurrences des objets */
  if(occs) {
    CalculerLargeurMax();
    Occs = malloc ((largeur_max_objet+1) * sizeof *Occs);
    assert (Occs);
  }
	
	
  /* Tableaux pour le sac à dos */
  if (sac) {
    Candidats = malloc ((nb_obj+1) * sizeof *Candidats);
    assert (Candidats);
		
    Poids = malloc ((nb_obj+1) * sizeof *Poids);
    assert (Poids);

    Gain = malloc ((nb_obj+1) * sizeof *Gain);
    assert (Gain);
		
    A = malloc ((nb_obj+1) * sizeof *A);
    assert (A);
    for (i = 0; i <= nb_obj; i++) {
      A[i] = malloc ((hauteur_conteneur+1) * sizeof *A[i]);
      assert(A[i]);
    }
  }
	
  for(i = 0; i < nb_obj; i++) {
    Coordonnees[i] = malloc (sizeof *Coordonnees[i]);
    assert(Coordonnees[i]);
		
    Meilleur_Remplissage[i] = malloc (sizeof *Meilleur_Remplissage[i]);
    assert(Meilleur_Remplissage[i]);
		
    Pile_Objets_Pris[i] = malloc (nb_obj * sizeof *Pile_Objets_Pris[i]);
    assert(Pile_Objets_Pris[i]);
		
    Pile_C[i] = malloc (nb_obj * sizeof *Pile_C[i]);
    assert(Pile_C[i]);

    O[i] = i;
		
    for(j = 0; j < nb_obj; j++) {
      Pile_Objets_Pris[i][j] = NONE;
      Pile_C[i][j] = NONE;
    }
  }
	
  return O;
}

void AfficherTrace (int profondeur, int k, int numero_bande, int e, 
		    int ligne, const char nom_fonction[]) 
{
  int p = profondeur, i;
	
  printf("************ L.%d dans \"%s()\" ************\n", ligne,
	 nom_fonction);
  printf("\tProfondeur : %d, k = %d,  e = %d,  bande n°%d", profondeur,
	 k, e, numero_bande);
	
  printf("\tPile_C[%d] : ", p);
  for(i = 0; i < k; i++) 
    printf("%d ", Pile_C[p][i]);

  printf("\n\n");
	
  printf("\tPile_Objets_Pris[%d] : ", p);
  for(i = 0; i < nb_obj; i++) 
    printf("%d ", Pile_Objets_Pris[p][i]);

  printf("\n\n");
}
	
