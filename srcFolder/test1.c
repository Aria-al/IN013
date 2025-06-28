#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "./hdrFolder/fctMatrices.h"
#include "./hdrFolder/plyCaract.h"
/*
Si le fichier est nommé test, plante car supprimé par avira et pas décontaminé



*/
int main (int argc, char const *argv[])
{
    FILE *f = fopen("ex4.txt", "r") ; 
    Poly *p1 = lirePoly(f) ; 
    fclose(f) ; 
    f = fopen("ex5.txt", "r") ; 
    Poly *p2 = lirePoly(f) ; 
    //Poly *p2 = copierPoly(p1, p1->d) ; 
    
    printf("Fin de lecture des fichiers\n") ; 
    affichePoly(p1) ; 
    affichePoly(p2) ; 
    Poly *res = multPoly(p1, p2, 31) ; 
    printf("\n  %d\n", multGrpQuot(2, 2, 31)) ; 
    affichePoly(res) ; 
    Poly *Q = NULL ; 
    Poly *R = NULL ; 
    divisionEucliPoly(p2, p1, &Q, &R, 31) ; 
    affichePoly(Q) ; 
    affichePoly(R) ; 
    liberePoly(res) ; 
    liberePoly(p1) ; 
    liberePoly(p2) ; 
    liberePoly(Q) ; 
    liberePoly(R) ; 
    fclose(f) ; 
    /*
    
    */
    return 0 ; 
}
