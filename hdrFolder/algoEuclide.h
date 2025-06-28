#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAXBUFF 32768

// Fonctions sur le groupe Z/pZ

void divEucli (int a, int b, int res[4]) ; 
void alogEucliEtendu (int a, int b, int res[3]) ; 
int invGrpQuot (int a, int p) ; 
int addiGrpQuot (int a, int b, int p) ; 
int multGrpQuot (int a, int b, int p) ; 