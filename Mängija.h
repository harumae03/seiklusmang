#ifndef KELLASSEPP_MÄNGIJA_H
#define KELLASSEPP_MÄNGIJA_H

#include <vector>
#include <string>
#include "Ese.h"
#include "Ruum.h"

class Mängija {
public:
    Mängija(Ruum* alguskoht);

    void liigu(const std::string& suund);
    bool võtaEse(const std::string& esemeNimi);
    bool paneEse(const std::string& esemeNimi);
    void kuvaInventar() const;
    bool kasOmabEset(const std::string& esemeNimi) const;
    Ese* getEse(const std::string& esemeNimi);
    bool eemaldaEseInventarist(const std::string& esemeNimi); //Eemaldab eseme inventarist (nt kui see ära kasutatakse)

    Ruum* getAsub() const;

private:
    Ruum* asukoht;
    std::vector<Ese*> inventar;
};

#endif //KELLASSEPP_MÄNGIJA_H