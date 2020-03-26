#include <iostream>

class tabla;

const int varsta_max = 100;
const double energie_inceput = 400;
const double c1 = energie_inceput;
const double c2 = energie_inceput / 4;
const double c3 = energie_inceput / 8;

class individ
{
    private:
        int i, j;
        char tip;
        int varsta;
        double energie;
        unsigned char viu;
        tabla *tabela; // pointer catre tabla de care apartine

        void hraneste();
        void inmulteste();
        void ataca();
        void imbatraneste();
        void moare();

    public:
        individ(int x, int y, char t, tabla* M);
        //~individ();
        void actualizare();
        bool esteviu();
        char gettip();
        friend std::ostream& operator <<(std::ostream &os, const individ &x);

};

