#include "controller.h"
#include <iostream>
#include "localitate.h"
#include "ruta.h"

int main() {
    std::vector<Localitate> localitati;
    std::vector<Ruta> rute;

    while (true) {
        std::cout << "\nMeniu:\n";
        std::cout << "1. Adaugare localitate\n";
        std::cout << "2. Adaugare ruta autocar\n";
        std::cout << "3. Afisarea localitatilor ordonate după numărul de rute dus-intors\n";
        std::cout << "4. Afisarea tuturor rutelor care se opresc intr-o localitate municipiu\n";
        std::cout << "5. Export JSON\n";
        std::cout << "0. Iesire\n";
        std::cout << "Selectati o optiune: ";

        int optiune;
        std::cin >> optiune;

        switch (optiune) {
            case 1:
                adaugaLocalitate(localitati);
                break;
            case 2:
                adaugaRuta(rute, localitati);
                break;
            case 3:
                afiseazaLocalitatiOrdonate(localitati, rute);
                break;
            case 4:
                afiseazaRuteInMunicipiu(localitati, rute);
                break;
            case 5:
                exportJson(localitati, rute);
                break;
            case 0:
                salveazaDate(localitati, rute);
                return 0;
            default:
                std::cout << "Opțiune invalidă.\n";
                break;
        }
    }

    return 0;
}
