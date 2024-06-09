#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "SuiteDetermine.h"

void calculeTermesSuite (RelRec *r, int **res, int nbVal) 
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
        int n, m ; 

    if (fgets(buff, MAXBUFF, f) == NULL) 
    {
        printf("Erreur de lecture du fichier\n") ; 
        return 0 ; 
    }

    if (sscanf(buff, "n : %d, m : %d\n", &n, &m) != 2) 
    {
        printf("Erreur de lecture de fichier 2 \n") ; 
        return 0 ; 
    }

}
