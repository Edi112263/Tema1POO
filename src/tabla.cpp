#include "tabla.h"
#include <individ.h>
#include <cstdlib>
#include <ctime>


tabla::tabla()
{
    /* Initializeaza tabla cu valori nule(la inceput, nu exista niciun individ!) */

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            M[i][j] = NULL;
}

tabla::~tabla()
{
    /* Dezaloca spatiul din memorie alocat pentru indivizi. */

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (M[i][j] != NULL)
                {
                    delete M[i][j];
                    M[i][j] = NULL;
                }
}

void tabla::initializare()
{
    /* Aloca indivizi pe pozitii aleatorii in tabela. */

    srand(time(NULL));
    int k = 400,rand_i, rand_j, rand_t; // vom initializa aproximativ 400 de locuri aleatorii din tabela
    char t;
    while (k)
    {
        rand_i = rand() % n;
        rand_j = rand() % m;
        rand_t = rand() % 2;
        if (rand_t)
            t = '+';
        else
            t = '0';

        M[rand_i][rand_j] = new individ(rand_i, rand_j, t, this); // creeaza un nou individ care va contine si un pointer catre tabla de care apartine
        k--;
    }
}

void tabla::actualizare()
{
    /* Pentru fiecare individ de pe tabla, daca acesta este viu,
    ii aplicam metoda actualizare, altfel il stergem de pe tabla */

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (M[i][j] != NULL) // daca M[i][j] egal cu null inseamna ca nu exista niciun individ pe pozitia (i,j).
            {
                if (M[i][j]->esteviu())
                    M[i][j]->actualizare();
                else
                {
                    delete M[i][j];
                    M[i][j] = NULL; // pointerul devine NULL pentru a marca faptul ca pozitia (i,j) a devenit libera.
                }
            }

        }
    }
}

bool tabla::verif_poz_libera(int i, int j)
{
    /* Verifica daca pozitia (i,j) nu depaseste marginile tablei
    si nu se afla niciun individ pe ea. */

    if (i < 0 || i >= n || j < 0 || j >= m || M[i][j] != NULL)
        return false;

    return true;
}

individ* tabla::get_individ(int i, int j)
{
    /* Intoarce adresa individului de pe pozitia (i, j) */

    if (i < 0 || i >= n || j < 0 || j >= m)
        return NULL;

    return M[i][j];
}

void tabla::alocare(int i, int j, char tip)
{
    /* Creeaza un nou individ pe pozitia (i,j) de pe tabla */

    if (verif_poz_libera(i, j))
        M[i][j] = new individ(i, j, tip, this);
}

bool tabla::test_indivizi()
{
    /* Verifica daca mai exista indivizi pe tabla */

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (M[i][j] != NULL)
                return true;
        }
    }
    return false;
}

std::ostream& operator <<(std::ostream &os, const tabla &t)
{
    /* Afiseaza tabla actuala. */


    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (t.M[i][j] != NULL)
                os << t.M[i][j]->gettip() << ' '; // afiseaza tipul individului
            else
                os << '-' << ' '; // simbolul '-' reprezinta faptul ca nu exista un individ pe pozitia (i,j)
        }
        os << '\n';
    }
    os << "\n\n\n\n\n\n\n\n";
    return os;
}

std::istream& operator >>(std::istream &is, tabla &t)
{
    /* Adauga k indivizi pe tabla introdusi de la tastatura sau dintr-un fisier. */

    int k, i, j;
    char tip;
    bool ok;
    std::cout << "Introdu numarul de indivizi pe care vrei sa-i adaugi: ";
    is >> k;
    std::cout << "\n\n";
    for (int l = 1; l <= k; l++)
    {
        std::cout << "Date pentru individul " << l << "\n\n";
        ok = false;
        while (!ok) // repeta pana cand datele introduse sunt corecte
        {
            std::cout << "Pozitia i j: "; is >> i >> j; i--; j--; // decrementam i si j intrucat numarotarea in matrice porneste de la 0
            std::cout << "Tipul(+ sau 0): "; is >> tip;

            if (t.verif_poz_libera(i, j))
            {
                    if (tip == '+' || tip == '0')
                    {
                        ok = true;
                        std::cout << "Individul " << l << " a fost adaugat cu succes!\n\n";
                    }
                    else std::cout << "Datele introduse sunt incorecte! Introdu altele.\n\n";
            }
            else std::cout << "Locul nu este disponibil. Introdu alte date!\n\n";
        }
        t.alocare(i, j, tip);
    }
    return is;
}
