#ifndef KELLASSEPP_MÄNG_H
#define KELLASSEPP_MÄNG_H

#include <string>
#include <vector>
#include <map>
#include "Ruum.h"
#include "Ese.h"
#include "Mängija.h"

// Enum mängu tüübi jaoks
enum class SeikluseTüüp {
    POLE_VALITUD,
    KLASSIKALINE_SEIKLUS,
    PROGRAMMEERIMISE_MÕISTATUS
};

// Uued olekud Raamatukogu jaoks programmeerimise seikluses
enum class RaamatukoguOlek {
    ALUSTAMATA,                 // Raamatukogu pole veel avatud või mõistatus pole alanud
    PLAAT_OOTAB_KIVI,           // Raamatukogus, plaat ootab aktiveerimist programmeerimiskiviga
    PLAAT_AKTIVEERITUD,         // Kivi on kasutatud, klotse saab paigutada
    JARJESTUS_ALUSTATUD,        // Mängija on hakanud klotse paigutama
    JARJESTUS_LAHENDATUD,       // Esimene (järjestus) ülesanne lahendatud
    TERMINAL_OOTAB_AKTIVEERIMIST, // Järjestus lahendatud, terminali saab aktiveerida
    TERMINAL_KYSIMUS_ESITATUD,  // Terminalis on küsimus aktiivne
    TERMINAL_LAHENDATUD,        // Teine (terminali) ülesanne lahendatud
    KONSOOL_OOTAB_AKTIVEERIMIST,  // Terminal lahendatud, konsooli saab aktiveerida
    KONSOOL_KYSIMUS_ESITATUD,   // Konsoolis on küsimus aktiivne
    KONSOOL_LAHENDATUD,         // Kolmas (konsooli) ülesanne lahendatud
    KÕIK_LAHENDATUD             // Kõik programmeerimise mõistatused raamatukogus lahendatud
};

struct KysimusVastus {
    std::string kysimus_tekst;      // Küsimuse tekst (või koodinäide)
    std::vector<std::string> valikud; // Valikvastustega küsimuste jaoks
    int oigeVastusIndeks;           // Valikvastustega (0-põhine indeks)
    std::string oigeVastusString;   // Väljundi ennustamise jaoks (stringina)
};

class Mäng {
public:
    Mäng();
    ~Mäng();
    void alusta();

private:
    void looMaailm();
    void mänguLoop();
    void töötleKäsk(const std::string& käsk);
    void kuvaSissejuhatus() const;
    void kuvaAbi() const;
    void puhastaMälu();
    void parseKäsk(const std::string& input, std::string& command, std::string& argument);
    Ese* findEseGlobal(const std::string& nimi) const;

    Mängija* mängija;
    bool mängKäib;
    SeikluseTüüp valitudSeiklus;

    std::map<std::string, Ruum*> kõikRuumid;
    std::vector<Ese*> kõikEsemed;

    // --- Klassikalise seikluse olekulipud ---
    bool laduKappAvatud;
    bool töökodaVanaisaKellParandatud;
    bool kontorLaudSahtelAvatud;
    bool medaljonLauakellas;
    bool kontorLauakellSeadistatud;
    bool salakäikAvatud;
    bool vanaisaKellVajabVäikeHammasratas;
    bool vanaisaKellVajabKeskmineHammasratas;
    bool kronomeeterLeitudSalakambrist;

    // --- Programmeerimise mõistatuse olekulipud/andmed ---
    bool raamatukoguUksAvatud; // Kas uks töökojast raamatukokku on avatud
    RaamatukoguOlek raamatukoguPraeguneOlek;

    // Järjestusülesande jaoks (loogikaplokkide masin)
    std::string plaatPesaA; // Klotsi ID pesa A-s
    std::string plaatPesaB;
    std::string plaatPesaC;
    std::string plaatPesaD;
    std::vector<std::string> saadaolevadKlotsidJarjestuseks; // Klotside ID-d, mida mängija saab kasutada

    // Terminali (valikvastused) jaoks
    std::vector<KysimusVastus> terminaliKysimused;
    int praeguneTerminaliKysimusIndeks; // -1 kui küsimust pole aktiivne

    // Konsooli (väljund) jaoks
    std::vector<KysimusVastus> konsooliKysimused;
    int praeguneKonsooliKysimusIndeks; // -1 kui küsimust pole aktiivne
};

#endif //KELLASSEPP_MÄNG_H