#include <string>
#pragma once

using namespace std;

class Ruta {
private:
    std::string id;
    std::string idPornire;
    std::string idOprire;
    double pret;
    bool dusIntors;

public:
    Ruta(std::string id, std::string idPornire, std::string idOprire, double pret, bool dusIntors);

    std::string getId() const;

    std::string getIdPornire() const;

    std::string getIdOprire() const;

    double getPret() const;

    bool isDusIntors() const;
};
