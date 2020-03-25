#include <iostream>
#include <tabla.h>
#include <individ.h>
#include <fstream>


int main()
{
    std::ofstream g("test.out");

    tabla t;
    t.initializare(); // intializeaza tabla cu un nr aleator de indivizi
    std::cout << t;
    std::cin >> t;    // citeste indivizi de la tastatura


    for (int i = 0; i < 1000 && t.test_indivizi(); i++)
    {
        t.actualizare();
        g << t; // afiseaza in fisier evolutia jocului
    }

    std::cout << "Deschide fisierul test.out pentru a vedea evolutia jocului!\n";
    return 0;
}
