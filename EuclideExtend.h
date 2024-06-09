#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAXBUFF 32768

// Fonctions sur le groupe Z/pZ

void divisionEucli (int a, int b, int res[4]) ; 
void alogEuclideEtendu (int a, int b, int res[3]) ; 
int inverseGroupeQuotient (int a, int p) ; 


// Une matrice de dimentions n x m

typedef struct matriceCarre
{
    int n, m ; 
    int **mat ; 
} mat ; 


// Fonctions de base sur les matrices n*m

void afficheMat (mat *m) ; 
void libereMatrice (mat *m) ; 
mat *creeMatrice (int n, int m) ; 
mat * matriceDiag (int i, int n) ; 
mat *tranposeMatrice (mat *m) ; 
mat *copieMatrice (mat *m) ; 


// Fonctions d'écriture-lecture de matrice 

void ecrireMatrice (FILE *f, mat *m) ; 
mat *lireMatrice (FILE *f) ; 


// Fonctions d'opération élémentaire entre 2 matrices sachant qu'elles possèdent les bonnes dimentions 

mat *sommeMatrice (mat *m1, mat *m2) ; 
mat *produitMatrice (mat *m1, mat *m2) ; 


// Calcul de déterminant

int detMatrice (mat *m) ; 
mat *matriceMineure (mat *m, int ligne, int colonne) ; 


// Algorithme de réduction de Gauss 

void permutationLigne (mat *m, int l1, int l2) ; 
void dilateLigne (mat *m, int coef, int ligne, int premier, char type) ; 
void transvectionLigne (mat *m, int l1, int coef, int l2, int premier, char type)  ; 
mat *eliminationGaussJordan (mat *m, int premier) ; 


// Un système d'équations de reste chinois 
/*
x = aCoef[0] [mMods[0]] ; 
x = aCoef[1] [mMods[1]] ;
x = aCoef[2] [mMods[2]] ; 
...
x = aCoef[nbEqa] [mMods[nbEqa]] ; 
*/
typedef struct systemeModulo 
{
    int nbEqua ; 
    int x ; 
    int *aCoef ; 
    int *mMods ; 
} sytChi ;

sytChi *creeEq (int nbEqua) ; 
sytChi *lireSytChi (FILE *f) ; 
void ecrireSytChi (FILE *f, sytChi *s) ; 
void affSytChi (sytChi *s) ; 
void resoudreSytChiDuo(sytChi *s) ; 
void libereSytChi (sytChi *s) ; 
void resoudreSytChiRec (sytChi *s) ; 