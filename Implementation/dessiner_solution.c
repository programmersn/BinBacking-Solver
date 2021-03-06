/* INF24 PROJET PACKING
 *
 * Dessiner avec ez-draw la solution donnée par le programme packing.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ez-draw.h"
#include "dessiner_solution.h"

unsigned char txt_objs = 0, depuis_haut = 0;
double zoom = 4;

int main (int argc, char *argv[]) {
  Window win1;
  int i = 1;
   
  /** Ligne de commande */ 
  if(argc > 4) {
    fprintf(stderr, "%s : erreur de syntaxe.\n", argv[0]);
    PrintUsage ();
    exit(EXIT_FAILURE);
  }	
  while(argv[i] != NULL) {
    if(strcmp(argv[i], "--depuis-haut") == 0) depuis_haut = 1;
    else if(strcmp(argv[i], "--text-objs") == 0) txt_objs = 1;
    else if((zoom = strtod(argv[i], NULL)) <= 0.0) {
      fprintf(stderr, "%s : erreur de syntaxe.\n", argv[0]);
      PrintUsage ();
      exit(EXIT_FAILURE);
    }
    i++;
  }
	
  LireSolutions ();
    
  if (ez_init() < 0) 
    exit(1);
    
  win1 = ez_window_create (1100, 700, "Packing : dessin du meilleur"
			   " remplissage", win1_event);

  ez_main_loop ();
    
  return EXIT_SUCCESS;
}

void PrintUsage () {
  fprintf(stderr, "Usage : ./dessiner_solution [--depuis-haut] "
	  "[--text-objs] [Z]\n"
	  "Avec : \n"
	  "  --depuis-haut : dessine un remplissage depuis le haut du "
	  "conteneur (par defaut depuis le bas)\n"
	  "   --text-objs : affiche le nom des objets presents\n"
	  "              Z : zoom de dessin (reel arbitraire strictement"
	  " positif) par defaut 4.\n");
}

/** 
    Dessiner graphiqument les solutions du meilleur remplissage
*/
void win1_redessiner (Window win) {
  int i;
  unsigned long obj_color = ez_get_RGB (0, 112, 49);; 
	
  /* Affichage des caract�ristiques du conteneur */
  ez_set_nfont (2);
  ez_draw_text (win, EZ_TL, 0, 0, "Largeur du conteneur : %d\n"
		"Hauteur du conteneur : %d\n\n"
		"Nombre d'objets mis : %d\n",
		largeur_conteneur, 
		hauteur_conteneur, nb_obj);	
											  
  /* Affichage des caract�ristiques des solutions */
  if(txt_objs)
    for(i = 0; i < nb_obj; i++)
      ez_draw_text (win, EZ_TL, 0, 90 + 20*i, "%s %d %d %d %d\n", 
		    Obj_Solution[i]->nom, 
		    Obj_Solution[i]->l, Obj_Solution[i]->h, 
		    Obj_Solution[i]->x, Obj_Solution[i]->y);
  ez_draw_text (win, EZ_TL, 350, 0, "Surface occup�e : %.1f\n"
		"Soit : %.3f pourcent de la surface totale\n", 
		surface_max, pourcentage);

  /* Dessin du conteneur */
  ez_set_thick (3);
  ez_set_color (ez_get_RGB(0, 50, 20));
  ez_draw_rectangle (win, 320-2, 70-2, 320 + zoom*largeur_conteneur+2, 
		     70 +  zoom*hauteur_conteneur+2);
  /* Dessin des objets */
  if(depuis_haut) /* Dessin du remplissage depuis le haut */
    for(i = 0; i < nb_obj; i++) {			
      /* Contenu */
      ez_set_color (obj_color);
      ez_fill_rectangle (win,  
			 320 + zoom*Obj_Solution[i]->x, 
			 70 + zoom*Obj_Solution[i]->y, 
			 320 + zoom*(Obj_Solution[i]->l + Obj_Solution[i]->x),
			 70 + zoom*(Obj_Solution[i]->h + Obj_Solution[i]->y));
			
      /* Contours */
      ez_set_color(ez_white);
      ez_set_thick (1);
      ez_draw_rectangle (win, 
			 320 + zoom*Obj_Solution[i]->x, 
			 70 + zoom*Obj_Solution[i]->y, 
			 320 + zoom*(Obj_Solution[i]->l + Obj_Solution[i]->x),
			 70 + zoom*(Obj_Solution[i]->h + Obj_Solution[i]->y));
			
      /* Affiche sur chaque objet son nom */
      if(txt_objs) {
	ez_set_color(ez_white);
	ez_set_nfont (0);
	ez_draw_text (win, EZ_TL, 322 + zoom*Obj_Solution[i]->x, 
		      70 + zoom*Obj_Solution[i]->y, 
		      "%s", Obj_Solution[i]->nom);
      }
    }
  else /* Dessin des objets depuis le bas du conteneur */
    for(i = 0; i < nb_obj; i++) {
      /* Contenu */
      ez_set_color (obj_color);
      ez_fill_rectangle (win,  
			 320 + zoom*Obj_Solution[i]->x, 
			 70 + zoom*(hauteur_conteneur - Obj_Solution[i]->y), 
			 320 + zoom*(Obj_Solution[i]->l + Obj_Solution[i]->x),
			 70 + zoom*(hauteur_conteneur - Obj_Solution[i]->h - Obj_Solution[i]->y));
			
      /* Contours */
      ez_set_color(ez_white);
      ez_set_thick (1);
      ez_draw_rectangle (win, 
			 320 + zoom*Obj_Solution[i]->x, 
			 70 + zoom*(hauteur_conteneur - Obj_Solution[i]->y), 
			 320 + zoom*(Obj_Solution[i]->l + Obj_Solution[i]->x),
			 70 + zoom*(hauteur_conteneur - Obj_Solution[i]->h - Obj_Solution[i]->y));
			
      /* Affiche sur chaque objet son nom */
      if(txt_objs) {
	ez_set_color(ez_white);
	ez_set_nfont (0);
	ez_draw_text (win, EZ_TL, 322 + zoom*Obj_Solution[i]->x, 
		      55 + zoom*(hauteur_conteneur - Obj_Solution[i]->y), 
		      "%s", Obj_Solution[i]->nom);
      }
    }
}

