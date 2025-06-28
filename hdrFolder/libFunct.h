#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int min (int a, int b) ; 
int max (int a, int b) ; 
// Etend le tableau passe en parametre en taille 2*len
// Initialise les nouvelles valeurs à 0 
int *etendTableau (int *tab, int len) ; 
// Copie le tableau passé en paramètre 
int *copieTableau (int *tab, int len) ; 
// affiche le tableau en paramètre 
void afficheTableau (int *tab, int len) ; 
// Applique la fonction func sur tab
int *map (int *tab, int len, int (*func) (int)) ; 