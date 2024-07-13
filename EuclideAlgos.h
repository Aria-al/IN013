#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAXBUFF 32768

// Fonctions sur le groupe Z/pZ

void divisionEucli (int a, int b, int res[4]) ; 
void alogEuclideEtendu (int a, int b, int res[3]) ; 
int inverseGroupeQuotient (int a, int p) ; 
int sommeGroupe (int a, int b, int p) ; 
int produitGroupe (int a, int b, int p) ; 