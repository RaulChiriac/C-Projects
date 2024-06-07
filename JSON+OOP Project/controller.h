#include "localitate.h"
#include "ruta.h"
#include <vector>
#pragma once

void salveazaDate(const std::vector<Localitate>& localitati, const std::vector<Ruta>& rute);

void exportJson(const std::vector<Localitate>& localitati, const std::vector<Ruta>& rute);

void afiseazaRuteInMunicipiu(const std::vector<Localitate>& localitati, const std::vector<Ruta>& rute);

void afiseazaLocalitatiOrdonate(const std::vector<Localitate>& localitati, const std::vector<Ruta>& rute);

void adaugaLocalitate(std::vector<Localitate>& localitati);

void adaugaRuta(std::vector<Ruta>& rute, const std::vector<Localitate>& localitati);

