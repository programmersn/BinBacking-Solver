/** INF24 PROJET PACKING
 * 	DIALLO-SOUIKI, 2011/2012
 * 
 * Procédures pour la recherche d'un remplissage du conteneur.
 *************************************************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "lecture_probleme.h"
#include "recherche_remplissage.h"
#include "remplir_bande.h"
#include "utiles.h"

int* Occs = NULL;
ENSEMBLE_SOLUTIONS Meilleur_Remplissage = NULL;
int surface_max = 0, largeur_max_objet;
int nb_solutions;
int **Pile_C = NULL;
unsigned char tri = 0, occs = 0, pivot = 0, sac = 0, coupes = 0, imbrique = 0;
unsigned char hmin = 0;


unsigned char CasTrivial (int *O)
{
	int i;

	/* L'instance se réduit à un seul objet */
	if (nb_obj == 1  &&  EstValide (0, largeur_conteneur, hauteur_conteneur)) {
		int l = Obj_Genere[0]->l, h = Obj_Genere[0]->h;
		O[0] = NONE;
		SauvegarderMeilleurRemplissage (O);
		surface_max = l*h;
		return 1;
	}
	
	/* Un objet remplit tout */
	for (i = 0; i < nb_obj; i++) {
		int l = Obj_Genere[i]->l, h = Obj_Genere[i]->h;
		if (l == largeur_conteneur && h == hauteur_conteneur) {
			O[i] = NONE;
			SauvegarderMeilleurRemplissage (O);
			surface_max = l*h;
			return 1;
		}
		if (pivot && l == hauteur_conteneur && h == largeur_conteneur) {
			Pivoter (i);
			O[i] = NONE;
			SauvegarderMeilleurRemplissage (O);
			surface_max = l*h;
			return 1;
		}
	}

	return 0;
}

void  RemplirConteneur (int largeur_restante, int *O, int largeur_exploration, 
												int profondeur)
{
	int numero_bande, k = largeur_exploration;

	if (coupes && profondeur > 0) {
		if (CoupureRemplissagePartiel (O, largeur_restante)) {
			LibererObjets (O, profondeur-1);
			return;
		}
		if (CoupureRemplissageTotal ()) {
			LibererObjets (O, profondeur-1);
			return;
		}
	}

	if (occs) 
		k = Selectionner_k_LargeursValides (O, k, largeur_restante, profondeur);							
 	else
		k = Selectionner_k_LargeursValidesParDefaut (O, k, largeur_restante,
																								 profondeur);

	if (k == 0) {
			UpdateMeilleurRemplissage(O);
		return;
	}

	for (numero_bande = 0; numero_bande < k; numero_bande++) {
		int e, largeur_max_mise, decalage;
		static int largeur_max_mise_prec;

		e = Extraire_e_de_C (largeur_restante, profondeur, numero_bande);
		if (e == NONE) continue;
		if (sac) {
			largeur_max_mise = RemplirBandeSacADos (O, e, largeur_restante, 
																							profondeur);
		} else {
			largeur_max_mise = RemplirBandeGlouton (O, e, largeur_restante,
																							profondeur);
		}

/*	AfficherTrace (profondeur, k, numero_bande, e, __LINE__,
										 "RemplirConteneur"); */

		if (imbrique && profondeur > 0) {
			decalage = ImbriquerBandes (largeur_max_mise_prec, profondeur);

			largeur_max_mise -= decalage;
			largeur_max_mise_prec = largeur_max_mise;
		}		

		RemplirConteneur (largeur_restante-largeur_max_mise, O, largeur_exploration,
											profondeur+1);

		LibererObjets (O, profondeur);
	}
}

void LibererObjets (int *O, int profondeur)
{
	int i, obj;
	int *Objets_Pris = Pile_Objets_Pris[profondeur];
	assert (Objets_Pris);

	for (i = 0; i < nb_obj && Objets_Pris[i] != NONE; i++) {
		obj = Objets_Pris[i];
		O[obj] = obj;
		Objets_Pris[i] = NONE;
	}
}


/** --------------------- T R I   O B J E T S --------------------------------*/  

void TrierLargeursObjets ()
{
	int i, n = nb_obj;
		
	ConstruireTasObjs (n);

	for(i = n-1; i > 0; i--) {
		PermuterObjs (0, i);
		EntasserObjs(0, i);
	}
}

void ConstruireTasObjs (int n)
{
	int i = 0;
	
	for(i = (n/2)-1; i >= 0; i--)
		EntasserObjs(i, n);
}

void EntasserObjs (int i, int n)
{
	int i_max = i;
	
	if (2*i+1 < n  &&  Obj_Genere[2*i+1]->l > Obj_Genere[i_max]->l)
		i_max = 2*i + 1;	

	if (2*i+2 < n  &&  Obj_Genere[2*i+2]->l > Obj_Genere[i_max]->l)
		i_max = 2*i + 2;

	if (i_max != i) {
		PermuterObjs (i, i_max);
		EntasserObjs(i_max, n);
	}
}

