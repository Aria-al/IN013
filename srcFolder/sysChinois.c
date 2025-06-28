#include "./hdrFolder/sysChinois.h"

sytChi *creeEq (int nbEqua)
{
    // Crée un sytème de reste chinois avec nbEqua équations 
    sytChi *res = malloc(sizeof(sytChi)) ; 
    res->nbEqua = nbEqua ; 
    res->x = 0 ; 
    res->aCoef = malloc(sizeof(int) * nbEqua) ; 
    res->mMods = malloc(sizeof(int) * nbEqua) ; 
    return res ; 
}


// Lit un système de reste chinois dans un fichier passé en paramètre 
sytChi *lireSytChi (FILE *f)
{
    char buff [MAXBUFF] ;  
    int nbEqa, x ; 

    if (fgets(buff, MAXBUFF, f) == NULL) 
    {
        printf("Erreur de lecture du fichier\n") ; 
        return 0 ; 
    }

    if (sscanf(buff, "nbEqa : %d, x : %d\n", &nbEqa, &x) != 2) 
    {
        printf("Erreur de lecture de fichier 2 \n") ; 
        return 0 ; 
    }

    sytChi *res = creeEq(nbEqa) ; 

    res->x = x ; 
    int a, mod ; 
    for (int i = 0 ; i < res->nbEqua ; i++)
    {
        fgets(buff, MAXBUFF, f) ; 
        if (sscanf(buff, "%d [%d]\n", &a, &mod) != 2)
        {
            return NULL ; 
        }
        (res->aCoef)[i] = a ; 
        (res->mMods)[i] = mod ; 
    }
    return res ; 
}


// Ecrit un système de reste chinois dans un fichier passé en paramètre 
void ecrireSytChi (FILE *f, sytChi *s)
{
    fprintf(f, "nbEqa : %d, x : %d\n", s->nbEqua, s->x) ; 
    for (int i = 0 ; i < s->nbEqua ; i++)
    {
        fprintf(f, "%d [%d]\n", (s->aCoef)[i], (s->mMods)[i]) ; 
    }
}


// Affiche un système de reste chinois 
void affSytChi (sytChi *s)
{
    printf("nbEqua : %d, x : %d\n", s->nbEqua, s->x) ; 
    for (int i = 0 ; i < s->nbEqua ; i++)
    {
        printf("%d = %d [%d]\n", s->x, (s->aCoef)[i], (s->mMods)[i]) ; 
    }
}


// Résouds un système de reste chinois à 2 équations 
void resoudreSytChiDuo(sytChi *s)
{
    int t[3] ; 
    alogEucliEtendu((s->mMods)[0], (s->mMods)[1], t) ; 
    s->x = (t[2] * (s->mMods)[1] * (s->aCoef)[0]) + (t[1] * (s->mMods)[0] * (s->aCoef)[1]) ; 
    s->x = (s->x % ((s->mMods)[0] * (s->mMods)[1])) + ((s->mMods)[0] * (s->mMods)[1]) ; 
}

// Résout un système de reste chinois à n équations 
void resoudreSytChiRec (sytChi *s)
{
    sytChi *temp = creeEq(2) ; 
    (temp->mMods)[0] = (s->mMods)[0] ; 
    (temp->mMods)[1] = (s->mMods)[1] ; 
    (temp->aCoef)[0] = (s->aCoef)[0] ; 
    (temp->aCoef)[1] = (s->aCoef)[1] ; 
    resoudreSytChiDuo(temp) ; 

    for (int i = 2 ; i < s->nbEqua ; i++)
    {
        (temp->mMods)[0] = ((temp->mMods)[0] * (temp->mMods)[1]) ; 
        (temp->mMods)[1] = (s->mMods)[i] ; 
        (temp->aCoef)[0] = temp->x ; 
        (temp->aCoef)[1] = (s->aCoef)[i] ; 
        resoudreSytChiDuo(temp) ; 
    }
    s->x = temp->x ; 
    libereSytChi(temp) ; 
}

// Libère la mémoire allouée à un système de reste chinois 
void libereSytChi (sytChi *s) 
{
    free(s->aCoef) ; 
    free(s->mMods) ; 
    free(s) ; 
}


/*
Version optimisé de résolveur de système de reste chinois 
1. On fork le programme pour chaque couple d'équation disponible au début 
2. Chaque fils possédant 2 équations, on éxécute la résolution d'un sytème pour 2 équations 
3. Le père attend que 2 fils ont fini, recrée un nouveau fils qui exécute la résolution sur
les deux équations obtenues 
4. On fait ceci jusqu'à ce qu'il ne reste qu'une seule équations 

*/