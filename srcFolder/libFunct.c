#include "./hdrFolder/libFunct.h"

int min (int a, int b) 
{
    if (a < b) 
    {
        return a ; 
    }
    return b ; 
}

int max (int a, int b)
{
    if (a < b)
    {
        return b ; 
    }
    return a ; 
}

int *etendTableau (int *tab, int len) 
{
    // On suppose que len == #(tab)
    int *res = malloc(sizeof(int) * (2 * len)) ; 
    
    for (int i = 0 ; i < len ; i++)
    {
        res[i] = tab[i] ; 
    }

    for (int i = len ; i < 2 * len ; i++)
    {
        res[i] = 0 ; 
    }

    return res ; 
}

int *copieTableau (int *tab, int len)
{
    // On suppose que len == #(tab) - 1
    int *res = malloc(sizeof(int)*(len)) ; 

    for (int i = 0 ; i < len ; i++)
    {
        res[i] = tab[i] ; 
    }

    return res ; 
}

int *map (int *tab, int len, int (*func) (int))
{
    int *res = malloc(sizeof(int) * len) ; 
    for (int i = 0 ; i < len ; i++)
    {
        res[i] = func(tab[i]) ; 
    }
    return res ; 
}

void afficheTableau (int *tab, int len)
{
    for (int i = 0 ; i < len - 1 ; i++)
    {
        printf("[%d,%d], ", i, tab[i]) ; 
    }
    printf("[%d,%d]\n", len-1, tab[len-1]) ; 
}

// Calcule x^e
int sqrAndMult (int x, int e)
{
    int res = 1 ; 
    if (e > 0)
    {
        res = sqrAndMult(x, e/2) ; 
        switch (e % 2)
        {
        case 0 :
            res = res * res ; 
            break ;

        case 1 : 
            res = res * res * x ;     
            break ; 
        
        default :
            res = res ; 
            break ;
        }
        return res ; 
    }
    else
    {
        return res ; 
    }
    
}