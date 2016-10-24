/** INF24 PROJET PACKING
 *  	DIALLO-SOUIKI, 2011/2012
 * 
 * Procédures pour remplir une bande donnée dans le conteneur.
 * ***********************************************************
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "remplir_bande.h"
#include "lecture_probleme.h"
#include "recherche_remplissage.h"

COORDONNEES Coordonnees = NULL;
int **Pile_Objets_Pris = NULL;

int Extraire_e_de_C (int largeur_restante, int profondeur, int numero_bande) 
{
	int e;
	int *Largeurs_Valides = Pile_C[profondeur];
	assert (Largeurs_Valides);
	
	e = Largeurs_Valides[numero_bande];
	if(e != NONE && e <= largeur_restante) {
		Largeurs_Valides[numero_bande] = NONE;
		return e;
	}
	return NONE;
}

void CalculerCoordObjet (int objet, int largeur_restante, int hauteur_restante,
												 int profondeur)
{
	if (profondeur%2 == 0 || ! imbrique) {	/* Remplissage depuis le bas */
		Coordonnees[objet]->x = largeur_conteneur - largeur_restante;
		Coordonnees[objet]->y = hauteur_conteneur - hauteur_restante;
	}
	else {		/* Alternance : remplissage depuis le haut */
		Coordonnees[objet]->x = largeur_conteneur - largeur_restante;
		Coordonnees[objet]->y = hauteur_restante  - Obj_Genere[objet]->h;
	}
}

unsigned char EstValide (int i, int largeur, int hauteur)
{
	int l_obj = Obj_Genere[i]->l, h_obj = Obj_Genere[i]->h;
	
	/* Privilégier une hauteur minimale dans la bande */
	if(hmin)
		if((h_obj > l_obj)  &&  (h_obj <= largeur && l_obj <= hauteur)) {
			Pivoter (i);
			return 1;
		}
				
	if(l_obj <= largeur && h_obj <= hauteur)
		return 1;		

	/*	 On vérifie que pour un objet	 
	(une taille est invalide)  */
	
	if(pivot) {
		if((l_obj > largeur)  &&  (h_obj <= largeur && l_obj <= hauteur)) {
			Pivoter(i);
			return 1;
		}
		else if((h_obj > hauteur)  &&  (l_obj <= hauteur && h_obj <= largeur)) {	
			Pivoter(i);
			return 1;
		}
	}

	return 0;
}

void Pivoter (int objet) {
	int l = Obj_Genere[objet]->l, h = Obj_Genere[objet]->h;
	
	Obj_Genere[objet]->l = h;
	Obj_Genere[objet]->h = l;
}


/** ----------- R E M P L I S S A G E    G L O U T O N -----------------------*/

int RemplirBandeGlouton (int *O, int e, int largeur_restante, int profondeur)
{
	int hauteur_restante = hauteur_conteneur;
	int i, j = 0, largeur_max_mise = 0;
	int *Objets_Pris = Pile_Objets_Pris[profondeur];
	assert (Objets_Pris);

	for(i = nb_obj-1; i >= 0 ; i--) 
		if(O[i] != NONE && EstValide(i, e, hauteur_restante)) {
			Objets_Pris[j] = i; j++;
			O[i] = NONE;							/* L'objet n'est plus libre */

			CalculerCoordObjet (i, largeur_restante, hauteur_restante, profondeur);

			hauteur_restante -= Obj_Genere[i]->h;
						
			if(Obj_Genere[i]->l > largeur_max_mise)
				largeur_max_mise = Obj_Genere[i]->l;
		}

	return largeur_max_mise;
}


/** ----------- R E M P L I S S A G E     S A C   A   D O S ------------------*/

int *Candidats = NULL, *Poids = NULL, *Gain = NULL, **A = NULL;

int RemplirBandeSacADos (int *O, int e, int largeur_restante, int profondeur)
{
	int nb_candidats = ChoisirCandidatsSacADos (O, e);
	int largeur_max_mise = 0;

	if ( ! nb_candidats) return largeur_max_mise;

	RemplirTableSacADos (nb_candidats);

	return ReconstruireSolutions (O, nb_candidats, largeur_restante, profondeur);
}

int ChoisirCandidatsSacADos (int *O, int e)
{
	int i, j, capacite_sac = hauteur_conteneur, nb_candidats = 0;

	/* Initialisation des structures */
	for (i = 0; i <= nb_obj; i++) {
		Candidats[i] = NONE;
		Poids[i] = NONE;
		Gain[i]  = NONE;
		for (j = 0; j <= hauteur_conteneur; j++)
			A[i][j] = NONE;
	}

	/* Sélection des candidats */
	for (i = 1; i <= nb_obj; i++)
		if (O[i-1] != NONE && EstValide (i-1, e, capacite_sac)) {
			Candidats [nb_candidats] = i-1;
			Poids     [nb_candidats] = Obj_Genere[i-1]->h;
			Gain      [nb_candidats] = Obj_Genere[i-1]->l * Obj_Genere[i-1]->h;
			
			nb_candidats++;
		}

	return nb_candidats;
}

void RemplirTableSacADos (int nb_candidats)
{
	int i, p, capacite_sac = hauteur_conteneur;

	for (p = 0; p <= capacite_sac; p++)
		A[0][p] = 0;

	for(i = 1; i <= nb_candidats; i++)  {/* printf("i=%d\n", i);*/
		for(p = 0; p <= capacite_sac; p++) {/* printf(" p=%d\n", p);*/
			A[i][p] = A[i-1][p];
			if(Poids[i] <= p && Gain[i] + A[i-1][p-Poids[i]] > A[i][p])
				A[i][p] = Gain[i] + A[i-1][p-Poids[i]];
		}
	}
}

int ReconstruireSolutions (int *O, int nb_candidats, int largeur_restante,
													 int profondeur)
{
	int i, p = hauteur_conteneur, j = 0, largeur_max_mise = 0;
	int hauteur_restante = hauteur_conteneur;
	int *Objets_Pris = Pile_Objets_Pris[profondeur];
	assert (Objets_Pris);
	
	for(i = nb_candidats; i >= 1; i--)
		if(Candidats[i] != NONE  &&  A[i][p] != A[i-1][p]) {
			Objets_Pris[j]  = Candidats[i]; j++;
			O[Candidats[i]] = NONE;									/* L'objet n'est plus libre */
			
	
			CalculerCoordObjet (Candidats[i], largeur_restante, hauteur_restante,
													profondeur);
														
			hauteur_restante -= Poids[i];

			if(largeur_max_mise < Obj_Genere[Candidats[i]]->l)
				largeur_max_mise = Obj_Genere[Candidats[i]]->l;

			p -= Poids[i];
		}

	return largeur_max_mise;
}