/** Appel�e a chaque �venement sur win1 */
void win1_event (Ez_event *ev) {
  switch (ev->type) {
		 
  case Expose :	/* Il faut tout redessiner */
		
    win1_redessiner (ev->win);
    break;
            
  case KeyPress :	 /* Une touche a ete press�e */
    switch (ev->key_sym) {
    case XK_q : ez_quit (); 
      break;
    }
    break;
  }
}

/**
   Lire les solutions, les stocker.
*/
void LireSolutions ()
{
  int i;

  if(scanf("%d %d", &largeur_conteneur, &hauteur_conteneur) != 2) {
    fprintf(stderr, "LireSolutions : erreur lors de la lecture des "
	    "objets mis dans le conteneur : dimensions du conteneur "
	    "incorrectes. Abandon.\n");
    exit(EXIT_FAILURE);
  }
	
  if(scanf("%d", &nb_obj) != 1) {			
    fprintf(stderr, "LireSolutions : erreur lors de la lecture des "
	    "objets mis dans le conteneur : nombre d'objets incorrect."
	    "Abandon.\n");
    exit(EXIT_FAILURE);
  }

  Obj_Solution = AllouerEnsembleSolutions();
	
  for(i = 0; i < nb_obj; i++) {
    if(scanf("%s %d %d %d %d", Obj_Solution[i]->nom, 
	     &Obj_Solution[i]->l, 
	     &Obj_Solution[i]->h,
	     &Obj_Solution[i]->x, 
	     &Obj_Solution[i]->y) != 5) {
      fprintf(stderr, "LireSolutions : "
	      "erreur lors de la lecture des objets mis dans"
	      " le conteneur : idendite d'objet incorrecte. Abandon.\n");
      exit(EXIT_FAILURE);
    }
  }
  if(scanf("%lf %lf", &surface_max, &pourcentage) != 2) {
    fprintf(stderr, "LireSolutions : erreur lors de la lecture des "
	    "objets mis dans le conteneur : statistiques incorrectes. "
	    "Abandon.\n");
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
