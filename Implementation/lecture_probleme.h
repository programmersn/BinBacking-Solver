/** INF24 PROJET PACKING
 * 	DIALLO-SOUIKI, 2011/2012
 */
#ifndef _LECTURE_PROBLEME_
#define _LECTURE_PROBLEME_

typedef struct OBJET {
	char nom[80];
	int l, h;
} **ENSEMBLE_OBJETS;

extern ENSEMBLE_OBJETS Obj_Genere;

extern int nb_obj, largeur_conteneur, hauteur_conteneur;

void LireProblemes ();

ENSEMBLE_OBJETS AllouerEnsembleObjets ();

#endif  /** _LECTURE_PROBLEME_*/
