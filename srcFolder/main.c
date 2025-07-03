#include "./hdrFolder/fctSuite.h"

int p = 8083 ; 

int mod (int a)
{
    return a % p ; 
}
//128,64,32,16,8,4,2,1
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
    RelRec *trouve = determineRelationV3(nbVal, temp, p) ; 

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