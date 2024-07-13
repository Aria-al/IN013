#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "PolynomeCaract.h"

void affichePoly (Poly *p) 
{
    for (int i = 0 ; i < p->d + 1; i++)
    {
        printf("%d*X^%d ", (p->coefs)[i], p->d - i) ; 
    }
    printf("\n") ; 
}


Poly *copierPoly (Poly *P, int d) 
{
    Poly *res = malloc(sizeof(Poly)) ; 
    res->d = d ; 
    res->coefs = malloc(sizeof(int) * (d + 1)) ; 

    int k = 0 ; 

    if (d > P->d)
    {
        k = d - P->d ; 
        printf("valeur de k : %d\n", k) ; 
        for (int i = 0 ; i < k ; i++)
        {
            printf("BAV\n") ; 
            (res->coefs)[i] = 0 ; 
        }

        for (int i = 0 ; i < P->d + 1 ; i++)
        {
            printf("BAA\n") ; 
            (res->coefs)[i + k] = (P->coefs)[i] ; 
        }
    }
    else 
    {
        k = P->d - d ; 
        for (int i = 0 ; i < d + 1 ; i++)
        {
            (res->coefs)[i] = (P->coefs)[i + k] ; 
        }
    }

    return res ; 
}


int degreMax (Poly *P1, Poly *P2)
{
    int dMax ; 

    if (P1->d > P2->d)
    {
        dMax = P1->d ; 
    }

    else 
    {
        dMax = P2->d ; 
    }
    return dMax ; 
}

Poly *sommePoly (Poly *P1, Poly *P2, char s, int premier) 
{
    int dMax = degreMax(P1, P2) ; 

    int c = 1 ; 
    if (s == 's')
    {
        c = -1 ; 
    }

    Poly *T1, *T2 ; 
    T1 = copierPoly(P1, dMax) ; 
    T2 = copierPoly(P2, dMax) ;  

    Poly *temp = malloc(sizeof(Poly)) ;
    temp->d = dMax ; 
    temp->coefs = malloc(sizeof(int) * (temp->d + 1)) ; 

    for (int i = 0 ; i < dMax + 1; i++)
    {
        (temp->coefs)[i] = (T1->coefs)[i] + c * (T2->coefs)[i] ; 
        //(temp->coefs)[i] = sommeGroupe((T1->coefs)[i], produitGroupe(c, (T2->coefs)[i], premier), premier) ; 
    }

    Poly *res = raccourcitPoly(temp) ; 
    
    free(temp->coefs) ; 
    free(temp) ; 
    free(T1->coefs) ; 
    free(T2->coefs) ; 
    free(T1) ; 
    free(T2) ; 

    return res ; 
}


Poly *raccourcitPoly (Poly *P)
{
    int q = P->d ; 
    for (int i = 0 ; i < P->d + 1 ; i++)
    {
        if ((P->coefs)[i] % 7)
        {
            break ; 
        }
        q -= 1 ; 
    }
    return copierPoly(P, q) ; 
}


Poly *produitPoly (Poly *P1, Poly *P2, int premier)
{
    Poly *res = malloc(sizeof(Poly)) ; 
    res->d = P1->d + P2->d ; 
    res->coefs = malloc(sizeof(int) * (res->d + 1)) ; 

    for (int i = 0 ; i < res->d + 1 ; i++)
    {
        (res->coefs)[i] = 0 ; 
    }

    for (int i = 0 ; i < P1->d + 1 ; i++) 
    {
        for (int j = 0 ; j < P2->d ; j++)
        {
            (res->coefs)[i + j] += (P1->coefs)[i] * (P2->coefs)[j] ; 
            //(res->coefs)[i + j] += produitGroupe((P1->coefs)[i], (P2->coefs)[j], premier) ; 
        }
    }

    for (int i = 0 ; i < P1->d + 1 ; i++)
    {
        (res->coefs)[i + P2->d] += (P1->coefs)[i] * (P2->coefs)[P2->d] ; 
    }

    return res ; 
}