void PermuterObjs (int i, int j)
{
	struct OBJET *tmp = NULL; 
	
	tmp = Obj_Genere[i]; assert(tmp != NULL);
	Obj_Genere[i] = Obj_Genere[j];
	Obj_Genere[j] = tmp;
}


/** --------------------------------------------------------------------------*/

int
Selectionner_k_LargeursValidesParDefaut (int *O, int k, int largeur_restante,
																				 int profondeur)
{
	int Bandes_Par_Defaut[3] = {10, 20, 30};
	int i, bandes_dix = 0, bandes_vingt = 0, bandes_trente = 0;
	int *Largeurs_Valides = Pile_C[profondeur];
	assert (Largeurs_Valides);
	
	for(i = 0; i < nb_obj; i++) {
		if(O[i] != NONE && Bandes_Par_Defaut[0] <= largeur_restante
			 && EstValide (i, Bandes_Par_Defaut[0], hauteur_conteneur))		
			bandes_dix++;
	
		else if(O[i] != NONE && Bandes_Par_Defaut[1] <= largeur_restante
				    && EstValide (i, Bandes_Par_Defaut[1], hauteur_conteneur))
			bandes_vingt++;
			
		else if(O[i] != NONE && Bandes_Par_Defaut[2] <= largeur_restante
				    && EstValide (i, Bandes_Par_Defaut[2], hauteur_conteneur))
			bandes_trente++;
	}

	i = 0;
	if(bandes_dix) {
		Largeurs_Valides[i] = Bandes_Par_Defaut[0];
		i++;
	}
	if(bandes_vingt) {
		Largeurs_Valides[i] = Bandes_Par_Defaut[1];
		i++;
	}
	if(bandes_trente) {
		Largeurs_Valides[i] = Bandes_Par_Defaut[2];
		i++;
	}
	k = i;
	
	return k;
}


/**		
----------	S E L E C T I O N   D E S   B A N D E S   P A R  -----------------  
						              O C C U R R E N C E S 	
*/

int Selectionner_k_LargeursValides (int *O , int k, int largeur_restante, 
												            int profondeur)
{
	int nb_largeurs_select = 0, i;
	int *Largeurs_Valides = Pile_C[profondeur];
	assert (Largeurs_Valides);

	CalculerOccs (O, largeur_restante);

	while (nb_largeurs_select < k) {
		int l = SelectLargeurLaPlusFrequente ();
		if (l == 0 || AucunObjetValide(O, l, largeur_restante)) break;
		Largeurs_Valides[nb_largeurs_select] = l; nb_largeurs_select++;
		Occs[l] = 0;
	}

	return nb_largeurs_select;
}

void CalculerOccs (int *O, int largeur_restante)
{
	int i;

	InitialiserOccs ();
	
	for (i = 0; i < nb_obj; i++) {
		int l = Obj_Genere[i]->l;
		if (O[i] != NONE && l <= largeur_restante)
			Occs[l]++;
	}
}

void InitialiserOccs ()
{
	int l;

	for (l = 0; l <= largeur_max_objet; l++)
		Occs[l] = 0;
}

void CalculerLargeurMax ()
{
	int i;
	
	largeur_max_objet = Obj_Genere[0]->l;

	for (i = 1; i < nb_obj; i++)
		if (largeur_max_objet < Obj_Genere[i]->l)
			largeur_max_objet = Obj_Genere[i]->l;
}

int SelectLargeurLaPlusFrequente ()
{
	int largeur_plus_freq = 0, l;

	for (l = 0; l <= largeur_max_objet; l++)
		if (Occs[l] != 0 && Occs[largeur_plus_freq] < Occs[l])
			largeur_plus_freq = l;

	

	return largeur_plus_freq;
}

unsigned char AucunObjetValide (int *O, int l, int largeur_restante)
{
	int i;
	
	for (i = 0; i < nb_obj; i++)
		if (O[i] == i              &&
		    Obj_Genere[i]->l <= l  &&
		    Obj_Genere[i]->h <= hauteur_conteneur) {
		
			return 0;
		}
		
	return 1;
}


/** --------------------------- C O U P U R E S ------------------------------*/

unsigned char CoupureRemplissagePartiel (int *O, int largeur_restante)
{
	int surface_totale_courante = (largeur_conteneur-largeur_restante) *
																hauteur_conteneur;

	int surface_libre_courante  = surface_totale_courante - 
													      CalculSurfaceOccupee (O);
	
	int surface_conteneur = largeur_conteneur*hauteur_conteneur;
	int surface_libre_meilleur_remplissage = surface_conteneur - surface_max;

	if(surface_libre_courante >= surface_libre_meilleur_remplissage)
		return 1;
	
	return 0;
}

