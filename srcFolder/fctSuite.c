#include "./hdrFolder/fctSuite.h"

int *calculeTermesSuite (RelRec *rel, int nbVal, int p) 
{
    if (!rel)
    {
        return NULL ; 
    }

    int *res = malloc(sizeof(int) * (nbVal + rel->nbValBase)) ; 
    
    // Valeurs de la base 
    for (int i = 0 ; i < rel->nbValBase ; i++)
    {
        // res[i] = (rel->termeBase)[i] ; 
        res[i] = (rel->termeBase)[i] % p ; 
    }

    // Valeurs de la relation de réccurence 
    for (int i = rel->nbValBase ; i < nbVal + rel->nbValBase ; i++)
    {
        res[i] = 0 ; 
        int k = 0 ; 
        for (int j = i - rel->nbValBase ; j < i ; j++)
        {
            // res[i] += res[j] * (rel->coefs)[k] ;
            res[i] = addiGrpQuot(res[i], multGrpQuot(res[j], (rel->coefs)[k], p), p) ; 
            k += 1 ; 
        }
    }
    return res ; 
}

void ecritRelRec (FILE *f, RelRec *rel)
{
    fprintf(f, "r=%d\n", rel->nbValBase) ; 
    for (int i = 0 ; i < rel->nbValBase ; i++)
    {
        fprintf(f, "%d,%d\n", rel->termeBase[i], rel->coefs[i]) ; 
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

    if (sscanf(buff, "r=%d\n", &r) != 1) 
    {
        printf("Mauvais format de fichier pour lireRelRec\n") ; 
        return NULL ; 
    }

    RelRec *res = malloc(sizeof(RelRec)) ; 
    res->nbValBase = r ; 
    res->coefs = malloc(sizeof(int) * r) ; 
    res->termeBase = malloc(sizeof(int) * r) ; 
    int u, a ; 
    for (int i = 0 ; i < r ; i++)
    {
        fgets(buff, MAXBUFF, f) ; 
        if (sscanf(buff, "%d,%d\n", &u, &a) != 2)
        {
            return NULL ; 
        }
        res->termeBase[i] = u ; 
        res->coefs[i] = a ; 
    }

    return res ; 

}

void afficheRelRec (RelRec *r)
{
    printf("r : %d\n", r->nbValBase) ; 
    for (int i = 0 ; i < r->nbValBase ; i++)
    {
        printf("u_(%d) = %d ; ", i, (r->termeBase)[i]) ; 
        if (!(i + 1%10))
        {
            printf("\n") ; 
        }
    }
    printf("\n\n") ; 

    for (int i = 0 ; i < r->nbValBase ; i++)
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
    fprintf(f, "nbTermes=%d\n", nbTermes) ; 
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

    if (sscanf(buff, "nbTermes=%d\n", nbTermes) != 1) 
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

void libereRelRec (RelRec *r) 
{
    free(r->coefs) ; 
    free(r->termeBase) ; 
    free(r) ; 
}


int relationCorrecte (int *termeCalc, int *termeSuite, int tailleTab, int *nbEchec) 
{
    int res = 0 ; 
    for (int i = 0 ; i < tailleTab ; i++)
    {
        if (termeCalc[i] != termeSuite[i])
        {
            res += 1 ; 
        }
    }
    *nbEchec = res ; 
    if (res == 0)
    {
        return 1 ; 
    }
    return 0 ; 
}

/*

Donne la matrice suivante : 
u0 u1 ... ur-1
u1 u2 ... ur
        ...
ur-1 ur+1 .... u2r-2
*/
mat *donneMatriceCarreSuite(int nbTermes, int *tab, int r, int p)
{
    mat *res = creeMatrice(r, r, p) ; 
    for (int i = 0 ; i < r ; i++)
    {
        for (int j = 0 ; j < r ; j++)
        {
            (res->mat)[i][j] = tab[i + j] ; 
        }
    }
    return res ; 
}

RelRec *determineRelationV1 (int nbTermes, int *tab, int p) 
{
    RelRec *res = malloc(sizeof(RelRec)) ; 
    mat *matDroite = malloc(sizeof(mat)) ; 
    matDroite->m = 1 ; 
    matDroite->n = 1 ; 
    matDroite->p = p ; 
    matDroite->mat = malloc(sizeof(int*) * matDroite->n) ;     
    // En employant M*
    for (int r = 1 ; 2*r < nbTermes + 1 ; r++)
    {
        mat *matGauche = donneMatriceCarreSuite(nbTermes, tab, r, p) ; 
        // On initialise le vecteur de gauche 
        matDroite->n = r ; 
        matDroite->mat = malloc(sizeof(int*) * matDroite->n) ; 

        for (int i = 0 ; i < r ; i++)
        {
            matDroite->mat[i] = malloc(sizeof(int)) ; 
            matDroite->mat[i][0] = tab[r + i] ; 
        }

        mat *invMatGauche = eliminationGaussJordan(matGauche) ; 
        if (invMatGauche != NULL)
        {
            /*
            */
            printf("\n") ; 
            afficheMat(invMatGauche) ; 
            printf("\n") ; 
            afficheMat(matDroite) ; 
            mat *vctRes = produitMatrice(invMatGauche, matDroite) ; 
            printf("FinProd\n") ; 
            //printf("%d\n", vctRes) ; 
            res->coefs = malloc(sizeof(int) * r) ; 
            printf("HI") ; 
            for (int i = 0 ; i < r ; i++)
            {
                res->coefs[i] = vctRes->mat[i][0] ; 
            }
            printf("HI") ; 
            res->nbValBase = r ; 
            res->termeBase = copieTableau(tab, r) ; 
            int *temp = calculeTermesSuite(res, nbTermes, p) ; 
            int *valCalc = malloc(sizeof(int) * nbTermes) ; 
            for (int u = 0 ; u < nbTermes ; u++)
            {
                valCalc[u] = temp[u] % p ; 
            }
            int nbEchecs = 0 ; 
            //
            if (relationCorrecte(valCalc, tab, nbTermes, &nbEchecs))
            {
                printf("Relation correcte pour r=%d\n", r) ; 
                free(valCalc) ; 
                libereMatrice(matGauche) ; 
                libereMatrice(vctRes) ; 
                libereMatrice(invMatGauche) ; 
                libereMatrice(matDroite) ; 
                return res ; 
            }
            else 
            {
                printf("Pour r=%d, # valeur incorrectes : %d\n", r, nbEchecs) ; 
                afficheTableau(valCalc, nbTermes) ; 
                printf("\n") ; 
                afficheTableau(tab, nbTermes) ; 
            }
        }

        else 
        {
            printf("Pour r=%d, matrice non inversible\n", r) ; 
        }
    }

    libereMatrice(matDroite) ; 
    return NULL ; 
}


RelRec *determineRelationV2 (int nbTermes, int *tab, int p) 
{

}