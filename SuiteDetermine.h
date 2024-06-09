#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "EuclideAlgos.h"

typedef struct relationDeRecurrence {
    int r ; 
    int *coefs ; 
    int *termeBase ; 
} RelRec ; 

void calculeTermesSuite (RelRec *r, int **res, int nbVal) ; 
void ecritRelRec (FILE *f, RelRec *r) ; 
RelRec *lireRelRec (FILE *f) ; 


void ecrireTermeSuite (FILE *f, int nbTermes, int *t) ; 
void lireTermeSuite (FILE *f, int *nbTermes, int **t) ; 


int relationCorrecte (int *termeCalc, int *termeSuite, int tailleTab) ;