unsigned char CoupureRemplissageTotal ()
{
	return surface_max == largeur_conteneur*hauteur_conteneur;
}


/** -------------- I M B R I C A T I O N   D E S   B A N D E S ---------------*/

int ImbriquerBandes (int largeur_max_mise_prec, int profondeur)
{
	int lmmp = largeur_max_mise_prec;
	int* Objs_Cour = Pile_Objets_Pris[profondeur];
	int* Objs_Prec = Pile_Objets_Pris[profondeur-1];
	int nb_objs_prec = 0, nb_objs_cour = 0;
	int p;								/* Curseur sur objs bande precédente */
	int c; 								/* Curseur sur objs bande courante */
	int decalage = 0;			/* Décalage sur l'ensemble de la bande courante */
	int i;

	/* Calcul du nb d'objs dans les 2 bandes */
	for (i = 0; Objs_Prec[i] != NONE; i++)
		nb_objs_prec++;
	for (i = 0; Objs_Cour[i] != NONE; i++)
		nb_objs_cour++;

	if (profondeur%2 == 0)
		for (c = 0; c < nb_objs_cour && Objs_Cour[c] != NONE; c++)
			for (p = nb_objs_prec-1; p >= 0; p--)
				if (EstDecalable (Objs_Cour[c], Objs_Prec[p], lmmp)) {
					printf("obj%d décalable\n", Objs_Cour[c]);
					decalage = DecalerObjet (Objs_Cour[c], Objs_Prec[p], decalage);
					c++; p++;
				}
	else
		for (c = nb_objs_cour-1; c >= 0; c--)
			for (p = 0; p < nb_objs_prec && Objs_Prec[p] != NONE; p)
				if (EstDecalable (Objs_Cour[c], Objs_Prec[p], lmmp)) {
					printf("obj%d décalable\n", Objs_Cour[c]);
					decalage = DecalerObjet (Objs_Cour[c], Objs_Prec[p], decalage);
					c++; p++;
				}
	
	return decalage;
}

unsigned char EstDecalable (int o_cour, int o_prec, int lmmp)
{
	if (Coordonnees[o_cour]->y > Coordonnees[o_prec]->y   ||
			Obj_Genere[o_prec]->l == lmmp)
		return 0;

	return 1;
}

int DecalerObjet (int o_cour, int o_prec, int decalage)
{
	int nouv_decal = Coordonnees[o_cour]->x - Coordonnees[o_prec]->x
									 - Obj_Genere[o_prec]->l;

	Coordonnees[o_cour]->x  -=  nouv_decal;

	if(nouv_decal < decalage) return nouv_decal;
	return decalage;
}


/** --------------------------------------------------------------------------*/

void UpdateMeilleurRemplissage (int *O)
{
	int nouvelle_surface_occupee = CalculSurfaceOccupee(O);

	if (surface_max < nouvelle_surface_occupee) {
		surface_max = nouvelle_surface_occupee;
		SauvegarderMeilleurRemplissage (O);
	}
}

int CalculSurfaceOccupee (int *O) 
{
	int i;
	int surface_occupee = 0;

	for (i = 0; i < nb_obj; i++)
		if(O[i] == NONE) 
			surface_occupee += Obj_Genere[i]->l * Obj_Genere[i]->h;

	return surface_occupee;
}

void SauvegarderMeilleurRemplissage (int *O)
{
	int i, b = 0;

	for (i = 0; i < nb_obj; i++)
		if(O[i] == NONE) {		/* Si l'objet est dans le conteneur */
			strcpy (Meilleur_Remplissage[b]->nom, Obj_Genere[i]->nom);
			Meilleur_Remplissage[b]->l = Obj_Genere[i]->l;
			Meilleur_Remplissage[b]->h = Obj_Genere[i]->h;
			Meilleur_Remplissage[b]->x = Coordonnees[i]->x;
			Meilleur_Remplissage[b]->y = Coordonnees[i]->y;
			b++;
		}
		nb_solutions = b;
}

void AfficherSolutions ()
{
	int i;
	
	printf("\n%d %d\n%d\n", largeur_conteneur, hauteur_conteneur, nb_solutions);
	for(i = 0; i < nb_solutions; i++)
		printf("%s %d %d %d %d\n",  Meilleur_Remplissage[i]->nom, 
																Meilleur_Remplissage[i]->l, 
																Meilleur_Remplissage[i]->h,
																Meilleur_Remplissage[i]->x, 
																Meilleur_Remplissage[i]->y);

	printf("%d\n", surface_max);
	printf("%.3f\n\n",
				 100*(double)surface_max/(hauteur_conteneur*largeur_conteneur));
}
