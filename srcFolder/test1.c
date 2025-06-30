#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "./hdrFolder/plyCaract.h"
#include "./hdrFolder/fctSuite.h"
/*
Si le fichier est nommé test, plante car supprimé par avira et pas décontaminé



*/
int main (int argc, char const *argv[])
{
    /*
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
    

    FILE *f = fopen("mat1.txt", "r") ; 
    mat *m1 = lireMatrice(f) ; 
    fclose(f) ; 
    f = fopen("mat2.txt", "r") ; 
    mat *m2 = lireMatrice(f) ; 
    afficheMat(m1) ; 
    afficheMat(m2) ; 
    mat *m1Inv = eliminationGaussJordan(m1) ; 
    afficheMat(m1Inv) ; 
    mat *res = produitMatrice(m1Inv, m2); 
    afficheMat(res) ; 
    */
    
    FILE *f = fopen("ply1.txt", "r") ; 
    Poly *p1 = lirePoly(f) ; 
    fclose(f) ; 
    f = fopen("ply2.txt", "r") ; 
    Poly *p2 = lirePoly(f) ; 
    //Poly *p2 = copierPoly(p1, p1->d) ; 
    
    printf("Fin de lecture des fichiers\n") ; 
    affichePoly(p1) ; 
    affichePoly(p2) ; 
    Poly **res = malloc(sizeof(Poly*) * 3) ; 
    algoEuclideEtenduPoly(p2, p1, &res, 31) ; 
    printf("HI\n") ; 
    affichePoly(res[0]) ; 
    //affichePoly(res[1]) ; 
    affichePoly(res[2]) ; 
    /*
    Poly *Q, *R ; 
    Q = NULL ; R = NULL ; 
    divisionEucliPoly(p1, p2, &Q, &R, 8053) ;
    printf("FinEUcli\n") ; 
    affichePoly(Q) ; 
    affichePoly(R) ; 
    
    */
    return 0 ; 
}
