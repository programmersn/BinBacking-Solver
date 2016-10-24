/* INF24 PROJET PACKING
 * 	 DIALLO-SOUIKI, 2011/2012
 */

#ifndef _RECHERCHE_REMPLISSAGE_
#define _RECHERCHE_REMPLISSAGE_
#define NONE -1

/** Structure qui sauvegarde l'identité d'un objet solution (ie un objet présent
    dans le conteneur */

typedef struct SOLUTION {
  char nom[80];
  int l, h;
  int x, y;
} **ENSEMBLE_SOLUTIONS ;

/** Ensemble des objets solutions */

extern ENSEMBLE_SOLUTIONS Meilleur_Remplissage;

/** Tableau des occurrences des largeurs de objets */

extern int *Occs;

/** Largeur maximale parmi les objets de l'instance */

extern int largeur_max_objet;

/** Pile des largeurs valides */

extern int **Pile_C;

/** Flags de la commande */

extern unsigned char tri, occs, pivot, sac, coupes, imbrique, hmin;

/** Cas trivial : un seul obj dans l'instance, ou un objet remplit à lui-seul
    le conteneur */

unsigned char CasTrivial (int *O);	

/** Procédure de recherche */

void RemplirConteneur (int largeur_restante, int *O, int largeur_exploration,
		       int profondeur);

/** Libération des objets de la dernière bande remplie */

void LibererObjets (int *O, int profondeur);

/** Sélectionne 3 largeurs valides prédefinies dans {10, 20, 30} */  

int Selectionner_k_LargeursValidesParDefaut (int *O, int k, 
					     int largeur_restante,
					     int profondeur);

/** Tri des objets suivant leur largeurs : tri par tas. */

void TrierLargeursObjets ();
void ConstruireTasObjs   (int n);
void EntasserObjs        (int i, int n);
void PermuterObjs        (int i, int j);


/** Selection des largeurs suivant leurs occurrences */

/* Prend en paramètre la largeur d'exploration k, et renvoie dans cette même
   variable le nombre de largeurs effectivement sélectionnées.  */

int Selectionner_k_LargeursValides (int *O , int k, int largeur_restante, 
				    int profondeur);
																		
/* Calcule la plus grande largeur parmi les objets de l'instance
   (utile pour l'allocation de Occs) */
		
void CalculerLargeurMax    ();

/* Initialise Occs[] à 0 */

void InitialiserOccs       ();

/* Calcule les occurrences des largeurs des objets libres */

void CalculerOccs    		   (int *O, int largeur_restante);

/* Renvoie la largeur la plus fréquente parmi les objets libres */

int  SelectLargeurLaPlusFrequente ();

/* Vérifie qu'un objet au-moins est valide pour la bande de largeur l */

unsigned char AucunObjetValide (int *O, int l, int largeur_restante);


/** Coupures */

/* Applique la propriété de la coupure sur le remplissage partiel */

unsigned char CoupureRemplissagePartiel (int *O, int largeur_restante);

/* Coupe l'algorithme si un remplissage de 100% est atteint */

unsigned char CoupureRemplissageTotal   ();


/** Imbrication des bandes deux par deux */

/* Imbrique la bande courante avec la bande précedente */

int ImbriquerBandes (int largeur_max_mise_prec, int profondeur);

/* Vérifie qu'un objet est décalable vers la bande précédente */

unsigned char EstDecalable (int obj_courant, int obj_prec,
			    int largeur_max_mise_prec);

int DecalerObjet (int obj_courant, int obj_prec, int decalage);


/** Utilitaires pour la recherche */

/* Met à jour le meilleur remplissage éventuel atteint à la feuille courante */

void   UpdateMeilleurRemplissage        (int *O);

/* Calcul de la surface occupée par les objets présents dans le conteneur */

int    CalculSurfaceOccupee             (int *O);

/* Sauvegarde les objets présents dans le conteneur, en tant qu'objets
   solutions */
		
void   SauvegarderMeilleurRemplissage   (int *O);

/* Affiche les objets du meilleur remplissage */

void   AfficherSolutions                ();


#endif  /** _RECHERCHE_REMPLISSAGE_ */
