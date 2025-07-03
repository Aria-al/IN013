#include "./hdrFolder/fctMatrices.h"

// Crée une matrice n x m 
mat *creeMatrice(int n, int m, int p)
{
    mat *res = malloc(sizeof(mat)) ; 
    res->n = n ; 
    res->m = m ; 
    res->p = p ; 
    res->mat = malloc(sizeof(int*) * m) ; 
    for (int i = 0 ; i < n ; i++)
    {
        (res->mat)[i] = malloc(sizeof(int) * m) ; 
        for (int j = 0 ; j < m ; j++)
        {
            res->mat[i][j] = 0 ; 
        }
    }
    return res ; 
}


// Fait la copie d'une matrice 
mat *copieMatrice (mat *m)
{
    mat *res = creeMatrice(m->n, m->m, m->p) ; 
    for (int i = 0 ; i < m->n ; i++)
    {
        for (int j = 0 ; j < m->m ; j++)
        {
            (res->mat)[i][j] = (m->mat)[i][j] ; 
        }
    }
    return res ; 
}


// Effectue la somme de deux matrices : m1 + m2 = res 
mat *sommeMatrice (mat *m1, mat *m2) 
{
    if ((m1->m != m2->m) || (m1->n != m2->n) || (m1->p != m2->p))
    {
        return NULL ; 
    }

    mat *res = creeMatrice(m1->n, m1->m, m1->p) ; 
    for (int i = 0 ; i < m1->n ; i++)
    {
        for (int j = 0 ; j < m1->m ; j++)
        {
            (res->mat)[i][j] = addiGrpQuot((m1->mat)[i][j], (m2->mat)[i][j], m1->p) ; 
        }
    }

    return res ; 
}


// Effectue le produit de deux matrices : m1 x m2 = res 
mat *produitMatrice(mat *m1, mat *m2)
{
    if ((m1->m != m2->n) || (m1->p != m2->p))
    {
        return NULL ; 
    }

    mat *res = creeMatrice(m1->n, m2->m, m2->p) ; 
    for (int i = 0 ; i < m1->n ; i++)
    {
        for (int j = 0 ; j < m2->m ; j++)
        {
            for (int t = 0 ; t < m1->m ; t++)
            {
                (res->mat)[i][j] = addiGrpQuot(multGrpQuot((m1->mat)[i][t], 
                                (m2->mat)[t][j], m1->p), (res->mat)[i][j], res->p ) ; 
            }
        }
    }

    return res ; 
}


// Libère la mémoire occupée par la matrice 
void libereMatrice (mat *m)
{
    for (int i = 0 ; i < m->m ; i++)
    {
        free((m->mat)[i]) ; 
    }
    free(m) ; 
}


// Renvoie une matrice diagonale de dimention n*n dont la diagonale est remplie de i 
mat * matriceDiag (int i, int n, int p)
{
    mat *res = creeMatrice(n, n, p) ; 
    for (int t = 0 ; t < n ; t++)
    {
        (res->mat)[t][t] = i ; 
    }
    return res ; 
}


// Affiche la matrice 
void afficheMat (mat *m)
{
    for (int i = 0 ; i < m->n ; i++)
    {
        for (int j = 0 ; j < m->m ; j++)
        {
            printf("%d ", (m->mat)[i][j]) ; 
        }
        printf("\n") ; 
    }
}


// Renvoie la matrice mineure A(ligne,colonne) qui correspond à la matrice m dont on a retiré une ligne et une colonne 
mat *matriceMineure (mat *m, int ligne, int colonne) 
{
    mat *res = creeMatrice(m->n - 1, m->m - 1, m->p) ; 
    int iTemp = 0 ; 
    for (int i = 0 ; i < m->n ; i++)
    {
        // On a la ligne qu'on cherche à éviter 
        if (i == ligne)
        {
            i += 1 ; 
            if (i >= m->n)
            {
                break ; 
            }
        }

        int jTemp = 0 ; 
        for (int j = 0 ; j < m->m ; j++)
        {   
            // On a la colonne qu'on cherche à éviter 
            if (j == colonne)
            {
                j += 1 ; 
                if (j >= m->m)
                {
                    break ;
                }
            }

            (res->mat)[iTemp][jTemp] = (m->mat)[i][j] ; 
            jTemp += 1 ; 
        }
        iTemp += 1 ; 
    }
    return res ; 
}


