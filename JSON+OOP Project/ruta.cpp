#include "ruta.h"

Ruta::Ruta(std::string id, std::string idPornire, std::string idOprire, double pret, bool dusIntors)
        : id(id), idPornire(idPornire), idOprire(idOprire), pret(pret), dusIntors(dusIntors) {}

std::string Ruta::getId() const {
    return this->id;
}

std::string Ruta::getIdPornire() const {
    return this->idPornire;
}

std::string Ruta::getIdOprire() const {
    return this->idOprire;
}

double Ruta::getPret() const {
    return this->pret;
}

bool Ruta::isDusIntors() const {
    return this->dusIntors;
}