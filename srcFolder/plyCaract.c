#include "./hdrFolder/plyCaract.h"

// Affiche le polynome passé en paramètre 
void affichePoly (Poly *p) 
{
    for (int i = 0 ; i < p->d + 1; i++)
    {
        printf("%d*X^%d ", (p->coefs)[i], i) ; 
    }
    printf("\n") ; 
}

void affichePolyAlt(Poly *p)
{
    ecritPoly(stdout, p) ; 
}

Poly *copierPoly (Poly *P, int d) 
{
    Poly *res = malloc(sizeof(Poly)) ; 
    res->d = d ; 
    res->coefs = malloc(sizeof(int) * (d + 1)) ; 
    
    int valMin = min(P->d, d) + 1; 
    for (int i = 0 ; i < valMin ; i++)
    {
        (res->coefs)[i] = (P->coefs)[i] ; 
    }

    if (valMin == P->d + 1)
    {
        for (int j = P->d  + 1; j < d + 1 ; j++)
        {
            (res->coefs)[j] = 0 ; 
        }
    }

    return res ; 
}

Poly *sommePoly (Poly *P1, Poly *P2, int premier) 
{
    Poly *res = copierPoly(P1, max(P1->d, P2->d)) ; 
    for (int j = 0 ; j < P2->d + 1 ; j++)
    {
        (res->coefs)[j] = addiGrpQuot((res->coefs)[j], (P2->coefs)[j], premier) ; 
    }
    return res ; 
}

Poly *opposePoly (Poly *P, int premier) 
{
    Poly *res = copierPoly(P, P->d) ; 
    for (int i = 0 ; i < P->d + 1 ; i++)
    {
        (res->coefs)[i] = (((-(res->coefs)[i]) % premier) + premier) % premier ; 
    }
    return res ; 
}

Poly *initPoly (int d) 
{
    Poly *res = malloc(sizeof(Poly)) ;
    res->d = d ; 
    res->coefs = malloc(sizeof(int) * (d + 1)) ; 
    for (int i = 0 ; i < d + 1 ; i++)
    {
        (res->coefs)[i] = 0 ; 
    }
    return res ; 
}

Poly *multPoly (Poly *P1, Poly *P2, int premier)
{
    Poly *res = initPoly((P1->d + 1) * (P2->d + 1)) ; 
    for (int i = 0 ; i < P1->d + 1 ; i++)
    {
        for (int j = 0 ; j < P2->d + 1 ; j++)
        {
            (res->coefs)[i + j] = addiGrpQuot(
                multGrpQuot((P1->coefs)[i], (P2->coefs)[j], premier), 
                (res->coefs)[i + j], premier) ; 
            //printf("i=%d,j=%d,%d*x^%d\n", i, j, (res->coefs)[i + j], i+j) ; 
        }
    }
    res = raccourcitPoly(res) ; 
    return res ; 
}

Poly *lirePoly(FILE *f)
{
    char buff[MAXBUFF] ; 
    int d ; 
    if (fgets(buff, MAXBUFF, f) == NULL)
    {
        printf("Erreur de lecture de fichier\n") ; 
        return 0 ; 
    }

    if (sscanf(buff, "d=%d\n", &d) != 1)
    {
        printf("Erreur de format de fichier\n") ; 
    }

    Poly *res = malloc(sizeof(Poly)) ; 
    res->d = d ; 
    res->coefs = malloc(sizeof(int) * (d + 1)) ; 
    fgets(buff, MAXBUFF, f) ; 
    char *temp = strtok(buff, ",") ; 
    (res->coefs)[0] = atoi(temp) ; 
    for (int i = 1 ; i <= d + 1 ; i++)
    {
        temp = strtok(NULL, ",") ; 
        (res->coefs)[i] = atoi(temp) ; 
    }
    return res ; 
}

void ecritPoly (FILE *f, Poly *P) 
{
    fprintf(f, "d=%d\n", P->d) ; 
    for (int i = 0 ; i < P->d ; i++)
    {
        fprintf(f, "%d,", (P->coefs)[i]) ; 
    }
    fprintf(f, "%d\n", P->coefs[P->d]) ; 
} 

void liberePoly (Poly *P)
{
    free(P->coefs) ; 
    free(P) ; 
}

