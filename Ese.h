#ifndef KELLASSEPP_ESE_H
#define KELLASSEPP_ESE_H

#include <string>

class Ese {
public:
    Ese(std::string n, std::string k);
    std::string getNimi() const;
    std::string getKirjeldus() const;
    void setKirjeldus(std::string k);

private:
    std::string nimi;
    std::string kirjeldus;
};

#endif //KELLASSEPP_ESE_H