// Renvoie le déterminant de la matrice passé en paramètre 
int detMatrice (mat *m)
{
    if (m->m != m->n)
    {
        return 0 ; 
    }

    if (m->m == 1)
    {
        if ((m->mat[0][0] % m->p) != 0)
        {
            return 1 ; 
        }
    }

    // Si on a une matrice 2*2, dont on a la formule directe 
    if (m->m == 2)
    {
        int v1 = multGrpQuot((m->mat)[0][0], (m->mat)[1][1], m->p) ; 
        int v2 = multGrpQuot((m->mat)[1][0], (m->mat)[0][1], m->p) ; 
        return addiGrpQuot(v1, -v2, m->p) ; 
    }

    int res = 0 ; 
    int coef = 1 ; 

    for (int t = 0 ; t < m->n ; t++)
    {
        if ((m->mat[t][0] % m->p) != 0)
        {
            mat *matMineure = matriceMineure(m, t, 0) ; 
            int a = multGrpQuot((m->mat)[t][0], detMatrice(matMineure), m->p) ; 
            int b = multGrpQuot(coef, a, m->p) ; 
            res = addiGrpQuot(res, b, m->m) ; 
            libereMatrice(matMineure) ; 
        }
        coef *= -1 ; 
    }
    return res ; 
}


/*
Réalise la dilation suivante :
    - l <= coef * l si type = 'm'
    - l <= coef^-1 * l si type = 'd' 
*/ 
void dilateLigne (mat *m, int coef, int ligne, char type)
{
    switch (type)
    {
        case 'd' :
            coef = invGrpQuot(coef, m->p) ; 
            for (int j = 0 ; j < m->m ; j++)
            {
                (m->mat)[ligne][j] = multGrpQuot(coef, (m->mat)[ligne][j], m->p) ; 
            }
            break ;

        case 'm' : 
            for (int j = 0 ; j < m->m ; j++)
            {
                (m->mat)[ligne][j] = multGrpQuot(coef, (m->mat)[ligne][j], m->p) ; 
            }
            break ; 

        default :
            printf("Mauvais caractere dans dilateLigne : %c\n", type) ; 
            break ;
    }
}


// Effectue la permutations des lignes de numéros l1 et l2 
void permutationLigne (mat *m, int l1, int l2)
{
    if (l1 == l2)
    {
        return ; 
    }
    int temp ; 
    for (int j = 0 ; j < m->m ; j++)
    {
        temp = (m->mat)[l1][j] ; 
        (m->mat)[l1][j] = (m->mat)[l2][j] ; 
        (m->mat)[l2][j] = temp ; 
    }
}


/*
Effectue la transvection suivante : 
    - l1 <= l1 + coef * l2 si type = 'm'
    - l1 <= l1 + coef^-1 * l2 si type = 'd'
*/ 
void transvectionLigne (mat *m, int l1, int coef, int l2, char type) 
{
    if (l1 == l2)
    {
        return ; 
    }

    switch (type)
    {
        case 'm' :

            for (int j = 0 ; j < m->m ; j++)
            {
                // (m->mat)[l1][j] = (((m->mat)[l1][j] + (coef * (m->mat)[l2][j] % premier))  + premier) % premier; 
                int a = multGrpQuot(coef, (m->mat)[l2][j], m->p) ; 
                (m->mat)[l1][j] = addiGrpQuot(a, (m->mat)[l1][j], m->p) ; 
            }
            break ;

        case 'd' : 
            coef = invGrpQuot(coef, m->p) ; 
            for (int j = 0 ; j < m->m ; j++)
            {
                // (m->mat)[l1][j] = ((m->mat)[l1][j] + (invGrpQuot(coef, premier) * (m->mat)[l2][j] % premier)) % premier; 
                int a = multGrpQuot(coef, (m->mat)[l2][j], m->p) ; 
                (m->mat)[l1][j] = addiGrpQuot(a, (m->mat)[l1][j], m->p) ; 
            }
            break ; 

        default:
            printf("Mauvais caractere dans transvectionLigne : %c\n", type) ; 
            return ; 
    }

}


void ecrireMatrice (FILE *f, mat *m)
{
    // écrit une matrice dans le fichier passé en paramètre 
    fprintf(f, "n=%d,m=%d,p=%d\n", m->n, m->m, m->p) ; 

    for (int i = 0 ; i < m->n ; i++)
    {
        for (int j = 0 ; j < m->m - 1 ; j++)
        {
            fprintf(f, "%d,", (m->mat)[i][j]) ; 
        }
        fprintf(f, "%d\n", (m->mat)[i][m->m - 1]) ; 
    }
}