Poly *raccourcitPoly (Poly *P) 
{
    int k = P->d ; 
    while (k > 0 && ((P->coefs)[k] == 0))
    {
        k = k - 1 ; 
    }
    int *newCoefs = malloc(sizeof(int) * (k + 1)) ; 
    for (int i = 0 ; i < k + 1 ; i++)
    {
        newCoefs[i] = (P->coefs)[i] ; 
    }
    free(P->coefs) ; 
    P->coefs = newCoefs ; 
    P->d = k ; 
    return P ; 
    
}

int indxPlusGrandCoefNonNul(Poly *P, int premier)
{
    // Si premier == -1, fonctionne sur Z, sinon sur Z/premierZ
    int *tab = P->coefs ; 
    switch (premier)
    {
    case -1 :
        for (int i = P->d ; i > 0 ; i--)
        {
            if (tab[i] != 0)
            {
                return i ;
            }
        }
        break;
    
    default:
        for (int i = P->d ; i > 0 ; i--)
        {
            if ((tab[i] % premier) != 0)
            {
                return i ; 
            }
        }
        break;
    }
    return 0 ; 
}

void divisionEucliPoly (Poly *P1, Poly *P2, Poly **Q, Poly **R, int premier)  
{

    // On suppose que Q et R pointent à NULL 
    Poly *quotient ; 
    Poly *reste ; 
    Poly *numerateur = raccourcitPoly(copierPoly(P1, P1->d)) ; 
    Poly *denomiateur = raccourcitPoly(copierPoly(P2, P2->d)) ; 
    if (*Q != NULL || *R != NULL)
    {
        printf("Reecriture de pointeur quotient ou reste.\n") ; 
        return ; 
    }
    quotient = initPoly(0) ; 
    reste = NULL ; 
    
    Poly *cst ; 
    int i = 0 ; 
    while ((numerateur->d >= denomiateur->d) && (i < 10))
    {
        /*
        
        printf("HI : %d\n", i) ; 
        affichePoly(numerateur) ; 
        affichePoly(quotient) ; 
        */ 
        int coefMult = oppGrpQuot(multGrpQuot(numerateur->coefs[numerateur->d], invGrpQuot(denomiateur->coefs[denomiateur->d], premier), premier), premier) ; 
        cst = initPoly(numerateur->d - denomiateur->d) ; 
        (cst->coefs)[cst->d] = coefMult ; 
        Poly *DenTemp = multPoly(denomiateur, cst, premier) ; 
        Poly *NumTemp = sommePoly(numerateur, DenTemp, premier) ; 
        liberePoly(numerateur) ; 
        numerateur = copierPoly(NumTemp, NumTemp->d) ; 
        (cst->coefs)[cst->d] = oppGrpQuot((cst->coefs)[cst->d], premier) ; 
        Poly *QuotTemp = sommePoly(quotient, cst, premier) ; 
        liberePoly(quotient) ; 
        quotient = copierPoly(QuotTemp, QuotTemp->d) ; 
        
        liberePoly(DenTemp) ; 
        liberePoly(QuotTemp) ; 
        liberePoly(NumTemp) ; 

        numerateur = raccourcitPoly(numerateur) ; 
        quotient = raccourcitPoly(quotient) ; 

        //printf("FinPR\n") ; 
        i++ ; 
    }

    reste = copierPoly(numerateur, numerateur->d) ; 

    *Q = quotient ; 
    *R = reste ; 
}

