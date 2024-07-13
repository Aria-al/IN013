#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "SuiteDetermine.h"

void calculeTermesSuite (RelRec *r, int nbVal, int **res) 
{
    if (!r)
    {
        return ; 
    }
    (*res) = malloc(sizeof(int) * (nbVal + r->r)) ; 
    int *valeurs = (*res) ; 
    
    // Valeurs de la base 
    for (int i = 0 ; i < r->r ; i++)
    {
        valeurs[i] = (r->termeBase)[i] ; 
    }

    // Valeurs de la relation de réccurence 
    for (int i = r->r ; i < nbVal + r->r ; i++)
    {
        valeurs[i] = 0 ; 
        int k = 0 ; 
        for (int j = i - r->r ; j < i ; j++)
        {
            valeurs[i] += valeurs[j] * r->coefs[k] ; 
            k += 1 ; 
        }
    }
}

void ecritRelRec (FILE *f, RelRec *r)
{
    fprintf(f, "r : %d\n", r->r) ; 
    for (int i = 0 ; i < r->r ; i++)
    {
        fprintf(f, "%d, %d\n", r->termeBase[i], r->coefs[i]) ; 
    }
}

RelRec *lireRelRec (FILE *f) 
{
    char buff[MAXBUFF] ; 
    int r ; 

    if (fgets(buff, MAXBUFF, f) == NULL) 
    {
        printf("Erreur de lecture pour lireRelRec\n") ; 
        return NULL ; 
    }

    if (sscanf(buff, "r : %d\n", &r) != 1) 
    {
        printf("Mauvais format de fichier pour lireRelRec\n") ; 
        return NULL ; 
    }

    RelRec *res = malloc(sizeof(RelRec)) ; 
    res->r = r ; 
    res->coefs = malloc(sizeof(int) * r) ; 
    res->termeBase = malloc(sizeof(int) * r) ; 
    int u, a ; 
    for (int i = 0 ; i < r ; i++)
    {
        fgets(buff, MAXBUFF, f) ; 
        if (sscanf(buff, "%d, %d\n", &u, &a) != 2)
        {
            return NULL ; 
        }
        res->coefs[i] = a ; 
        res->termeBase[i] = u ; 
    }

    return res ; 

}

void afficheRelRec (RelRec *r)
{
    printf("r : %d\n", r->r) ; 
    for (int i = 0 ; i < r->r ; i++)
    {
        printf("u_(%d) = %d ; ", i, (r->termeBase)[i]) ; 
        if (!(i + 1%10))
        {
            printf("\n") ; 
        }
    }
    printf("\n\n") ; 

    for (int i = 0 ; i < r->r ; i++)
    {
        printf("a_(%d) = %d ; ", i, (r->coefs)[i]) ; 
        if (!(i + 1%10))
        {
            printf("\n") ; 
        }
    }
    printf("\n") ; 
}


void ecrireTermeSuite (FILE *f, int nbTermes, int *t)
{
    fprintf(f, "nbTermes : %d\n", nbTermes) ; 
    for (int i = 0 ; i < nbTermes ; i++)
    {
        fprintf(f, "%d\n", t[i]) ;
    }
}


void lireTermeSuite (FILE *f, int *nbTermes, int **t)
{
    char buff[MAXBUFF] ; 
    
    if (fgets(buff, MAXBUFF, f) == NULL) 
    {
        printf("Erreur de lecture pour lireTermeSuite\n") ; 
        return ; 
    }

    if (sscanf(buff, "nbTermes : %d\n", nbTermes) != 1) 
    {
        printf("Mauvais format de fichier pour lireTermeSuite\n") ; 
        return ; 
    }

    (*t) = malloc((*nbTermes) * sizeof(int)) ; 
    int temp ; 

    for (int i = 0 ; i < (*nbTermes) ; i++)
    {
        fgets(buff, MAXBUFF, f) ; 
        if (sscanf(buff, "%d\n", &temp) != 1)
        {
            return ; 
        }
        (*t)[i] = temp ; 
    }
}


void afficheTermeSuite (int nbTermes, int *t)
{
    printf("nbTermes : %d\n", nbTermes) ; 
    for (int i = 0 ; i < nbTermes ; i++)
    {
        printf("u_(%d) = %d\n", i,t[i]) ; 
    }
}


int relationCorrecte (int *termeCalc, int *termeSuite, int tailleTab, int *rEchec) 
{
    for (int i = 0 ; i < tailleTab ; i++)
    {
        if (termeCalc[i] != termeSuite[i])
        {
            (*rEchec) = i ; 
            return 0 ; 
        }
    }
    return 1 ; 
}

RelRec *donneRelation(int *t, int nbTermes, int d)
{
    
}