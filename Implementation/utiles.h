/** INF24 PROJET PACKING
 *   DIALLO-SOUIKI, 2011/2012
 */

#ifndef _UTILES_
#define _UTILES_

/** Afficher l'usage du programme en cas de demande ou d'erreur de synatxe */

void AfficherUsage    ();

/** Analyser la ligne de commande qui exécute le solveur */

int  AnalyserCommande (int argc, char *argv[]);

/** Allouer tous les tableaux globeaux utilisés par le solveur */

int* AllouerTableaux  ();

/** Afficher la trace de la procédure */

void AfficherTrace   (int profondeur, int k, int numero_bande, int e, int ligne, 
										  const char nom_fonction[]);

#endif  /** _UTILES_ */
