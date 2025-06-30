#include "Mängija.h"
#include <iostream> // Vajalik inventari kuvamiseks ja teadete jaoks
#include <algorithm> // Vajalik std::find_if jaoks inventari otsimisel

// Konstruktor: seab mängija algasukoha
Mängija::Mängija(Ruum* alguskoht) : asukoht(alguskoht) {
    if (asukoht == nullptr) {
        std::cerr << "Viga: Mangija loodi ilma kehtiva alguskohata!" << "\n";
    }
}

// Liigutab mängija uude ruumi antud suunas
void Mängija::liigu(const std::string& suund) {
    if (asukoht == nullptr) return;

    Ruum* järgmineRuum = asukoht->getVäljapääs(suund);
    if (järgmineRuum != nullptr) {
        asukoht = järgmineRuum;
        std::cout << "Liikusid suunas " << suund << "." << "\n";
        asukoht->kuvaKirjeldusTäis();
    } else {
        std::cout << "Selles suunas (" << suund << ") ei saa liikuda." << "\n";
    }
}

bool Mängija::võtaEse(const std::string& esemeNimi) {
    if (asukoht == nullptr) return false;

    Ese* ese = asukoht->võtaEse(esemeNimi);

    if (ese != nullptr) {
        inventar.push_back(ese);
        std::cout << "Votsid eseme: " << esemeNimi << "." << "\n";
        return true;
    } else {
        // Ruumis polnud sellist eset
        std::cout << "Siin ruumis ei ole eset nimega '" << esemeNimi << "'." << "\n";
        return false;
    }
}

bool Mängija::paneEse(const std::string& esemeNimi) {
    if (asukoht == nullptr) return false;

    auto it = std::find_if(inventar.begin(), inventar.end(),
                           [&esemeNimi](const Ese* ese) {
                               return ese != nullptr && ese->getNimi() == esemeNimi;
                           });

    if (it != inventar.end()) {
        Ese* ese = *it;
        inventar.erase(it);
        asukoht->lisaEse(ese);
        std::cout << "Panid maha eseme: " << esemeNimi << "." << "\n";
        return true;
    } else {
        std::cout << "Sul ei ole kaasas eset nimega '" << esemeNimi << "'." << "\n";
        return false;
    }
}

// Kuvab mängija inventari sisu
void Mängija::kuvaInventar() const {
    std::cout << "--- Inventar ---" << std::endl;
    if (inventar.empty()) {
        std::cout << "Su inventar on tuhi." << "\n";
    } else {
        std::cout << "Sul on kaasas:" << "\n";
        for (const Ese* ese : inventar) {
            if (ese != nullptr) {
                std::cout << "- " << ese->getNimi() << "\n";
            }
        }
    }
     std::cout << "----------------" << "\n";
}

bool Mängija::kasOmabEset(const std::string& esemeNimi) const {
     auto it = std::find_if(inventar.begin(), inventar.end(),
                           [&esemeNimi](const Ese* ese) {
                               return ese != nullptr && ese->getNimi() == esemeNimi;
                           });
    return it != inventar.end();
}

Ese* Mängija::getEse(const std::string& esemeNimi) {
     auto it = std::find_if(inventar.begin(), inventar.end(),
                           [&esemeNimi](const Ese* ese) {
                               return ese != nullptr && ese->getNimi() == esemeNimi;
                           });
    if (it != inventar.end()){
        return *it;
    }
    return nullptr;
}

bool Mängija::eemaldaEseInventarist(const std::string& esemeNimi) {
    auto it = std::find_if(inventar.begin(), inventar.end(),
                           [&esemeNimi](const Ese* ese) {
                               return ese != nullptr && ese->getNimi() == esemeNimi;
                           });
    if (it != inventar.end()) {
        inventar.erase(it); // Eemalda pointer inventarist
        return true;
    }
    return false; // Eset ei leitud inventarist
}

// Tagastab pointeri ruumile, kus mängija asub
Ruum* Mängija::getAsub() const {
    return asukoht;
}