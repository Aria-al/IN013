#include "./hdrFolder/fctSuite.h"


int mod (int a)
{
    return a % 192217 ; 
}

int main ()
{
    printf("HIII\n") ; 
    FILE *f = fopen("ex3.txt", "r") ; 
    RelRec *relation = lireRelRec(f) ; 
    afficheRelRec(relation) ; 
    int nbVal = 15 ; 
    int *listExp = calculeTermesSuite(relation, nbVal) ; 
    int *temp = map(listExp, nbVal, mod) ; 
    afficheTableau(temp, nbVal) ; 
    RelRec *trouve = determineRelationV1(nbVal, temp, 13) ; 

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