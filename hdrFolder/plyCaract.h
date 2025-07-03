#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "./hdrFolder/algoEuclide.h"
#include "./hdrFolder/libFunct.h"

// Représente un polynôme, sachant que le premier terme est toujours non nul 
// ATTENTION, d = degrée, et non pas la taille du tableau des coefficients, la taille est 
// égale à d + 1
typedef struct polynome 
{
    int d ; 
    int *coefs ; 
} Poly ; 

// Un polynôme nul (P = 0) est représenté par le pointeur NULL 


/*
Un polynôme est écrit de cette manière dans un fichier : 
d=%d
a0,a1,a2,...,ad-1,ad
Qui est équivalent à : 
a0 + a1 * x + a2 * x^2 + ... + ad * x^d
*/

// Lit un polynôme dans le fichier passé en paramètre 
Poly *lirePoly (FILE *f) ; 
void ecritPoly (FILE *f, Poly *p) ; 

// Calcule P1 + P2 
Poly *sommePoly (Poly *P1, Poly *P2, int premier) ; 
// Effectue la division euclidienne de P1 par P2, avec Q le quotient et R le reste
// On suppose que deg(P1) >= deg(P2)
void divisionEucliPoly (Poly *P1, Poly *P2, Poly **Q, Poly **R, int premier)  ; 
// Copie le polynôme passé en paramètre dans un nouveau polynôme de degré d 
Poly *copierPoly (Poly *P, int d) ; 
// Affiche le polynôme 
void affichePoly (Poly *p) ; 
// Version alternative qui utilise ecritPoly et le fait que sdtout peut être considéré comme un flus 
void affichePolyAlt(Poly *p) ; 

// Raccourcit le polynôme 
Poly *raccourcitPoly (Poly *P) ; 
// Renvoie le degré maximal entre les deux polynômes passés en paramètre
int degreMax (Poly *P1, Poly *P2) ; 

Poly *multPoly (Poly *P1, Poly *P2, int premier) ; 
Poly *initPoly (int d) ; 

// Calcule -P dans Z/premierZ
Poly *opposePoly (Poly *P, int premier) ; 

void algoEuclideEtenduPoly (Poly *P1, Poly *P2, Poly ***res, int p) ; 

Poly *algoBerlekampMassey (int *termes, int n, int premier) ; 

void liberePoly (Poly *P) ; 