mat *lireMatrice (FILE *f)
{
    // Lit une matrice à partir d'un fichier passé en entrée 
    char buff [MAXBUFF] ;  
    int n, m, p ; 
    /*    
    */
    if (fgets(buff, MAXBUFF, f) == NULL) 
    {
        printf("Erreur de lecture du fichier\n") ; 
        return 0 ; 
    }

    if (sscanf(buff, "n=%d,m=%d,p=%d\n", &n, &m, &p) != 3) 
    {
        printf("Erreur de format de fichier\n") ; 
        return 0 ; 
    }

    mat *res = creeMatrice(n, m, p) ; 

    char *temp = NULL ; 
    // On lit le fichier 

    for (int i = 0 ; i < n ; i++)
    {
        fgets(buff, MAXBUFF, f) ; 
        temp = strtok(buff, ",") ; 
        (res->mat)[i][0] = atoi(temp) ; 
        for (int j = 1 ; j < m ; j++)
        {
            temp = strtok(NULL, ",") ; 
            (res->mat)[i][j] = atoi(temp) ; 
        }
    }
    return res ; 
}


// Renvoie la transposée de la matrice, ne libère pas la mémoire de la matrice originale 
mat *tranposeMatrice (mat *m)
{
    mat *res = creeMatrice(m->m, m->n, m->p) ; 
    for (int i = 0 ; i < m->n ; i++)
    {
        for (int j = 0 ; j < m->m ; j++)
        {
            (res->mat)[j][i] = (m->mat)[i][j] ; 
        }
    }
    return res ; 
}

int rangMatrice (mat *pa)
{
    mat *m = copieMatrice(pa) ; 

    int lignePivot = 0 ; 

    
}

// Elimination de Gauss-Jordan, renvoie NULL si la matrice est non-inversible 
mat *eliminationGaussJordan (mat *pa)
{
    mat *m = copieMatrice(pa) ; 
    mat *res = matriceDiag(1, m->m, m->p) ; 

    if (detMatrice(m) == 0) 
    {
        return NULL ; 
    }

    int lignePivot = 0 ; 

    for (int j = 0 ; j < m->n ; j++)
    {
        // On cherche la première ligne dont le coefficient dans la colonne donnée est inversible
        int nbChange = lignePivot ; 
        for (int i = lignePivot ; i < m->m ; i++)
        {

            //if (((m->mat)[i][j] % premier) != 0)
            if ((m->mat[i][j] % m->p) != 0)
            {
                nbChange = i ; 
                break ;
            }

        }

        // On a trouvé la bonne ligne, si cette ligne est différente de la ligne pivot, on l'échange 
        permutationLigne(res, nbChange, lignePivot) ; 
        permutationLigne(m, nbChange, lignePivot) ;
        
        // On divise cette ligne par l'inverse du pivot 
        //dilateLigne(res, (m->mat)[lignePivot][j], lignePivot, premier, 'd') ; 
        //dilateLigne(m, (m->mat)[lignePivot][j], lignePivot, premier, 'd') ; 
        dilateLigne(res, (m->mat)[lignePivot][j], lignePivot, 'd') ; 
        dilateLigne(m, (m->mat)[lignePivot][j], lignePivot, 'd') ; 

        // On doit simplifier chacune des qui sont en-dessus dont les coefficients sont nuls 
        for (int i = lignePivot + 1 ; i < m->m ; i++)
        {
            //if (((m->mat)[i][j] % premier) != 0)
            if (((m->mat)[i][j] % (m->p)) != 0)
            {
                //transvectionLigne(res, i, -(m->mat)[i][j], lignePivot, premier, 'm') ; 
                //transvectionLigne(m, i, -(m->mat)[i][j], lignePivot, premier, 'm') ; 
                transvectionLigne(res, i, -(m->mat)[i][j], lignePivot, 'm') ; 
                transvectionLigne(m, i, -(m->mat)[i][j], lignePivot, 'm') ; 
            }
        }

        lignePivot += 1 ; 
    }

    // On a donc obtenu une matrice échelonnée, dont tout les pivots sont alignés
    // On va donc la transformer en une matrice échelonnée réduite 
    for (int j = m->m - 1; j >= 0 ; j--)
    {
        for (int i = j - 1 ; i >= 0 ; i--)
        {
            //transvectionLigne(res, i, -(m->mat)[i][j], j, premier, 'm') ; 
            //transvectionLigne(m, i, -(m->mat)[i][j], j, premier, 'm') ; 
            transvectionLigne(res, i, -(m->mat)[i][j], j, 'm') ; 
            transvectionLigne(m, i, -(m->mat)[i][j], j, 'm') ; 
        }
    }

    libereMatrice(m) ; 
    return res ; 

} 