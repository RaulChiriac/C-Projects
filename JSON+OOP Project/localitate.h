#include <string>
#pragma once
using namespace std;

class Localitate {
private:
    string id;
    string nume;
    string tip;

public:
    Localitate(string id, string nume, string tip);

    string getId() const;

    string getNume() const;

    string getTip() const;
};

