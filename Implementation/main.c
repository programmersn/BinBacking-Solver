/** INF24 PROJET PACKING
 * 	DIALLO-SOUIKI, 2011/2012
 * 
 * Programme principal
 ************************
 * Usage : 
 *
 *		./remplir_conteneur [tri] [-pivot] [-sac] [-occs [k]] [-coupes]
 * 												[-imbrique]
 * 
 *  L'entrée standard doit être redirigée depuis un fichier d'instances
 *   bien formé.
*/

#include <stdio.h>
#include <stdlib.h>
#include "lecture_probleme.h"
#include "recherche_remplissage.h"
#include "remplir_bande.h"
#include "utiles.h"

int main (int argc, char *argv[]) 
{
	int largeur_exploration = AnalyserCommande (argc, argv);
	int profondeur = 0;			/* Profondeur de l'arbre de recherche */
	int *O;									/* O := Ensemble des objets libres */

	LireProblemes ();

	O = AllouerTableaux ();

	if (CasTrivial (O))
		goto Sol;
		
	if (tri || imbrique)		/* L'imbrication des bandes requiert le tri */
		TrierLargeursObjets ();

	RemplirConteneur (largeur_conteneur, O,  largeur_exploration, profondeur);

	Sol : AfficherSolutions ();

	return EXIT_SUCCESS;
}
