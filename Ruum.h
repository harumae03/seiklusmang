#ifndef KELLASSEPP_RUUM_H
#define KELLASSEPP_RUUM_H

#include <string>
#include <vector>
#include <map>
#include "Ese.h"

class Ruum {
public:
    Ruum(std::string n, std::string k);
    std::string getNimi() const;
    std::string getKirjeldus() const;
    void kuvaKirjeldusTäis() const;
    void setKirjeldus(std::string k);

    void lisaVäljapääs(const std::string& suund, Ruum* sihtkoht);
    Ruum* getVäljapääs(const std::string& suund) const;

    void lisaEse(Ese* ese);
    Ese* võtaEse(const std::string& esemeNimi);
    bool kasSisaldabEset(const std::string& esemeNimi) const;

private:
    std::string nimi;
    std::string kirjeldus;
    std::map<std::string, Ruum*> väljapääsud;
    std::vector<Ese*> esemed;
};

#endif //KELLASSEPP_RUUM_H