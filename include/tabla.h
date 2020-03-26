#include <iostream>

class individ;

const int n = 20;
const int m = 70;

class tabla
{
    private:
        individ* M[n][m];

    public:

        tabla();
        ~tabla();
        void initializare();
        void actualizare();
        bool verif_poz_libera(int i, int j);
        individ* get_individ(int i, int j);
        void alocare(int i, int j, char tip);
        void eliminare(int i, int j);
        bool test_indivizi();
        friend std::ostream& operator <<(std::ostream& os, const tabla &t);
        friend std::istream& operator >>(std::istream& is, tabla &t);
};

