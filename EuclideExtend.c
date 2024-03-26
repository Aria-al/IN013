#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void divisionEucli (int a, int b, int res[4])
{
    int max, min ; 
    if (a > b)
    {
        max = a ; 
        min = b ; 
    }
    else 
    {
        max = b ; 
        min = a ; 
    }
    res[0] = max ; 
    res[1] = min ; 
    res[2] = max / min ; 
    res[3] = max - (res[2] * min) ; 
}

int inverseGroupeQuotient (int a, int p)
{
    int tab[4] = {0, 0, 0, 0} ; 
    int j = 1 ; 
    divisionEucli(a * j, p, tab) ; 
    printf("%d = %d * %d + %d\n", tab[0], tab[1], tab[2], tab[3]) ; 
    while ((j < 100) && (tab[3] != 1))
    {
        j += 1 ; 
        for (int i = 0 ; i < 4 ; i++)
        {
            tab[i] = 0 ; 
        }
        divisionEucli(a * j, p, tab) ; 
        printf("%d = %d * %d + %d\n", tab[0], tab[1], tab[2], tab[3]) ; 
    }
    return j ; 
}

void alogEuclideEtendu (int a, int b, int res[3])
{
    int r = a, rp = b ; 
    int u = 1, up = 0 ; 
    int v = 0, vp = 1 ; 
    int q = 0 ; 
    int rs, us, vs ; 
    int j = 0 ;
    while ((rp) && (j < 10000))
    {
        q = r / rp ; 
        rs = r ; us = u ; vs = v ; 
        r = rp ; u = up ; v = vp ; 
        rp = rs - (rp * q) ; 
        up = us - (up * q) ; 
        vp = vs - (vp * q) ; 
        j += 1 ; 
    }
    res[0] = r ; res[1] = u ; res[2] = v ; 
}

int main(int argc, char const *argv[])
{
    int d = -1 ; 
    int a, b ; 
    while (d != 0)
    {
        printf("Entrer la decision :\n0.Sortie de programme\n1.Algo Etendu d'euclide\n2.Division euclidienne\n3.Inverse groupe quotient\n") ; 
        scanf("%d", &d) ; 
        switch (d)
        {
        case 1 :
            int tab1[3] = {0, 0, 0} ; 
            printf("Valeurs de a et b, a>b\n") ; 
            scanf("%d %d", &a, &b) ; 
            alogEuclideEtendu(a, b, tab1) ;     
            printf("%d = %d * %d + %d * %d\n", tab1[0], a, tab1[1], b, tab1[2]) ; 
            break;
        
        case 2 : 
            int tab2[4] = {0, 0, 0, 0} ; 
            printf("Valeurs de a et b, a > b\n") ; 
            scanf("%d %d", &a, &b) ; 
            divisionEucli(a, b, tab2) ;
            printf("%d = %d * %d + %d\n", tab2[0], tab2[1], tab2[2], tab2[3]) ; 
            break;
        
        case 3 :
            printf("Valeurs de a et p, Z/pZ\n") ; 
            scanf("%d %d", &a, &b) ; 
            while (a < b)
            {
                a += b ; 
            }
            printf("a=%d, p=%d\n", a, b) ; 
            int q = inverseGroupeQuotient(a, b) ; 
            printf("%d\n", q) ; 
            break;

        default:
            break;
        }
        a = 0 ; 
        b = 0 ; 
    }
    return 0;
}