void divisionEucliPoly (Poly *P1, Poly *P2, Poly **Q, Poly **R, int premier) 
{
    // On définit le quotient comme étant nul 
    (*Q) = malloc(sizeof(Poly)) ; 
    (*Q)->d = 0 ; 
    (*Q)->coefs = malloc(sizeof(int)) ; 
    (*Q)->coefs[0] = 0 ; 

    // On alloue les deux termes de la division dans des variables locales 
    Poly *dividende = raccourcitPoly(P1) ; 
    Poly *diviseur = raccourcitPoly(P2) ; 

    // Polynôme constitant d'un seul mônome de degré maximal 
    Poly monome ; 
    Poly *aSoustraire ; 
    Poly *tempDividende ; 
    Poly *tempQ ; 

    int iter = 0 ; 
    while (dividende->d >= diviseur->d && iter < 5)
    {
        monome.d = dividende->d - diviseur->d ; 
        monome.coefs = malloc(sizeof(int) * (monome.d + 1)) ; 
        // On devrait remplacer (dividende->coefs)[0] par une fonction donnant x tel que x * cd(diviseur) = cd(dividende)
        monome.coefs[0] = produitGroupe((dividende->coefs)[0], inverseGroupeQuotient(diviseur->coefs[0], premier), premier) ; 

        for (int i = 1 ; i < monome.d + 1 ; i++)
        {
            (monome.coefs)[i] = 0 ; 
        }
        printf("valeur : %d, et soustraction vaut %d \nmonome : ", monome.coefs[0], sommeGroupe(monome.coefs[0], dividende->coefs[0], premier)) ; 
        affichePoly(&monome) ;

        aSoustraire = produitPoly(diviseur, &monome, premier) ; 
        tempDividende = sommePoly(dividende, aSoustraire, 's', premier) ; 

        // On met à jour le dividende 
        free(dividende->coefs) ; 
        free(dividende) ; 
        dividende = tempDividende ; 

        // On ajoute monome au quotient 
        tempQ = sommePoly(*Q, &monome, 'a', premier) ; 
        free((*Q)->coefs) ; 
        free((*Q)) ; 
        (*Q) = tempQ ; 

        printf("dividende : ") ; affichePoly(dividende) ; 
        printf("Q : ") ; affichePoly((*Q)) ; 
        free(monome.coefs) ; 
        free(aSoustraire->coefs) ; 
        free(aSoustraire) ; 

        printf("%d\n", iter) ; 
        iter += 1 ; 

    }

    printf("Fin de division polynomiale\n") ; 
    printf("R : ") ; 
    affichePoly(dividende) ; 
    *R = raccourcitPoly(dividende) ; 

    free(dividende->coefs) ; 
    free(diviseur->coefs) ; 
    free(dividende) ; 
    free(diviseur) ; 
}


Poly *alogEuclideEtenduPoly (Poly *P1, Poly *P2)
{

}

Poly *algoBerlekampMassey (int *termes, int n, int premier)
{
    Poly *R, *R0, *R1, *V, *V0, *V1, *Q ; 
    // Initialisation des variables 
    R0 = malloc(sizeof(Poly)) ; 
    R0->d = 2*n ; 
    R0->coefs = malloc(sizeof(int) * (R0->d + 1)) ;
    R0->coefs[0] = 1 ; 
    for (int i = 1 ; i < R0->d + 1 ; i++)
    {
        (R0->coefs)[i] = 0 ; 
    }

    R1 = malloc(sizeof(Poly)) ; 
    R1->d = 2*n - 1 ; 
    R1->coefs = malloc(sizeof(int) * (R1->d + 1)) ; 
    for (int i = 0 ; i < R1->d + 1 ; i++)
    {
        R1->coefs[i] = termes[((2*n) - 1) - i] ; 
    }

    V0 = malloc(sizeof(Poly)) ; 
    V0->d = 2*n ; 
    V0->coefs = malloc(sizeof(int) * (V0->d + 1)) ;
    for (int i = 0 ; i < V0->d + 1 ; i++)
    {
        (V0->coefs)[i] = 0 ; 
    }

    V1 = malloc(sizeof(Poly)) ; 
    V1->d = 2*n ; 
    V1->coefs = malloc(sizeof(int) * (V1->d + 1)) ;
    for (int i = 0 ; i < V1->d ; i++)
    {
        (V1->coefs)[i] = 0 ; 
    }
    V1->coefs[V1->d] = 1 ; 
    
    printf("R0 : ") ; 
    affichePoly	(R0) ; 

    printf("R1 : ") ; 
    affichePoly	(R1) ; 
    
    printf("V0 : ") ; 
    affichePoly	(V0) ; 
    
    printf("V1 : ") ; 
    affichePoly	(V1) ; 
    printf("\n") ; 

    Poly *temp1 ; 
    Poly *temp2 ; 
    int iter = 0 ; 
    while (n <= R1->d && iter < 20)
    {
        divisionEucliPoly(R0, R1, &Q, &R, premier) ; 
        temp1 = produitPoly(Q, V1, premier) ; 
        temp2 = sommePoly(V0, temp1, 's', premier) ; 
        /*
        free(temp1->coefs) ; 
        free(temp1) ; 
        */

        /*
        free(V0->coefs) ; 
        free(V0) ; 
        */
        V0 = V1 ; 

        /*
        free(V1->coefs) ; 
        free(V1) ; 
        */
        V1 = temp2 ;  

        /*
        free(R0->coefs) ; 
        free(R0) ; 
        */
        R0 = R1 ; 

        /*
        
        free(R1->coefs) ; 
        free(R1) ; 
        */
        R1 = R ;
        /*
        free(temp2->coefs) ; 
        free(temp2) ; 
        */

        iter += 1 ; 
    }

    int d = 1 + R1->d ; 
    if (V1->d > 1 + R1->d)
    {
        d = V1->d ; 
    }

    Poly *monome = malloc(sizeof(Poly)) ;
    monome->d = d - 1 ; 
    monome->coefs = malloc(sizeof(int) * (monome->d + 1)) ; 
    monome->coefs[0] = 1 ; 
    for (int i = 1 ; i < monome->d + 1 ; i++)
    {
        monome->coefs[i] = 0 ; 
    }


    Poly *P = produitPoly(monome, V1, premier) ; 
    affichePoly(P) ; 
    
    for (int i = 0 ; i < P->d ; i++)
    {
        (P->coefs)[i] = ((P->coefs)[i] * inverseGroupeQuotient(P->coefs[0], premier)) % premier; 
    }

    free(monome->coefs) ; 
    free(monome) ; 

    return P ;
}