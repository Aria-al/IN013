#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "./hdrFolder/algoEuclide.h"

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