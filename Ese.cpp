#include "Ese.h"
#include <utility> // std::move

Ese::Ese(std::string n, std::string k) : nimi(std::move(n)), kirjeldus(std::move(k)) {
}

std::string Ese::getNimi() const {
    return nimi;
}

std::string Ese::getKirjeldus() const {
    return kirjeldus;
}

void Ese::setKirjeldus(std::string k) {
    this->kirjeldus = std::move(k);
}