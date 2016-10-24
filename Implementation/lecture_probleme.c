/** INF24 PROJET PACKING
 * 	 DIALLO-SOUIKI, 2011/2012
 * 
 * Lecture des instance de problème.
 * *********************************	
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "lecture_probleme.h"

ENSEMBLE_OBJETS Obj_Genere;
int nb_obj, largeur_conteneur, hauteur_conteneur;


void LireProblemes () 
{
	int i;
	
	/* Tailles du conteneur */
	if(scanf("%d %d", &largeur_conteneur, &hauteur_conteneur) != 2) {
		fprintf(stderr,
					  "LireProblemes : erreur lors de la lecture des objets genérés :"
						" dimensions du conteneur incorrectes. Abandon.\n");
		exit(EXIT_FAILURE);
	}
	
	/* Nombre d'objets genérés */	
	if(scanf("%d", &nb_obj) != 1) {
		fprintf(stderr,
						"LireProblemes : erreur lors de la lecture des objets genérés :"
						" nombre d'objets incorrect. Abandon.\n");
		exit(EXIT_FAILURE);
	}
	
	Obj_Genere = AllouerEnsembleObjets();
	
	/* Noms et tailles des objets. */
	for(i = 0; i < nb_obj; i++) {
		if(scanf("%s %d %d", Obj_Genere[i]->nom, &Obj_Genere[i]->l,
		                     &Obj_Genere[i]->h) != 3) {
			fprintf(stderr,
					"LireProblemes : erreur lors de la lecture des objets genérés : "
					"identité d'objet incorrecte. Abandon.\n");
			exit(EXIT_FAILURE);
		}
	}
}

ENSEMBLE_OBJETS AllouerEnsembleObjets () {
	ENSEMBLE_OBJETS Bison = NULL;
	int i;
	
	Bison = malloc(nb_obj * sizeof(*Bison));
	assert(Bison != NULL);
	for(i = 0; i < nb_obj; i++)
		Bison[i] = NULL;
		
	for(i = 0; i < nb_obj; i++) {	
		Bison[i] = malloc(sizeof(*Bison[i]));
		assert(Bison[i] != NULL);
	}
	
	return Bison;
}
