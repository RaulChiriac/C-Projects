#include "localitate.h"

Localitate::Localitate(std::string id, std::string nume, std::string tip)
        : id(id), nume(nume), tip(tip) {}

std::string Localitate::getId() const {
    return this->id;
}

std::string Localitate::getNume() const {
    return this->nume;
}

std::string Localitate::getTip() const {
    return this->tip;
}
