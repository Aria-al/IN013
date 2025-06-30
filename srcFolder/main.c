#include "./hdrFolder/fctSuite.h"

int p = 13 ; 

int mod (int a)
{
    return a % p ; 
}

int main ()
{
    printf("HIII\n") ; 
    FILE *f = fopen("ex3.txt", "r") ; 
    RelRec *relation = lireRelRec(f) ; 
    afficheRelRec(relation) ; 
    int nbVal = 20 ; 
    int *listExp = calculeTermesSuite(relation, nbVal, p) ; 
    int *temp = map(listExp, nbVal, mod) ; 
    afficheTableau(temp, nbVal) ; 
    RelRec *trouve = determineRelationV1(nbVal, temp, p) ; 

    afficheTableau(listExp, nbVal) ; 
    libereRelRec(relation) ; 
    free(listExp) ; 
    free(temp) ; 
    if (trouve != NULL)
    {
        printf("Trouvee : \n") ; 
        afficheRelRec(trouve) ; 
        libereRelRec(trouve) ; 
    }
    fclose(f) ; 
    return 0 ; 
}