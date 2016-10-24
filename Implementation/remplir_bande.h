/** INF24 PROJET PACKING
 * 	 DIALLO-SOUIKI, 2011/2012
 */

#ifndef _REMPLIR_BANDES_
#define _REMPLIR_BANDES_


/** Structure sauvegardant les coordonnées d'un objet dans le conteneur.
	   L'origine du repère est le coin inférieur gauche du conteneur, l'unité est
	   pixel. 
*/

typedef struct COORDONNEE {
	int x, y;
} **COORDONNEES;


/** Ensemble des coordonnées de tous les objets */

extern COORDONNEES Coordonnees;


/** Pile des tableaux des objets mis dans le conteneur :
  	 un tableau dans la pile à une profondeur contient les objets mis dans une
  	 bande à cette profondeur */

extern int **Pile_Objets_Pris;


/** Tableaux pour le sac à dos */

extern int *Candidats, *Poids, *Gain, **A;


/** Remplissage d'une bande de manière glouton */

int RemplirBandeGlouton (int *O, int e, int largeur_restante, int profondeur);


/**
   Remplir une bande e avec sac à dos :
		candidats    := objets valides pour e.
		capacite sac := hauteur conteneur
		poids objet  := hauteur objet
		gain objet   := surface objet 
*/

/* Remplir bande suivant une stratégie de sac à dos */

int RemplirBandeSacADos (int *O, int e, int largeur_restante, int profondeur);

/* Elit les objets pouvant être mis dans une bande */

int ChoisirCandidatsSacADos (int *O, int e);

/* Remplir la table de programmation dynamique des gains */

void RemplirTableSacADos    (int nb_candidats);

/* Retrouve les solutions mis dans le sac (bande), depuis la table des
		profits */

int ReconstruireSolutions   (int *O, int nb_candidats, int largeur_restante,
														 int profondeur);


/** Utilitaires pour le remplissage d'une bande */

/* Extrait une largeur de bande depuis la pile des largeurs valides */

int Extraire_e_de_C (int largeur_restante, int profondeur, int numero_bande);

/* Calcule les coordonnées des objets dans le conteneur, en fonction que le
    remplissage de la bande courante se fasse depuis le bas ou depuis le haut
    (pour l'imbrication des bandes) */
    
void CalculerCoordObjet (int objet, int largeur_restante, int hauteur_restante,
												 int profondeur) ;

/* Décide si un objet est valide pour les dimensions largeur et hauteur */

unsigned char EstValide (int i, int largeur, int hauteur);

/* Pivote un objet si cela lui permet d'être valide */

void Pivoter (int objet);


#endif  /** _REMPLIR_BANDES_ */
