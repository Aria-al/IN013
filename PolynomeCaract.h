#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "EuclideAlgos.h"

// Représente un polynôme, sachant que le premier terme est toujours non nul 
// ATTENTION, d = degrée, et non pas la taille du tableau des coefficients, la taille est 
// égale à d + 1
typedef struct polynome 
{
    int d ; 
    int *coefs ; 
} Poly ; 

// Effectue une opération entre les deux polynomes, P1 - P2 si s = 's', P1 + P2 si s = 'a'
Poly *sommePoly (Poly *P1, Poly *P2, char s, int premier) ; 
// Effectue la division euclidienne de P1 par P2, avec Q le quotient et R le reste
// On suppose que le coefficient maximal  cd(P2) = 1 
void divisionEucliPoly (Poly *P1, Poly *P2, Poly **Q, Poly **R, int premier)  ; 
// Copie un polynôme passé en paramètre dans un nouveau polynôme de degré supérieur ou inférieur 
Poly *copierPoly (Poly *P, int d) ; 
// Affiche le polynôme 
void affichePoly (Poly *p) ; 
// Raccourcit le polynôme 
Poly *raccourcitPoly (Poly *P) ; 
// Renvoie le degré maximal entre les deux polynômes passés en paramètre
int degreMax (Poly *P1, Poly *P2) ; 

Poly *produitPoly (Poly *P1, Poly *P2, int premier) ; 

Poly *algoBerlekampMassey (int *termes, int n, int premier) ; 