#include "individ.h"
#include <tabla.h>
#include <cmath>


individ::individ(int x, int y, char t, tabla* M)
{
    /* Initializeaza individul cu valorile parametrilor */

    tabela = M;
    i = x;
    j = y;
    tip = t;
    energie = energie_inceput; // energia de inceput este o constanta
    varsta = 0;
    viu = 1;
}


char individ::gettip()
{
    return tip;
}

bool individ::esteviu()
{
    return viu;
}

void individ::actualizare()
{
    /* Aplica succesiv metodele de mai jos. */

    hraneste();
    inmulteste();
    ataca();
    imbatraneste();
}

void individ::hraneste()
{
    /* Calculeaza numarul de pozitii libere invecinate(aportul), iar apoi creste
    energia dupa formula de mai jos.*/

    int aport = 1;
    int di[] = {-1,0,1,0};
    int dj[] = {0,1,0,-1};
    for (int dir = 0; dir < 4; dir++)
    {
        if (tabela->verif_poz_libera(i+di[dir], j+dj[dir]))
            aport++;
    }

    energie += (double) (c1 * aport) / (abs(varsta - varsta_max / 2) + 1); // c1 este o constata pentru cresterea energiei
}
void individ::inmulteste()
{
    /* Calculeaza numarul de fii(minim 0, maxim 4) ce vor fi alocati pe pozitiile libere invecinate.
    Pentru fiecare alocare a unui fiu, se scade din energia proprie o constanta c2. */

    int nr_fii_alocati, v = abs(varsta - (varsta_max) / 2) + 1;
    if (energie * v < energie_inceput * 50)
        nr_fii_alocati = 0;
    else if (energie * v < energie_inceput * 60)
        nr_fii_alocati = 1;
    else if (energie * v < energie_inceput * 70)
        nr_fii_alocati = 2;
    else if (energie * v < energie_inceput * 80)
        nr_fii_alocati = 3;
    else
        nr_fii_alocati = 4;

    int di[] = {-1,0,1,0};
    int dj[] = {0,1,0,-1};
    for (int dir = 0; dir < 4 && nr_fii_alocati != 0; dir++)
    {
        if (tabela->verif_poz_libera(i+di[dir], j+dj[dir]))
        {
            tabela->alocare(i+di[dir], j+dj[dir], tip);
            nr_fii_alocati--;
            energie -= c2;
        }
    }
}

void individ::ataca()
{
    /* Verifica pentru fiecare pozitie invecinata daca se afla un individ de alt tip
     a carui energie este mai mica decat cea proprie, caz in care din energia proprie
     se scade energia dusmanului, caruia i se aplica metoda moare */

    int di[] = {-1,0,1,0};
    int dj[] = {0,1,0,-1};
    for (int dir = 0; dir < 4; dir++)
    {
        individ* dusman = tabela->get_individ(i+di[dir], j+dj[dir]);
        if (dusman != NULL && tip != dusman->tip && energie > dusman->energie)
        {
            energie -= dusman->energie;
            dusman->moare();
        }
    }
}

void individ::imbatraneste()
{
    /* Creste varsta cu 1 si scade energia cu constanta c3.
    Daca varsta este egala cu varsta maxima sau energia este <=0, atunci individul moare. */

    varsta += 1;
    energie -= c3;

    if (varsta == varsta_max || energie <= 0)
        moare();
}

void individ::moare()
{
    // Seteaza viu cu valoare 0.

    viu = 0;
}

std::ostream& operator <<(std::ostream &os, const individ& x)
{
    // Afiseaza informatii despre un individ.

    os << "Locatia pe tabla a individului este (" << x.i << ", " << x.j << ")\n";
    os << "Tip: " << x.tip << '\n';
    os << "Varsta: " << x.varsta << '\n';
    os << "Energie: " << x.energie << '\n';
    return os;
}
