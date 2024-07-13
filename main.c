#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "EuclideAlgos.h"
#include "SystemChinois.h"
#include "SuiteDetermine.h"
#include "PolynomeCaract.h"


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

    for (int i = 0 ; i < p->n ; i++)
    {
        for (int j = 0 ; j < p->m ; j++)
        {
            (p->mat)[i][j] = (p->mat)[i][j] % prem ; 
        }
    }
    afficheMat(p) ; 

    fclose(f) ; 
    */

    /*

    f = fopen("ex2.txt", "r") ; 
    sytChi *s = lireSytChi(f) ; 
    fclose(f) ; 
    
    resoudreSytChiRec(s) ; 
    affSytChi(s) ; 
    
    fclose(f) ; 
    f = fopen("ex3.txt", "r") ; 
    RelRec *u = lireRelRec(f) ; 
    afficheRelRec(u) ; 
    fclose(f) ; 
    int *toPrint ; 
    calculeTermesSuite(u, 30, &toPrint) ; 
    f = fopen("TEST.txt", "w") ; 
    ecrireTermeSuite(f, 30, toPrint) ; 



    Poly *test = sommePoly(produitPoly(&diviseur, Q, 7), R, 'a', 7) ; 
    affichePoly(test) ; 
    affichePoly(&dividende) ; 
    */


    Poly dividende ; 
    dividende.d = 3 ; 
    dividende.coefs = malloc(sizeof(int) * (dividende.d + 1)) ; 
    dividende.coefs[0] = 2 ; 
    dividende.coefs[1] = -3 ; 
    dividende.coefs[2] = 2 ; 
    dividende.coefs[3] = 1 ;

    Poly *temp = copierPoly(&dividende, 2) ; 
    affichePoly(temp) ; 
    free(dividende.coefs) ; 
    free(temp->coefs) ; 
    free(temp) ; 
    /*
    Poly diviseur ; 
    diviseur.d = 1 ; 
    diviseur.coefs = malloc(sizeof(int) * (diviseur.d + 1)) ; 
    diviseur.coefs[0] = 1 ; 
    diviseur.coefs[1] = 5 ; 
    affichePoly(&dividende) ; 
    affichePoly(&diviseur) ; 
    Poly *Q, *R ; 
    divisionEucliPoly(&dividende, &diviseur, &Q, &R, 7) ; 
    printf("Q : ") ; 
    affichePoly(Q) ; 
    printf("R : ") ; 
    affichePoly(R) ; 
    free(Q->coefs) ; 
    free(Q) ; 
    free(R->coefs) ; 
    free(R) ; 
    free(diviseur.coefs) ; 
    */


    /*

    Poly mono ; 
    mono.d = 2 ; 
    mono.coefs = malloc(sizeof(int) * (mono.d + 1)) ; 
    mono.coefs[0] =  produitGroupe(dividende.coefs[0], inverseGroupeQuotient(diviseur.coefs[0], 7), 7); 
    for (int i = 1 ; i < mono.d + 1 ; i++)
    {
        mono.coefs[i] = 0 ; 
    }
    affichePoly(&mono) ; 

    Poly *sous = produitPoly(&mono, &diviseur, 7) ; 
    printf("sous : ") ; 
    affichePoly(sous) ; 

    Poly *sres = sommePoly(&dividende, sous, 's', 7) ; 
    printf("sres : ") ; 
    affichePoly(sres) ; 
    printf("question : %d", (5 - (5 *  3 * inverseGroupeQuotient(3, 7))) % 7) ; 
    */
    int maoqsnqjsqn ; 

    /*
    
    */
    // Soit la suite u_n = 2 * u_(n-1), u_0 = 1 
    int tab[10] ; 
    tab[0] = 1 ; 
    for (int i = 1 ; i < 10 ; i++)
    {
        tab[i] = 2 * tab[i - 1] ; 
    }

    Poly *res = algoBerlekampMassey (tab, 5, 11) ; 
    affichePoly(res) ; 

    printf("9-1 = %d mod 7", inverseGroupeQuotient(9, 7)) ; 
    return 0 ; 
}
