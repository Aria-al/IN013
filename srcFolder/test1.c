#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "./hdrFolder/fctSuite.h"

/*
Si le fichier est nommé test, plante car supprimé par avira et pas décontaminé
*/

int main (int argc, char const *argv[])
{
    FILE *f = fopen("ex1.txt", "r") ; 
    mat *u = lireMatrice(f) ;
    printf("==============================\n") ; 
    afficheMat(u) ; 
    printf("==============================\n") ; 
    int t = rangMatrice(u) ; 
    return 0 ; 
}
