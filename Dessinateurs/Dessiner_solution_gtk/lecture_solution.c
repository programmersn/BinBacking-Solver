#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "lecture_solution.h"

int nb_obj, hauteur_conteneur, largeur_conteneur;
double surface_max;

ENSEMBLE_SOLUTIONS Obj_Solution = NULL;

void LireSolutions ()
{
	int i;

	if(scanf("%d %d", &largeur_conteneur, &hauteur_conteneur) != 2) {
		fprintf(stderr, "LireSolutions : erreur lors de la lecture des "
							      "objets mis dans le conteneur. Abandon\n");
		exit(EXIT_FAILURE);
	}
	
	if(scanf("%d", &nb_obj) != 1) {			
		fprintf(stderr, "LireSolutions : erreur lors de la lecture des "
							 "objets mis dans le conteneur. Abandon\n");
		exit(EXIT_FAILURE);
	}

	Obj_Solution = AllouerEnsembleSolutions();
	
	for(i = 0; i < nb_obj; i++) {
		if(scanf("%s %d %d %d %d", Obj_Solution[i]->nom, 
															 &Obj_Solution[i]->l, 
															 &Obj_Solution[i]->h,
		                           &Obj_Solution[i]->x, 
		                           &Obj_Solution[i]->y) != 5) {
			fprintf (stderr, "LireSolutions : "
											 "erreur lors de la lecture des objets mis dans"
											 " le conteneur. Abandon\n");
			exit (EXIT_FAILURE);
		}
	}

	if(scanf("%lf", &surface_max) != 1) {
		fprintf(stderr, "LireSolutions : erreur lors de la lecture des "
							 "objets mis dans le conteneur. Abandon\n");
		exit(EXIT_FAILURE);
	}
}

ENSEMBLE_SOLUTIONS AllouerEnsembleSolutions () {
	ENSEMBLE_SOLUTIONS Bison = NULL;
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