int estPolyNul (Poly *P) 
{
    if (P)
    {
        return (P->d == 0) && (P->coefs[0] == 0) ; 
    }
    return 0 ; 
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

/*

*/
void algoEuclideEtenduPolyOriginal (Poly *P1, Poly *P2, Poly ***res, int p)
{

    // r, u, v ; 
    Poly *R = copierPoly(P1, P1->d); 
    Poly *Rprec = copierPoly(P2, P2->d) ; 
    Poly *U = initPoly(0) ; 
    U->coefs[0] = 1 ; 
    Poly *Uprec = initPoly(0) ; 
    Poly *V = initPoly(0) ; 
    V->coefs[0] = 1 ; 
    Poly *Vprec = initPoly(0) ; 
    Poly *Q = NULL ; 
    Poly *Rtemp, *Utemp, *Vtemp ; 
    Poly *Reste = NULL ; 
    Poly *temp1, *temp2, *temp3 ; 
    Poly polNul ; 
    polNul.d = 0 ; 
    polNul.coefs = malloc(sizeof(int)) ; 
    polNul.coefs[0] = 0 ; 
    int j = 0 ; 

    while (!estPolyNul(Rprec) && (j < 100))
    {
        printf("Tour : %d\n", j) ; 
        affichePoly(R) ; 
        affichePoly(Rprec) ;
        printf("Inverse du coeff = %d\n", invGrpQuot(Rprec->coefs[Rprec->d ], p)) ; 
        divisionEucliPoly(R, Rprec, &Q, &Reste, p) ; 
        printf("HI\n") ; 
        Rtemp = raccourcitPoly(copierPoly(R, R->d)) ; 
        Utemp = raccourcitPoly(copierPoly(U, U->d)) ; 
        Vtemp = raccourcitPoly(copierPoly(V, V->d)) ; 
        liberePoly(R) ; liberePoly(U) ; liberePoly(V) ; 
        R = raccourcitPoly(copierPoly(Rprec, Rprec->d)) ; 
        U = raccourcitPoly(copierPoly(Uprec, Uprec->d)) ; 
        V = raccourcitPoly(copierPoly(Vprec, Vprec->d)) ; 
        // Rprec = Rtemp - Rprec * Q
        temp1 = multPoly(Rprec, Q, p) ; 
        temp2 = opposePoly(temp1, p) ; 
        temp3 = sommePoly(Rtemp, temp2, p) ; 
        liberePoly(Rprec) ; 
        Rprec = raccourcitPoly(copierPoly(temp3, temp3->d)) ; 
        
        liberePoly(Rtemp) ; 
        liberePoly(temp1) ; 
        liberePoly(temp2) ; 
        liberePoly(temp3) ; 
        
        // Uprec = Utemp - Uprec * Q
        temp1 = multPoly(Uprec, Q, p) ; 
        temp2 = opposePoly(temp1, p) ; 
        temp3 = sommePoly(Utemp, temp2, p) ; 
        liberePoly(Uprec) ; 
        Uprec = raccourcitPoly(copierPoly(temp3, temp3->d)) ; 
        
        liberePoly(Utemp) ; 
        liberePoly(temp1) ; 
        liberePoly(temp2) ; 
        liberePoly(temp3) ; 
        
        // Vprec = Vtemp - Vprec * Q
        temp1 = multPoly(Vprec, Q, p) ; 
        temp2 = opposePoly(temp1, p) ; 
        temp3 = sommePoly(Vtemp, temp2, p) ; 
        liberePoly(Vprec) ; 
        Vprec = raccourcitPoly(copierPoly(temp3, temp3->d)) ; 
        
        liberePoly(Vtemp) ; 
        liberePoly(temp1) ; 
        liberePoly(temp2) ; 
        liberePoly(temp3) ; 
        liberePoly(Q) ; 
        liberePoly(Reste) ; 
        Q = NULL ; 
        Reste = NULL ; 

        j ++ ; 
    }

    Poly **tabRes = *res ; 
    tabRes[0] = raccourcitPoly(copierPoly(R, R->d)) ; 
    tabRes[1] = raccourcitPoly(copierPoly(U, U->d)) ; 
    tabRes[2] = raccourcitPoly(copierPoly(V, V->d)) ; 
    
    liberePoly(R) ; liberePoly(Rprec) ; 
    liberePoly(U) ; liberePoly(Uprec) ; 
    liberePoly(V) ; liberePoly(Vprec) ; 
    free(polNul.coefs) ; 
}


void algoEuclideEtenduPoly (Poly *P1, Poly *P2, Poly ***res, int p)
{

    // r, u, v ; 
    Poly *R = copierPoly(P1, P1->d); 
    Poly *Rprec = copierPoly(P2, P2->d) ; 
    Poly *U = initPoly(0) ; 
    U->coefs[0] = 1 ; 
    Poly *Uprec = initPoly(0) ; 
    Poly *V = initPoly(0) ; 
    Poly *Vprec = initPoly(0) ; 
    Vprec->coefs[0] = 1 ; 
    Poly *Q = NULL ; 
    Poly *Rs, *Us, *Vs ; 
    Poly *Reste = NULL ; 
    Poly *temp1, *temp2, *temp3 ; 
    Poly polNul ; 
    polNul.d = 0 ; 
    polNul.coefs = malloc(sizeof(int)) ; 
    polNul.coefs[0] = 0 ; 
    int j = 0 ; 

    while (!(R->d < V->d) && (j < 5))
    {
        //printf("Tour EuclideExtend: %d\n", j) ; 
        //affichePoly(R) ; 
        //affichePoly(Rprec) ; 
        //affichePoly(V) ; 
        R = raccourcitPoly(R) ; 
        Rprec = raccourcitPoly(Rprec) ; 
        
        divisionEucliPoly(R, Rprec, &Q, &Reste, p) ; 
        //affichePoly(Q) ; 
        affichePoly(Q) ; 
        affichePoly(Reste) ; 
        printf("PostDiv\n") ; 
        
        Rs = raccourcitPoly(copierPoly(R, R->d)) ; 
        Us = raccourcitPoly(copierPoly(U, U->d)) ; 
        Vs = raccourcitPoly(copierPoly(V, V->d)) ; 
        liberePoly(R) ; liberePoly(U) ; liberePoly(V) ; 
        R = raccourcitPoly(copierPoly(Rprec, Rprec->d)) ; 
        U = raccourcitPoly(copierPoly(Uprec, Uprec->d)) ; 
        V = raccourcitPoly(copierPoly(Vprec, Vprec->d)) ; 
        // Rprec = (Rs (- (Q * Rprec)))
        temp1 = multPoly(Rprec, Q, p) ; 
        temp2 = opposePoly(temp1, p) ; 
        temp3 = sommePoly(Rs, temp2, p) ; 
        liberePoly(Rprec) ; 
        Rprec = raccourcitPoly(copierPoly(temp3, temp3->d)) ; 
        
        liberePoly(Rs) ; 
        liberePoly(temp1) ; 
        liberePoly(temp2) ; 
        liberePoly(temp3) ; 
        
        // Uprec = Us - Q * Uprec
        temp1 = multPoly(Uprec, Q, p) ; 
        temp2 = opposePoly(temp1, p) ; 
        temp3 = sommePoly(Us, temp2, p) ; 
        liberePoly(Uprec) ; 
        Uprec = raccourcitPoly(copierPoly(temp3, temp3->d)) ; 
        
        liberePoly(Us) ; 
        liberePoly(temp1) ; 
        liberePoly(temp2) ; 
        liberePoly(temp3) ; 
        
        // Vprec = Vs - Q * Vprec
        temp1 = multPoly(Vprec, Q, p) ; 
        temp2 = opposePoly(temp1, p) ; 
        temp3 = sommePoly(Vs, temp2, p) ; 
        liberePoly(Vprec) ; 
        Vprec = raccourcitPoly(copierPoly(temp3, temp3->d)) ; 
        
        liberePoly(Vs) ; 
        liberePoly(temp1) ; 
        liberePoly(temp2) ; 
        liberePoly(temp3) ; 

        printf("Tour : %d\n", j) ; 
        affichePoly(Q) ; 
        affichePoly(R) ; 
        affichePoly(Rprec) ; 
        affichePoly(Uprec) ; 
        affichePoly(Vprec) ; 
        liberePoly(Q) ; 
        liberePoly(Reste) ; 
        Q = NULL ; 
        Reste = NULL ; 
        
        
        j ++ ; 
        /*
        
        */
    }
    //printf("Fin euclideEtendu\n") ; 
    //affichePoly(R) ; 
    //affichePoly(V) ; 

    Poly **tabRes = *res ; 
    tabRes[0] = raccourcitPoly(copierPoly(R, R->d)) ; 
    tabRes[1] = raccourcitPoly(copierPoly(U, U->d)) ; 
    tabRes[2] = raccourcitPoly(copierPoly(V, V->d)) ; 
    
    liberePoly(R) ; liberePoly(Rprec) ; 
    liberePoly(U) ; liberePoly(Uprec) ; 
    liberePoly(V) ; liberePoly(Vprec) ; 
    free(polNul.coefs) ; 
}