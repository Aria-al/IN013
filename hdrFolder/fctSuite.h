#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "./hdrFolder/algoEuclide.h"
#include "./hdrFolder/fctMatrices.h"
#include "./hdrFolder/libFunct.h"
#include "./hdrFolder/plyCaract.h"

/*
Définit une relation de réccurence d'ordre nbValBase, avec les coefficients de la réccurence
ainsi que les premiers termes de la base 
*/
typedef struct relationDeRecurrence 
{
    int nbValBase ; 
    int *coefs ; 
    int *termeBase ; 
} RelRec ; 
/*
Une relation de réccurence est écrite de cette manière : 
r=%d
u0,a0
...
ur-1,ar-1
Les u étant les termes de la base, et les a étant les coefficients 
*/

// Retourne les nbVal + nbValBase premières valeurs de la suite, en plus des 
int *calculeTermesSuite (RelRec *r, int nbVal, int p) ; 
// Ecrit la relation de réccurence dans un fichier 
void ecritRelRec (FILE *f, RelRec *r) ; 
// Lit une relation de récurence dans un fichier 
RelRec *lireRelRec (FILE *f) ; 
// Affiche la relation de récurrence 
void afficheRelRec (RelRec *r) ; 

// Ecrit les nbTermes d'une suite dans un fichier 
void ecrireTermeSuite (FILE *f, int nbTermes, int *t) ; 
// Lit les nbTermes d'une suite dans un fichier 
void lireTermeSuite (FILE *f, int *nbTermes, int **t) ; 
// Affiche les nbTermes d'une suite 
void afficheTermeSuite (int nbTermes, int *t) ; 
// Libère le mémoire allouée à une RelRec 
void libereRelRec (RelRec *r) ; 

// Renvoie si la relation de réccurence est correcte, sinon renvoie 0 
// tandis que nbEchec renvoie le nombre d'échecs 
int relationCorrecte (int *termeCalc, int *termeSuite, int tailleTab, int *nbEchec) ;

// Dans les algorithmes suivants, on suppose que 

// Version 1 de l'algorithme, par inversion directe de matrice 
RelRec *determineRelationV1 (int nbTermes, int *tab, int p) ; 

RelRec *determineRelationV2 (int nbTermes, int *tab, int p) ; 

RelRec *determineRelationV3 (int nbTermes, int *tab, int p) ; 