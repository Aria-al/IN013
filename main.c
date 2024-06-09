#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "EuclideAlgos.h"
#include "InversionMatrice.h"
#include "SystemChinois.h"



int main(int argc, char const *argv[])
{
    /*
    int d = -1 ; 
    int a, b ; 
    while (d != 0)
    {
        printf("Entrer la decision :\n0.Sortie de programme\n1.Algo Etendu d'euclide\n2.Division euclidienne\n3.Inverse groupe quotient\n") ; 
        scanf("%d", &d) ; 
        switch (d)
        {
        case 1 :
            int tab1[3] = {0, 0, 0} ; 
            printf("Valeurs de a et b, a>b\n") ; 
            scanf("%d %d", &a, &b) ; 
            alogEuclideEtendu(a, b, tab1) ;     
            printf("%d = %d * %d + %d * %d\n", tab1[0], a, tab1[1], b, tab1[2]) ; 
            break;
        
        case 2 : 
            int tab2[4] = {0, 0, 0, 0} ; 
            printf("Valeurs de a et b, a > b\n") ; 
            scanf("%d %d", &a, &b) ; 
            divisionEucli(a, b, tab2) ;
            printf("%d = %d * %d + %d\n", tab2[0], tab2[1], tab2[2], tab2[3]) ; 
            break;
        
        case 3 :
            printf("Valeurs de a et p, Z/pZ\n") ; 
            scanf("%d %d", &a, &b) ; 
            while (a < b)
            {
                a += b ; 
            }
            printf("a=%d, p=%d\n", a, b) ; 
            int q = inverseGroupeQuotient(a, b) ; 
            printf("%d\n", q) ; 
            break;

        default:
            break;
        }
        a = 0 ; 
        b = 0 ; 
    }
    */

    
    FILE *f = fopen("ex1.txt", "r") ; 
    mat *res = lireMatrice(f) ; 
    int prem = 97 ; 
    mat * res1 = eliminationGaussJordan(res, prem) ;
    
    printf("Dans Z/%dZ : \n", prem) ; 

    printf("Matrice de base : \n") ; 
    afficheMat(res) ; 
    
    printf("Matrice inverse : \n") ; 
    afficheMat(res1) ; 

    mat *p = produitMatrice(res, res1) ; 
    printf("Produit des deux matrices : \n") ;
    afficheMat(p) ; 

    fclose(f) ; 

    f = fopen("ex2.txt", "r") ; 
    sytChi *s = lireSytChi(f) ; 
    fclose(f) ; 
    
    resoudreSytChiRec(s) ; 
    affSytChi(s) ; 
    fclose(f) ; 
    
    return 0;
}
