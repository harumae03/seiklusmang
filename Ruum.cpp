#include "Ruum.h"
#include <iostream>
#include <algorithm>
#include <utility> // std::move

Ruum::Ruum(std::string n, std::string k) : nimi(std::move(n)), kirjeldus(std::move(k)) {
}

std::string Ruum::getNimi() const {
    return nimi;
}

std::string Ruum::getKirjeldus() const {
    return kirjeldus;
}

void Ruum::setKirjeldus(std::string k) {
    this->kirjeldus = std::move(k);
}

void Ruum::kuvaKirjeldusTäis() const {
    std::cout << "--- " << nimi << " ---" << std::endl;
    std::cout << kirjeldus << std::endl;

    if (!esemed.empty()) {
        std::cout << "Sa näed siin järgmisi esemeid:" << std::endl;
        for (const Ese* ese : esemed) {
            if (ese) std::cout << "- " << ese->getNimi() << std::endl;
        }
    } else {
        std::cout << "Ruumis ei ole lahtiseid esemeid." << std::endl;
    }

    if (!väljapääsud.empty()) {
        std::cout << "Väljapääsud:" << std::endl;
        for (const auto& paar : väljapääsud) {
             std::cout << "- " << paar.first << std::endl;
        }
    } else {
        std::cout << "Siit ruumist ei paista olevat väljapääse." << std::endl;
    }
     std::cout << "--------------------" << std::endl;
}

void Ruum::lisaVäljapääs(const std::string& suund, Ruum* sihtkoht) {
    väljapääsud[suund] = sihtkoht;
}

Ruum* Ruum::getVäljapääs(const std::string& suund) const {
    auto it = väljapääsud.find(suund);
    if (it != väljapääsud.end()) {
        return it->second;
    }
    return nullptr;
}

void Ruum::lisaEse(Ese* ese) {
    if (ese) {
        esemed.push_back(ese);
    }
}

Ese* Ruum::võtaEse(const std::string& esemeNimi) {
    auto it = std::find_if(esemed.begin(), esemed.end(),
                           [&esemeNimi](const Ese* ese) {
                               return ese && ese->getNimi() == esemeNimi;
                           });
    if (it != esemed.end()) {
        Ese* leitudEse = *it;
        esemed.erase(it);
        return leitudEse;
    }
    return nullptr;
}

bool Ruum::kasSisaldabEset(const std::string& esemeNimi) const {
     auto it = std::find_if(esemed.begin(), esemed.end(),
                           [&esemeNimi](const Ese* ese) {
                               return ese && ese->getNimi() == esemeNimi;
                           });
    return it != esemed.end();
}