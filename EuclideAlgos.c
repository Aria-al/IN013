#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "EuclideAlgos.h"


// ax == 1 [b] sachant que on connaît a et b ; ax = 1 + by ; ax - by = 1 

// Renvoie la division euclidienne de max(a, b) par min(a, b) : max(a, b) = min(a, b) * res[2] + res[3] 
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


int algoEuclide (int a, int b)
{
    int t ; 
    while (b)
    {
        t = b ; 
        b = a % b ; 
        a = t ; 
    }
    return a ; 
}


int sommeGroupe (int a, int b, int p)
{
    return (((a + b) % p) + p) % p ; 
}


int produitGroupe (int a, int b, int p) 
{
    return (((a * b) % p) + p) % p ; 
}


// Renvoie l'invese de a dans l'anneau Z/pZ
int inverseGroupeQuotient (int a, int p)
{
    int t[3] ; 
    if (a < 0)
    {
        a = (a % p) + p ; 
    }
    alogEuclideEtendu(a, p, t) ; 
    if (t[1] < 0)
    {
        t[1] = (t[1] % p) + p ; 
    }
    return t[1] ; 
}


// Renvoie un couple de coefficients de bézout (u, v) = (res[1], res[2]) tel que : res[0] = res[1] * a + res[2] * b
void alogEuclideEtendu (int a, int b, int res[3])
{
    int r = a, rp = b ; 
    int u = 1, up = 0 ; 
    int v = 0, vp = 1 ; 
    int q = 0 ; 
    int rs, us, vs ; 
    int j = 0 ;
    while (rp)
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