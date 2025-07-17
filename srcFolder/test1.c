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
    FILE *f = fopen("ex3.txt", "r") ; 
    RelRec *r = lireRelRec(f) ; 
    afficheRelRec(r) ; 
    int p = 301 ; 
    int N = 10 ; 
    int a = calcTermeSuite (r, p, N) ; 
    printf("Terme #%d : %d\n", N, a) ; 

    
    /*
    */
    return 0 ; 
}
