#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "EuclideAlgos.h"
#include "InversionMatrice.h"

typedef struct relationDeRecurrence 
{
    int r ; 
    int *coefs ; 
    int *termeBase ; 
} RelRec ; 



// Retourne les termes de la base, avec nbVal valeurs de la suite récurrente linéaire 
void calculeTermesSuite (RelRec *r, int nbVal, int **res) ; 
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

// Renvoie si la relation de réccurence est correcte, 
int relationCorrecte (int *termeCalc, int *termeSuite, int tailleTab, int *rEchec) ;
