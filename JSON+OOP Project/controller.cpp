#include "controller.h"
#include <fstream>
#include "single_include/nlohmann/json.hpp"
#include <iostream>

using Json = nlohmann::json;

/// Functie de salvare a localitatiilor si rutelor in fisierele lor
void salveazaDate(const std::vector<Localitate>& localitati, const std::vector<Ruta>& rute) {
    std::ofstream fLocalitati("localitati_export.txt");
    std::ofstream fRute("rute_export.txt");

    if (fLocalitati.is_open()) {
        for (const auto& loc : localitati) {
            fLocalitati << loc.getId() << "," << loc.getNume() << "," << loc.getTip() << "\n";
        }
        fLocalitati.close();
    }

    if (fRute.is_open()) {
        for (const auto& r : rute) {
            fRute << r.getId() << "," << r.getIdPornire() << "," << r.getIdOprire() << ","
                  << r.getPret() << "," << r.isDusIntors() << "\n";
        }
        fRute.close();
    }
}

/// Functie de exportare a fisierelor loclitati.txt si rute.txt in export.json
void exportJson(const std::vector<Localitate>& localitati, const std::vector<Ruta>& rute) {
    Json exportData;

    for (const auto& loc : localitati) {
        Json destinatii;
        for (const auto& ruta : rute) {
            if (ruta.getIdPornire() == loc.getId()) {
                for (const auto& loc_dest : localitati) {
                    if (loc_dest.getId() == ruta.getIdOprire()) {
                        destinatii.push_back(loc_dest.getNume());
                    }
                }
            }
        }
        exportData[loc.getNume()] = destinatii;
    }

    std::ofstream fExport("export.json");
    if (fExport.is_open()) {
        fExport << exportData.dump(4);
        std::cout << "Datele au fost exportate în format JSON.\n";
    } else {
        std::cout << "Eroare la deschiderea fisierului pentru export JSON.\n";
    }
}

/// Functie care afiseaza rutele care au ca localitate de oprire municipiu
void afiseazaRuteInMunicipiu(const std::vector<Localitate>& localitati, const std::vector<Ruta>& rute) {
    for (const auto& ruta : rute) {
        for (const auto& loc : localitati) {
            if (loc.getId() == ruta.getIdOprire() && loc.getTip() == "municipiu") {
                std::cout << "Ruta " << ruta.getId() << " intre "
                          << loc.getNume() << " si ";
                for (const auto& loc_pornire : localitati) {
                    if (loc_pornire.getId() == ruta.getIdPornire()) {
                        std::cout << loc_pornire.getNume() << "\n";
                    }
                }
            }
        }
    }
}

/// Functie de sortare
void afiseazaLocalitatiOrdonate(const std::vector<Localitate>& localitati, const std::vector<Ruta>& rute) {
    std::vector<std::pair<Localitate, int>> numarRute;

    for (const auto& loc : localitati) {
        int count = std::count_if(rute.begin(), rute.end(), [&](const Ruta& rute) {
            return rute.getIdPornire() == loc.getId() && rute.isDusIntors();
        });
        numarRute.push_back({loc, count});
    }

    std::sort(numarRute.begin(), numarRute.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
    });

    for (const auto& [loc, count] : numarRute) {
        std::cout << loc.getNume() << ": " << count << " rute dus-intors\n";
    }
}

void adaugaLocalitate(std::vector<Localitate>& localitati) {
    std::string id, nume, tip;
    std::cout << "ID localitate: ";
    std::cin >> id;
    std::cout << "Nume localitate: ";
    std::cin.ignore();
    std::getline(std::cin, nume);
    std::cout << "Tip localitate (sat/oras/municipiu): ";
    std::cin >> tip;

    for (const auto& loc : localitati) {
        if (loc.getId() == id) {
            std::cout << "ID-ul localitații exista deja.\n";
            return;
        }
    }

    if (nume.empty()) {
        std::cout << "Numele localitatii nu poate fi nul.\n";
        return;
    }

    localitati.push_back(Localitate(id, nume, tip));
    std::cout << "Localitate adaugata cu succes.\n";
}

void adaugaRuta(std::vector<Ruta>& rute, const std::vector<Localitate>& localitati) {
    std::string id, idPornire, idOprire;
    double pret;
    bool dusIntors;
    std::cout << "ID ruta: ";
    std::cin >> id;
    std::cout << "ID localitate pornire: ";
    std::cin >> idPornire;
    std::cout << "ID localitate oprire: ";
    std::cin >> idOprire;
    std::cout << "Pret: ";
    std::cin >> pret;
    std::cout << "Dus-intors (1 pentru true, 0 pentru false): ";
    std::cin >> dusIntors;

    bool validPornire = false, validOprire = false;

    for (const auto& loc : localitati) {
        if (loc.getId() == idPornire) validPornire = true;
        if (loc.getId() == idOprire) validOprire = true;
    }

    if (!validPornire || !validOprire || idPornire == idOprire) {
        std::cout << "Localitatile de pornire si oprire trebuie sa existe si sa fie distincte.\n";
        return;
    }

    rute.push_back(Ruta(id, idPornire, idOprire, pret, dusIntors));
    std::cout << "Ruta adaugata cu succes.\n";
}
