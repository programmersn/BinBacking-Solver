#ifndef _LECTURE_SOLUTION_
#define _LECTURE_SOLUTION_

typedef struct SOLUTION {
	char nom[80];
	int  l, h;
	int  x, y;
} **ENSEMBLE_SOLUTIONS;

extern ENSEMBLE_SOLUTIONS Obj_Solution;

extern int nb_obj, hauteur_conteneur, largeur_conteneur;
extern double surface_max;

void LireSolutions ();
ENSEMBLE_SOLUTIONS AllouerEnsembleSolutions ();

#endif  /* _LECTURE_SOLUTION_ */
