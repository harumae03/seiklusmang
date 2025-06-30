#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <limits>
#include <cstdlib>
#include <ctime>

#include "Mäng.h"

//Konstruktor
Mäng::Mäng() : mängija(nullptr), mängKäib(false), valitudSeiklus(SeikluseTüüp::POLE_VALITUD),
               // Klassikalise seikluse lipud
               laduKappAvatud(false), töökodaVanaisaKellParandatud(false), kontorLaudSahtelAvatud(false),
               medaljonLauakellas(false), kontorLauakellSeadistatud(false), salakäikAvatud(false),
               vanaisaKellVajabVäikeHammasratas(true), vanaisaKellVajabKeskmineHammasratas(true),
               kronomeeterLeitudSalakambrist(false),
               // Programmeerimise mõistatuse lipud
               raamatukoguUksAvatud(false),
               raamatukoguPraeguneOlek(RaamatukoguOlek::ALUSTAMATA),
               plaatPesaA(""), plaatPesaB(""), plaatPesaC(""), plaatPesaD(""),
               praeguneTerminaliKysimusIndeks(-1), praeguneKonsooliKysimusIndeks(-1)
{
    srand(time(0));

    saadaolevadKlotsidJarjestuseks = {
        "dekl_arr", "for_loop", "if_check", "assign_min", "cout_arr", "while_loop"
    };

    terminaliKysimused.push_back({
        "Mis on 'polümorfism' objektorienteeritud programmeerimises?",
        {"1. Võime objektil esineda mitmel kujul.", "2. Andmete peitmine klassi sees.", "3. Klassi omaduste pärimine teise klassi poolt.", "4. Funktsiooni ülekoormamine."}, 0, ""});
    terminaliKysimused.push_back({
        "Mida tähendab 'int* ptr;' C++ koodis?",
        {"1. Deklareerib täisarvu muutuja nimega ptr.", "2. Deklareerib viida täisarvule nimega ptr.", "3. Deklareerib kursori (pointeri) täisarvule nimega ptr.", "4. Deklareerib täisarvude massiivi nimega ptr."}, 2, ""});
    terminaliKysimused.push_back({
        "Milline neist EI OLE C++ primaarne andmetüüp?",
        {"1. int", "2. float", "3. string", "4. bool"}, 2, ""});
    terminaliKysimused.push_back({
        "Mida teeb 'continue' käsk C++ tsüklis?",
        {"1. Lõpetab tsükli koheselt.", "2. Jätab vahele tsükli praeguse iteratsiooni ja liigub järgmisele.", "3. Peatab programmi täitmise.", "4. Prindib sõna 'continue'."}, 1, ""});
    terminaliKysimused.push_back({
        "Kuidas C++-s kommenteeritakse ühte koodirida?",
        {"1. /* Kommentaar */", "2. // Kommentaar", "3. # Kommentaar", "4. <!-- Kommentaar -->"}, 1, ""});

    konsooliKysimused.push_back({
        "Programm:\nint main() {\n  int x = 5;\n  int y = 10;\n  x = y;\n  y = x + 2;\n  std::cout << y;\n  return 0;\n}\nMis on selle programmi väljund?", {}, -1, "12"});
    konsooliKysimused.push_back({
        "Programm:\nint main() {\n  for (int i = 0; i < 3; ++i) {\n    std::cout << i;\n  }\n  return 0;\n}\nMis on selle programmi väljund?", {}, -1, "012"});
    konsooliKysimused.push_back({
        "Programm:\nint main() {\n  std::string txt = \"Tere\";\n  txt += \" Maailm!\";\n  std::cout << txt.length();\n  return 0;\n}\nMis on selle programmi väljund? (NB! Tähemärkide arv)", {}, -1, "12"});
    konsooliKysimused.push_back({
        "Programm:\nint main() {\n  int a = 10;\n  if (a > 5) {\n    a = a / 2;\n  }\n  if (a <= 5) {\n    a = a * 3;\n  }\n  std::cout << a;\n  return 0;\n}\nMis on programmi väljund?", {}, -1, "15"});
    konsooliKysimused.push_back({
        "Programm:\nvoid muuda(int &val) {\n  val = val + 5;\n}\nint main(){\n  int num = 7;\n  muuda(num);\n  std::cout << num;\n  return 0;\n}\nMis on programmi väljund?", {}, -1, "12"});
}

Mäng::~Mäng() {
    puhastaMälu();
}

void Mäng::puhastaMälu() {
    delete mängija;
    mängija = nullptr;
    for (Ese* ese : kõikEsemed) { if(ese) delete ese; }
    kõikEsemed.clear();
    for (auto const& [key, val] : kõikRuumid) { if(val) delete val; }
    kõikRuumid.clear();
}

Ese* Mäng::findEseGlobal(const std::string& nimi) const {
    for (Ese* ese : kõikEsemed) {
        if (ese && ese->getNimi() == nimi) return ese;
    }
    return nullptr;
}

void Mäng::looMaailm() {
    Ese* globaalne_olikann = new Ese("õlikann", "Väike õlikann peaaegu täis peent masinaõli.");
    kõikEsemed.push_back(globaalne_olikann);
    Ese* globaalne_kiri = new Ese("kiri", "Kortsus pärgamenditükk.");
    kõikEsemed.push_back(globaalne_kiri);

    Ruum* töökoda = new Ruum("Meistri Töökoda", "Ruum on täis pooleliolevaid kellamehhanisme ja tööriistu. Tolm katab enamikke pindu.");
    kõikRuumid["töökoda"] = töökoda;
    Ruum* kontor = new Ruum("Väike Kontor", "Seinad on kaetud riiulitega. Laual on tindiplekke.");
    kõikRuumid["kontor"] = kontor;

    if (töökoda && kontor) {
        töökoda->lisaVäljapääs("ida", kontor);
        kontor->lisaVäljapääs("lääs", töökoda);
    }


    if (valitudSeiklus == SeikluseTüüp::KLASSIKALINE_SEIKLUS) {
        if(globaalne_kiri) globaalne_kiri->setKirjeldus("Sellel on rida sümboleid ja all kiri: 'A=X, B=Y, C=Z... Peegelpildis ja tagurpidi lugedes peitub tõde.' Vihje päeviku jaoks?");
        if(töökoda) töökoda->setKirjeldus(töökoda->getKirjeldus() + " Keset ruumi seisab imposantne vanaisakell, mille seierid on peatunud ja mehhanismist paistab midagi puudu olevat. Põhja pool on uks lattu.");
        if(kontor) kontor->setKirjeldus(kontor->getKirjeldus() + " Laual on lahtine raamat ja elegantne lauakell. Üks kirjutuslaua sahtel on lukus.");

        Ese* võti = new Ese("võti", "Väike roostes messingvõti.");
        kõikEsemed.push_back(võti);
        Ese* hammasratas_ese = new Ese("hammasratas", "Keskmise suurusega pronksist hammasratas, millel on paar hammast puudu.");
        kõikEsemed.push_back(hammasratas_ese);
        Ese* väike_hammasratas_obj = new Ese("väikehammasratas", "Väike, peenelt valmistatud terasest hammasratas.");
        kõikEsemed.push_back(väike_hammasratas_obj);
        Ese* medaljon_obj = new Ese("medaljon", "Raske pronksist medaljon spiraalse mustriga.");
        kõikEsemed.push_back(medaljon_obj);
        Ese* päevik_obj = new Ese("päevik", "Vana nahkköites päevik šifreeritud sissekannetega.");
        kõikEsemed.push_back(päevik_obj);
        Ese* kronomeeter_obj = new Ese("kronomeeter", "Meistri legendaarne ajakronomeeter!");
        kõikEsemed.push_back(kronomeeter_obj);

        Ruum* ladu = new Ruum("Tolmune Ladu", "Siin hoitakse vanu kellakorpuseid ja metallijääke. Nurgas seisab suur, roostes metallkapp. Lõuna pool on uks tagasi töökotta.");
        kõikRuumid["ladu"] = ladu;
        Ruum* salakamber = new Ruum("Salakamber", "Väike, hämar ruum. Keskel postamendil on koht millegi väärtusliku jaoks.");
        kõikRuumid["salakamber"] = salakamber;

        if(töökoda && hammasratas_ese) töökoda->lisaEse(hammasratas_ese);
        if(ladu && võti) ladu->lisaEse(võti);
        if(kontor && globaalne_olikann) kontor->lisaEse(globaalne_olikann);
        if(kontor && globaalne_kiri) kontor->lisaEse(globaalne_kiri);

        if(töökoda && ladu) töökoda->lisaVäljapääs("põhi", ladu);
        if(ladu && töökoda) ladu->lisaVäljapääs("lõuna", töökoda);

    } else if (valitudSeiklus == SeikluseTüüp::PROGRAMMEERIMISE_MÕISTATUS) {
        raamatukoguPraeguneOlek = RaamatukoguOlek::ALUSTAMATA;

        if(globaalne_kiri) globaalne_kiri->setKirjeldus("Sellel on kritseldatud: 'Raamatukogu võti peitub kontori vaikuses, kus õli kohtub ajaga.'");
        if(kontor && globaalne_kiri) kontor->lisaEse(globaalne_kiri);
        if(kontor && globaalne_olikann) kontor->lisaEse(globaalne_olikann);

        Ese* kontorikell_ese = new Ese("kontorikell", "Väike lauakell kontoris, tundub veidi kinni kiilunud.");
        kõikEsemed.push_back(kontorikell_ese);
        if(kontor) kontor->lisaEse(kontorikell_ese);

        Ese* raamatukoguvoti_ese = new Ese("raamatukoguvõti", "Väike ehitud võti, millel on raamatu sümbol.");
        kõikEsemed.push_back(raamatukoguvoti_ese);

        if(töökoda) töökoda->setKirjeldus(töökoda->getKirjeldus() + " Põhja pool on tugev tammepuust uks, mis tundub olevat lukus.");

        Ruum* raamatukogu = new Ruum("Meistri Raamatukogu", "See ruum on vaikne ja tolmune, seinad on maast laeni kaetud raskete tammepuust riiulitega. Riiulid on täis raamatuid mehaanikast, ajaloost, filosoofiast ja programmeerimisõpikuid. Ühel suurel laual keset ruumi on kolm seadet: 'loogikaplokkide masin', 'definitsioonide terminal' ja 'koodianalüüsi konsool'. Lõuna pool on uks tagasi töökotta.");
        kõikRuumid["raamatukogu"] = raamatukogu;

        Ese* progkivi_ese = new Ese("programmeerimiskivi", "Sile, tume kivi, mille ühele küljele on graveeritud sümbol 'int main()'.");
        kõikEsemed.push_back(progkivi_ese);
        if(töökoda) töökoda->lisaEse(progkivi_ese);

        Ese* auhind_ese = new Ese("loogikaskeem", "Keerukas loogikaskeem, mis kirjeldab ajamasina tööpõhimõtet. See on lahendus!");
        kõikEsemed.push_back(auhind_ese);
    }

    if (töökoda) { // Kontrollime, et töökoda on loodud
        mängija = new Mängija(töökoda);
    } else {
        std::cerr << "Kriitiline viga: Töökoja ruumi ei suudetud luua!" << std::endl;
        mängKäib = false; // Väldi edasist tööd, kui algusruum puudub
        return;
    }

    if (!mängija || !mängija->getAsub()) {
        std::cerr << "Kriitiline viga: Mängija või algusruumi loomine ebaõnnestus!" << std::endl;
        mängKäib = false; // Seadista see lipp siin, et vältida alusta() jätkamist
    }
}

void Mäng::kuvaSissejuhatus() const {
    std::cout << "\n--- Kellassepa Saladused ---" << std::endl;
    if (valitudSeiklus == SeikluseTüüp::KLASSIKALINE_SEIKLUS) {
        std::cout << "Saabud oma vana meistri, tuntud kellassepa, töökotta." << std::endl;
        std::cout << "Ta on ootamatult kadunud, jättes maha vaid segaduse." << std::endl;
        std::cout << "Kuulduste kohaselt peitis ta siia oma suurima loomingu - ajakronomeetri." << std::endl;
        std::cout << "Sinu ülesanne on leida see legendaarne seade." << std::endl;
    } else if (valitudSeiklus == SeikluseTüüp::PROGRAMMEERIMISE_MÕISTATUS) {
        std::cout << "Oled noor õpipoiss kellassepa töökojas. Meister on sulle jätnud väljakutse:" << std::endl;
        std::cout << "lahendada tema loodud loogikamõistatus, mis peitub tema salajases raamatukogus." << std::endl;
        std::cout << "Edukas lahendus paljastab ühe tema suurima leiutise saladuse." << std::endl;
    }
    std::cout << "------------------------------------\n" << std::endl;
    std::cout << "Sisesta 'abi', et näha käske." << std::endl;
}

void Mäng::kuvaAbi() const {
    std::cout << "\n--- Käsud ---" << std::endl;
    std::cout << "  liigu [suund]  - Liigu antud suunas (nt. põhi, lõuna, ida, lääs, salakäik, raamatukogusse)" << std::endl;
    std::cout << "  vaata          - Kirjelda uuesti praegust ruumi" << std::endl;
    std::cout << "  uuri [objekt]  - Uuri eset, ruumi osa (nt. 'uuri kapp', 'uuri plaat', 'uuri terminal', 'uuri konsool')" << std::endl;
    std::cout << "  võta [ese]     - Võta ese ruumist üles" << std::endl;
    std::cout << "  pane [ese]     - Pane ese inventarist maha" << std::endl;
    std::cout << "  inventar       - Näita oma inventari" << std::endl;
    std::cout << "  kasuta [ese] [objekt] - Kasuta eset millegi peal (nt 'kasuta õlikann kapp')" << std::endl;
    if (valitudSeiklus == SeikluseTüüp::KLASSIKALINE_SEIKLUS) {
        std::cout << "  seadista [objekt] [väärtus] - (nt 'seadista lauakell 3:00')" << std::endl;
    }
    if (valitudSeiklus == SeikluseTüüp::PROGRAMMEERIMISE_MÕISTATUS) {
        std::cout << "  paiguta [pesa_id] [klots_id] - Paiguta klots pessa (nt. 'paiguta a dekl_arr')" << std::endl;
        std::cout << "                            Pesad: a, b, c, d" << std::endl;
        std::cout << "                            Klotsid: uuri plaati, et näha ID-sid." << std::endl;
        std::cout << "  käivita masin - Proovi loogikaplokkide masinat käivitada" << std::endl;
        std::cout << "  aktiveeri terminal - Alusta definitsioonide küsimusega" << std::endl;
        std::cout << "  vasta terminal [number] - Vasta terminali küsimusele (nt. 'vasta terminal 1')" << std::endl;
        std::cout << "  aktiveeri konsool - Alusta koodianalüüsi küsimusega" << std::endl;
        std::cout << "  vasta konsool [sinu_tekst_väljund] - Vasta konsooli küsimusele (nt. 'vasta konsool 012')" << std::endl;
    }
    std::cout << "  abi            - Näita seda abiteksti" << std::endl;
    std::cout << "  välju          - Lahku mängust" << std::endl;
    std::cout << "---------------\n" << std::endl;
}

void Mäng::parseKäsk(const std::string& input, std::string& command, std::string& argument) {
    std::istringstream iss(input);
    command.clear();
    argument.clear();
    if (iss >> command) {
        std::getline(iss >> std::ws, argument);
    }
}

void Mäng::töötleKäsk(const std::string& input_orig) {
    if (!mängija || !mängija->getAsub()) {
        std::cerr << "Viga töötleKäsk: Mängija või asukoht puudub!" << std::endl;
        mängKäib = false; return;
    }

    std::string command_str, argument_str;
    parseKäsk(input_orig, command_str, argument_str);

    std::string command_lower = command_str;
    std::transform(command_lower.begin(), command_lower.end(), command_lower.begin(), ::tolower);

    Ruum* praeguneRuum = mängija->getAsub();

    if (command_lower == "välju" || command_lower == "lahku") {
        std::cout << "Aitäh mängimast!" << std::endl;
        mängKäib = false;
    } else if (command_lower == "abi") { kuvaAbi(); }
    else if (command_lower == "vaata" || command_lower == "v") { praeguneRuum->kuvaKirjeldusTäis(); }
    else if (command_lower == "inventar" || command_lower == "i") { mängija->kuvaInventar(); }
    else if (command_lower == "liigu" || command_lower == "mine") {
        if (argument_str.empty()) { std::cout << "Kuhu suunas sa liikuda tahad?" << std::endl; }
        else { mängija->liigu(argument_str); }
    } else if (command_lower == "võta") {
        if (argument_str.empty()) { std::cout << "Mida sa võtta tahad?" << std::endl; }
        else { mängija->võtaEse(argument_str); }
    } else if (command_lower == "pane") {
        if (argument_str.empty()) { std::cout << "Mida sa maha panna tahad?" << std::endl; }
        else { mängija->paneEse(argument_str); }
    } else if (command_lower == "uuri") {
        if (argument_str.empty()) { praeguneRuum->kuvaKirjeldusTäis(); }
        else {
            std::string arg_lower = argument_str;
            std::transform(arg_lower.begin(), arg_lower.end(), arg_lower.begin(), ::tolower);
            bool leitud = false;
            Ese* eseInventaris = mängija->getEse(arg_lower);
            if (eseInventaris) {
                std::cout << eseInventaris->getNimi() << ": " << eseInventaris->getKirjeldus() << std::endl;
                leitud = true;
                if (valitudSeiklus == SeikluseTüüp::KLASSIKALINE_SEIKLUS && eseInventaris->getNimi() == "päevik") {
                    if (mängija->kasOmabEset("kiri")) {
                        std::cout << "Uurides päevikut koos kirjaga, dešifreerid: 'Kontori lauakell tuleb seada ajale 3:00. Kummaline medaljon on võtmeks sihverplaadile.'" << std::endl;
                    } else {
                        std::cout << "Päevik on šifreeritud. Sul on vaja vihjet selle dešifreerimiseks." << std::endl;
                    }
                }
            }

            if (!leitud && valitudSeiklus == SeikluseTüüp::KLASSIKALINE_SEIKLUS) {
                if (praeguneRuum->getNimi() == "Tolmune Ladu" && (arg_lower == "kapp" || arg_lower == "metallkapp")) {
                    if (laduKappAvatud) { std::cout << "Avatud metallkapp on tühi." << std::endl; }
                    else { std::cout << "Suur, roostes hingedega metallkapp. See on kinni kiilunud." << std::endl;}
                    leitud = true;
                } else if (praeguneRuum->getNimi() == "Meistri Töökoda" && (arg_lower == "vanaisakell" || arg_lower == "kell")) {
                    if (töökodaVanaisaKellParandatud) { std::cout << "Vanaisakell tiksub rahulikult. Selle laegas on tühi." << std::endl; }
                    else { std::cout << "Imposantne vanaisakell. Mehhanismist paistab midagi puudu olevat." << std::endl; }
                    leitud = true;
                } else if (praeguneRuum->getNimi() == "Väike Kontor" && (arg_lower == "laud" || arg_lower == "sahtel")) {
                    if (kontorLaudSahtelAvatud) { std::cout << "Kirjutuslaua sahtel on avatud ja tühi." << std::endl; }
                    else { std::cout << "Kirjutuslaud. Üks selle sahtlitest on lukus." << std::endl; }
                    leitud = true;
                } else if (praeguneRuum->getNimi() == "Väike Kontor" && arg_lower == "lauakell") {
                    if (salakäikAvatud) { std::cout << "Elegantne lauakell. Selle kõrval on avanenud salakäik." << std::endl; }
                    else if (medaljonLauakellas) { std::cout << "Elegantne lauakell, millel on medaljon. Saad seda seadistada." << std::endl; }
                    else { std::cout << "Elegantne lauakell. Selle sihverplaadil on kummaline sälk." << std::endl; }
                    leitud = true;
                }
            }
            if (!leitud && valitudSeiklus == SeikluseTüüp::PROGRAMMEERIMISE_MÕISTATUS) {
                if (praeguneRuum->getNimi() == "Meistri Raamatukogu") {
                    if (arg_lower == "plaat" || arg_lower == "masin") {
                        leitud = true;
                        std::cout << "See on loogikaplokkide masin." << std::endl;
                        if (raamatukoguPraeguneOlek == RaamatukoguOlek::PLAAT_OOTAB_KIVI) {
                            std::cout << "Plaadil on neli vagu ja neli sisselõiget (A, B, C, D). Klotsid on jäigad. Plaadi serval on sälk 'programmeerimiskivi' jaoks." << std::endl;
                        } else if (raamatukoguPraeguneOlek >= RaamatukoguOlek::PLAAT_AKTIVEERITUD && raamatukoguPraeguneOlek < RaamatukoguOlek::JARJESTUS_LAHENDATUD) {
                            std::cout << "Plaat on aktiveeritud. Ülesanne: järjestada read, et leida massiivist miinimum element." << std::endl;
                            std::cout << "Pesad: A(" << (plaatPesaA.empty()?"tühi":plaatPesaA) << "), B(" << (plaatPesaB.empty()?"tühi":plaatPesaB)
                                      << "), C(" << (plaatPesaC.empty()?"tühi":plaatPesaC) << "), D(" << (plaatPesaD.empty()?"tühi":plaatPesaD) << ")." << std::endl;
                            std::cout << "Saadaolevad klotsi ID-d (kasuta 'paiguta [pesa_id] [klots_id]'):" << std::endl;
                            std::cout << "  if_check     - (if(arr[i] < min_val))" << std::endl;
                            std::cout << "  assign_min   - (min_val = arr[i];)" << std::endl;
                            std::cout << "  dekl_arr     - (int arr[]={8,3,9,2,5}; int min_val=arr[0];)" << std::endl;
                            std::cout << "  while_loop   - (while(min_val > 0))" << std::endl;
                            std::cout << "  for_loop     - (for(int i=1; i<5; ++i))" << std::endl;
                            std::cout << "  cout_arr     - (std::cout << arr[0];)" << std::endl;
                        } else if (raamatukoguPraeguneOlek >= RaamatukoguOlek::JARJESTUS_LAHENDATUD) {
                            std::cout << "Oled loogikaplokkide ülesande lahendanud." << std::endl;
                        }
                    } else if (arg_lower == "terminal") {
                        leitud = true;
                        std::cout << "See on definitsioonide terminal." << std::endl;
                        if (raamatukoguPraeguneOlek < RaamatukoguOlek::TERMINAL_OOTAB_AKTIVEERIMIST) { std::cout << "Terminal on pime. Lahenda enne eelmine ülesanne." << std::endl; }
                        else if (raamatukoguPraeguneOlek == RaamatukoguOlek::TERMINAL_OOTAB_AKTIVEERIMIST) { std::cout << "Terminali ekraan helendab. Sisesta 'aktiveeri terminal'." << std::endl; }
                        else if (raamatukoguPraeguneOlek == RaamatukoguOlek::TERMINAL_KYSIMUS_ESITATUD) {
                            std::cout << "Terminalis on aktiivne küsimus:" << std::endl;
                            std::cout << terminaliKysimused[praeguneTerminaliKysimusIndeks].kysimus_tekst << std::endl;
                            for(const auto& v : terminaliKysimused[praeguneTerminaliKysimusIndeks].valikud) std::cout << "  " << v << std::endl;
                            std::cout << "Vasta käsuga 'vasta terminal [number]'." << std::endl;
                        } else { std::cout << "Oled terminali ülesande juba lahendanud." << std::endl; }
                    } else if (arg_lower == "konsool") {
                        leitud = true;
                        std::cout << "See on koodianalüüsi konsool." << std::endl;
                        if (raamatukoguPraeguneOlek < RaamatukoguOlek::KONSOOL_OOTAB_AKTIVEERIMIST) { std::cout << "Konsool on pime. Lahenda enne eelmised ülesanded." << std::endl; }
                        else if (raamatukoguPraeguneOlek == RaamatukoguOlek::KONSOOL_OOTAB_AKTIVEERIMIST) { std::cout << "Konsooli ekraan ootab. Sisesta 'aktiveeri konsool'." << std::endl; }
                        else if (raamatukoguPraeguneOlek == RaamatukoguOlek::KONSOOL_KYSIMUS_ESITATUD) {
                            std::cout << "Konsoolis on aktiivne ülesanne:" << std::endl;
                            std::cout << konsooliKysimused[praeguneKonsooliKysimusIndeks].kysimus_tekst << std::endl;
                            std::cout << "Vasta käsuga 'vasta konsool [sinu_tekst_väljund]'." << std::endl;
                        } else { std::cout << "Oled konsooli ülesande juba lahendanud." << std::endl; }
                    }
                } else if (praeguneRuum->getNimi() == "Väike Kontor" && arg_lower == "kontorikell") {
                    std::cout << "Väike lauakell kontoris. See on veidi tolmune ja mehhanism tundub kinni kiilunud." << std::endl;
                    leitud = true;
                }
            }

            if (!leitud) {
                Ese* eseRuumis = findEseGlobal(arg_lower);
                if (eseRuumis && praeguneRuum->kasSisaldabEset(arg_lower)) {
                    std::cout << eseRuumis->getNimi() << ": " << eseRuumis->getKirjeldus() << std::endl;
                    leitud = true;
                }
            }
            if (!leitud) { std::cout << "Sa ei näe siin ega oma kaasas midagi nimega '" << argument_str << "', mida uurida." << std::endl; }
        }
    } else if (command_lower == "kasuta") {
        if (argument_str.empty()) { std::cout << "Mida sa mille peal kasutada tahad?" << std::endl;}
        else {
            std::string itemToUseName, targetName;
            std::istringstream argStream(argument_str);
            argStream >> itemToUseName;
            std::getline(argStream >> std::ws, targetName);

            std::string item_lower = itemToUseName;
            std::transform(item_lower.begin(), item_lower.end(), item_lower.begin(), ::tolower);
            std::string target_lower = targetName;
            std::transform(target_lower.begin(), target_lower.end(), target_lower.begin(), ::tolower);

            if (itemToUseName.empty() || targetName.empty()) { std::cout << "Palun täpsusta: 'kasuta [ese] [objekt]'" << std::endl; }
            else {
                Ese* itemFromInventory = mängija->getEse(item_lower);
                if (!itemFromInventory) { std::cout << "Sul ei ole kaasas eset nimega '" << itemToUseName << "'." << std::endl; }
                else {
                    bool kasutatud = false;
                    if (valitudSeiklus == SeikluseTüüp::KLASSIKALINE_SEIKLUS) {
                        if (praeguneRuum->getNimi() == "Tolmune Ladu" && (target_lower == "kapp" || target_lower == "metallkapp") && item_lower == "õlikann") {
                            if (!laduKappAvatud) {
                                laduKappAvatud = true;
                                std::cout << "Õlitad kapi hinged. See avaneb kriiksuga! Seest leiad väikese hammasratta." << std::endl;
                                Ese* vHammas = findEseGlobal("väikehammasratas");
                                if (vHammas) praeguneRuum->lisaEse(vHammas);
                            } else { std::cout << "Kapp on juba lahti." << std::endl; }
                            kasutatud = true;
                        } else if (praeguneRuum->getNimi() == "Meistri Töökoda" && (target_lower == "vanaisakell" || target_lower == "kell")) {
                            if (töökodaVanaisaKellParandatud) { std::cout << "Vanaisakell töötab juba." << std::endl; }
                            else {
                                bool midagiSobis = false;
                                if (item_lower == "väikehammasratas" && vanaisaKellVajabVäikeHammasratas) {
                                    std::cout << "Paigaldad väikese hammasratta." << std::endl;
                                    mängija->eemaldaEseInventarist(item_lower);
                                    vanaisaKellVajabVäikeHammasratas = false; midagiSobis = true;
                                } else if (item_lower == "hammasratas" && vanaisaKellVajabKeskmineHammasratas) {
                                    std::cout << "Paigaldad keskmise hammasratta." << std::endl;
                                    mängija->eemaldaEseInventarist(item_lower);
                                    vanaisaKellVajabKeskmineHammasratas = false; midagiSobis = true;
                                }
                                if (midagiSobis && !vanaisaKellVajabVäikeHammasratas && !vanaisaKellVajabKeskmineHammasratas) {
                                    töökodaVanaisaKellParandatud = true;
                                    std::cout << "Kell hakkab tiksuma! Avanenud laekast leiad medaljoni." << std::endl;
                                    Ese* medaljonEse = findEseGlobal("medaljon");
                                    if (medaljonEse) praeguneRuum->lisaEse(medaljonEse);
                                } else if (midagiSobis) { std::cout << "Kell vajab veel teist hammasratast." << std::endl;}
                                else { std::cout << "See ese ei sobi vanaisakella." << std::endl; }
                            }
                            kasutatud = true;
                        } else if (praeguneRuum->getNimi() == "Väike Kontor" && (target_lower == "laud" || target_lower == "sahtel") && item_lower == "võti") {
                            if (!kontorLaudSahtelAvatud) {
                                kontorLaudSahtelAvatud = true;
                                std::cout << "Võti keerab lukus ja sahtel avaneb. Sealt leiad päeviku." << std::endl;
                                Ese* paevikEse = findEseGlobal("päevik");
                                if (paevikEse) praeguneRuum->lisaEse(paevikEse);
                            } else { std::cout << "Sahtel on juba lahti." << std::endl; }
                            kasutatud = true;
                        } else if (praeguneRuum->getNimi() == "Väike Kontor" && target_lower == "lauakell" && item_lower == "medaljon") {
                            if (salakäikAvatud) { std::cout << "Salakäik on juba avatud." << std::endl; }
                            else if (!medaljonLauakellas) {
                                medaljonLauakellas = true;
                                std::cout << "Medaljon sobib lauakella! Nüüd saad seda seadistada." << std::endl;
                                mängija->eemaldaEseInventarist(item_lower);
                            } else { std::cout << "Medaljon on juba lauakellas." << std::endl; }
                            kasutatud = true;
                        }
                    }
                    if (valitudSeiklus == SeikluseTüüp::PROGRAMMEERIMISE_MÕISTATUS) {
                        if (praeguneRuum->getNimi() == "Meistri Raamatukogu" && (target_lower == "plaat" || target_lower == "masin") && item_lower == "programmeerimiskivi") {
                            if (raamatukoguPraeguneOlek == RaamatukoguOlek::PLAAT_OOTAB_KIVI) {
                                raamatukoguPraeguneOlek = RaamatukoguOlek::PLAAT_AKTIVEERITUD;
                                std::cout << "Sa asetad programmeerimiskivi plaadi sisselõikesse. Klotsid on nüüd liigutatavad! Uuri plaati." << std::endl;
                                mängija->eemaldaEseInventarist(item_lower);
                            } else if (raamatukoguPraeguneOlek > RaamatukoguOlek::PLAAT_OOTAB_KIVI) { std::cout << "Plaat on juba aktiveeritud." << std::endl; }
                            else { std::cout << "Midagi on valesti, sa ei tohiks seda veel teha." << std::endl; }
                            kasutatud = true;
                        } else if (praeguneRuum->getNimi() == "Meistri Töökoda" && target_lower == "uks" && item_lower == "raamatukoguvõti") {
                            if (!raamatukoguUksAvatud) {
                                raamatukoguUksAvatud = true;
                                raamatukoguPraeguneOlek = RaamatukoguOlek::PLAAT_OOTAB_KIVI;
                                std::cout << "Võti keerab lukus ja uks raamatukokku avaneb." << std::endl;
                                Ruum* raamatukoguRef = kõikRuumid["raamatukogu"]; // Otse mapist
                                if (raamatukoguRef) {
                                    praeguneRuum->lisaVäljapääs("raamatukogusse", raamatukoguRef);
                                    raamatukoguRef->lisaVäljapääs("töökotta", praeguneRuum);
                                }
                                mängija->eemaldaEseInventarist(item_lower);
                            } else { std::cout << "Uks raamatukokku on juba lahti." << std::endl; }
                            kasutatud = true;
                        } else if (praeguneRuum->getNimi() == "Väike Kontor" && target_lower == "kontorikell" && item_lower == "õlikann") {
                             if (!praeguneRuum->kasSisaldabEset("raamatukoguvõti") && !mängija->kasOmabEset("raamatukoguvõti")) {
                                std::cout << "Sa õlitad kontorikella. Väike sahtel avaneb ja sealt leiad raamatukoguvõtme!" << std::endl;
                                Ese* rk_voti = findEseGlobal("raamatukoguvõti");
                                if (rk_voti) praeguneRuum->lisaEse(rk_voti);
                            } else { std::cout << "Oled kontorikella juba õlitanud või võtme kätte saanud." << std::endl; }
                            kasutatud = true;
                        }
                    }
                    if (!kasutatud) { std::cout << "Sa ei saa eset '" << itemToUseName << "' niimoodi '" << targetName << "' peal kasutada." << std::endl; }
                }
            }
        }
    }
    else if (valitudSeiklus == SeikluseTüüp::KLASSIKALINE_SEIKLUS && command_lower == "seadista") {
        if (argument_str.empty()) { std::cout << "Mida sa seadistada tahad ja mis väärtusele?" << std::endl; }
        else {
            std::string targetObjectName, value;
            std::istringstream argStream(argument_str);
            argStream >> targetObjectName;
            std::getline(argStream >> std::ws, value);
            std::string target_lower = targetObjectName;
            std::transform(target_lower.begin(), target_lower.end(), target_lower.begin(), ::tolower);

            if (praeguneRuum->getNimi() == "Väike Kontor" && target_lower == "lauakell") {
                if (salakäikAvatud) { std::cout << "Salakäik on juba avatud." << std::endl; }
                else if (medaljonLauakellas) {
                    if (value == "3:00") {
                        salakäikAvatud = true; kontorLauakellSeadistatud = true;
                        std::cout << "Seadsid kella 3:00. Klõpsatus! Sein nihkub, paljastades salakäigu!" << std::endl;
                        Ruum* salakamberRef = kõikRuumid["salakamber"];
                        if (salakamberRef) {
                            praeguneRuum->lisaVäljapääs("salakäik", salakamberRef);
                            salakamberRef->lisaVäljapääs("kontorisse", praeguneRuum);
                        }
                    } else { std::cout << "Seadistasid kella, aga midagi ei juhtu." << std::endl; }
                } else { std::cout << "Lauakella ei saa seadistada. Medaljon puudub?" << std::endl; }
            } else { std::cout << "Sa ei saa objekti '" << targetObjectName << "' seadistada." << std::endl; }
        }
    }
    else if (valitudSeiklus == SeikluseTüüp::PROGRAMMEERIMISE_MÕISTATUS) {
        if (command_lower == "paiguta") {
            if (praeguneRuum->getNimi() == "Meistri Raamatukogu" && raamatukoguPraeguneOlek >= RaamatukoguOlek::PLAAT_AKTIVEERITUD && raamatukoguPraeguneOlek < RaamatukoguOlek::JARJESTUS_LAHENDATUD) {
                std::string pesa_id_str, klots_id_str;
                std::istringstream argStream(argument_str);
                argStream >> pesa_id_str >> klots_id_str;
                std::transform(pesa_id_str.begin(), pesa_id_str.end(), pesa_id_str.begin(), ::tolower);
                std::transform(klots_id_str.begin(), klots_id_str.end(), klots_id_str.begin(), ::tolower);

                if (pesa_id_str.empty() || klots_id_str.empty()) { std::cout << "Sisesta: paiguta [pesa_id] [klots_id]" << std::endl; }
                else {
                    bool validKlots = std::find(saadaolevadKlotsidJarjestuseks.begin(), saadaolevadKlotsidJarjestuseks.end(), klots_id_str) != saadaolevadKlotsidJarjestuseks.end();
                    if (!validKlots) { std::cout << "Klotsi ID '" << klots_id_str << "' ei ole valiidne." << std::endl; }
                    else {
                        bool pesaLeitud = false;
                        if (pesa_id_str == "a") { plaatPesaA = klots_id_str; pesaLeitud = true; }
                        else if (pesa_id_str == "b") { plaatPesaB = klots_id_str; pesaLeitud = true; }
                        else if (pesa_id_str == "c") { plaatPesaC = klots_id_str; pesaLeitud = true; }
                        else if (pesa_id_str == "d") { plaatPesaD = klots_id_str; pesaLeitud = true; }

                        if(pesaLeitud) {
                            std::cout << "Paigutasid klotsi '" << klots_id_str << "' pessa " << (char)toupper(pesa_id_str[0]) << "." << std::endl;
                            if (raamatukoguPraeguneOlek == RaamatukoguOlek::PLAAT_AKTIVEERITUD) {
                                raamatukoguPraeguneOlek = RaamatukoguOlek::JARJESTUS_ALUSTATUD;
                            }
                        } else { std::cout << "Tundmatu pesa '" << pesa_id_str << "'. Kasuta a, b, c, d." << std::endl; }
                    }
                }
            } else { std::cout << "Sa ei saa praegu klotse paigutada." << std::endl; }
        } else if (command_lower == "käivita" && argument_str == "masin") {
             if (praeguneRuum->getNimi() == "Meistri Raamatukogu" && raamatukoguPraeguneOlek == RaamatukoguOlek::JARJESTUS_ALUSTATUD) {
                if (plaatPesaA == "dekl_arr" && plaatPesaB == "for_loop" && plaatPesaC == "if_check" && plaatPesaD == "assign_min") {
                    std::cout << "Õige järjestus! Loogikaplokkide masin sähvatab roheliselt." << std::endl;
                    raamatukoguPraeguneOlek = RaamatukoguOlek::TERMINAL_OOTAB_AKTIVEERIMIST;
                    std::cout << "Definitsioonide terminal lülitus sisse. Sisesta 'aktiveeri terminal'." << std::endl;
                } else {
                    std::cout << "Vale järjestus. Masin ei käivitu." << std::endl;
                }
            } else { std::cout << "Sa ei saa masinat praegu käivitada või oled selle juba lahendanud." << std::endl; }
        } else if (command_lower == "aktiveeri") {
            std::string midaAktiveerida = argument_str;
            std::transform(midaAktiveerida.begin(), midaAktiveerida.end(), midaAktiveerida.begin(), ::tolower);
            if (praeguneRuum->getNimi() == "Meistri Raamatukogu") {
                if (midaAktiveerida == "terminal") {
                    if (raamatukoguPraeguneOlek == RaamatukoguOlek::TERMINAL_OOTAB_AKTIVEERIMIST) {
                        if (!terminaliKysimused.empty()) {
                            praeguneTerminaliKysimusIndeks = rand() % terminaliKysimused.size();
                            std::cout << "Terminal aktiveerus. Küsimus:" << std::endl;
                            std::cout << terminaliKysimused[praeguneTerminaliKysimusIndeks].kysimus_tekst << std::endl;
                            for(const auto& v : terminaliKysimused[praeguneTerminaliKysimusIndeks].valikud) std::cout << "  " << v << std::endl;
                            std::cout << "Vasta käsuga 'vasta terminal [number]'." << std::endl;
                            raamatukoguPraeguneOlek = RaamatukoguOlek::TERMINAL_KYSIMUS_ESITATUD;
                        } else {std::cout << "Viga: Terminali küsimused puuduvad." <<std::endl;}
                    } else if (raamatukoguPraeguneOlek >= RaamatukoguOlek::TERMINAL_LAHENDATUD) { std::cout << "Oled terminali ülesande juba lahendanud." << std::endl; }
                    else { std::cout << "Sa ei saa terminali veel aktiveerida." << std::endl; }
                } else if (midaAktiveerida == "konsool") {
                    if (raamatukoguPraeguneOlek == RaamatukoguOlek::KONSOOL_OOTAB_AKTIVEERIMIST) {
                         if (!konsooliKysimused.empty()) {
                            praeguneKonsooliKysimusIndeks = rand() % konsooliKysimused.size();
                            std::cout << "Koodianalüüsi konsool aktiveerus. Ülesanne:" << std::endl;
                            std::cout << konsooliKysimused[praeguneKonsooliKysimusIndeks].kysimus_tekst << std::endl;
                            std::cout << "Vasta käsuga 'vasta konsool [sinu_tekst_väljund]'." << std::endl;
                            raamatukoguPraeguneOlek = RaamatukoguOlek::KONSOOL_KYSIMUS_ESITATUD;
                        } else {std::cout << "Viga: Konsooli küsimused puuduvad." <<std::endl;}
                    } else if (raamatukoguPraeguneOlek >= RaamatukoguOlek::KONSOOL_LAHENDATUD) { std::cout << "Oled konsooli ülesande juba lahendanud." << std::endl; }
                    else { std::cout << "Sa ei saa konsooli veel aktiveerida." << std::endl; }
                } else { std::cout << "Ei saa aru, mida soovid aktiveerida ('" << argument_str << "')." << std::endl; }
            } else { std::cout << "Siin pole midagi sellist, mida aktiveerida." << std::endl;}
        } else if (command_lower == "vasta") {
            std::istringstream argStream(argument_str);
            std::string sihtmärk, vastusTekst;
            argStream >> sihtmärk;
            std::getline(argStream >> std::ws, vastusTekst);
            std::transform(sihtmärk.begin(), sihtmärk.end(), sihtmärk.begin(), ::tolower);

            if (praeguneRuum->getNimi() == "Meistri Raamatukogu") {
                if (sihtmärk == "terminal") {
                    if (raamatukoguPraeguneOlek == RaamatukoguOlek::TERMINAL_KYSIMUS_ESITATUD) {
                        try {
                            int vastuseNr = std::stoi(vastusTekst);
                            if (vastuseNr > 0 && praeguneTerminaliKysimusIndeks != -1 && vastuseNr <= terminaliKysimused[praeguneTerminaliKysimusIndeks].valikud.size()) {
                                if ((vastuseNr - 1) == terminaliKysimused[praeguneTerminaliKysimusIndeks].oigeVastusIndeks) {
                                    std::cout << "Õige vastus!" << std::endl;
                                    raamatukoguPraeguneOlek = RaamatukoguOlek::KONSOOL_OOTAB_AKTIVEERIMIST;
                                    std::cout << "Koodianalüüsi konsool lülitus sisse. Sisesta 'aktiveeri konsool'." << std::endl;
                                } else { std::cout << "Vale vastus. Proovi uuesti." << std::endl; }
                            } else { std::cout << "Palun sisesta valiidne number." << std::endl; }
                        } catch (const std::exception& e) { std::cout << "Palun sisesta number vastusena." << std::endl; }
                    } else { std::cout << "Terminalile pole küsimust esitatud." << std::endl; }
                } else if (sihtmärk == "konsool") {
                     if (raamatukoguPraeguneOlek == RaamatukoguOlek::KONSOOL_KYSIMUS_ESITATUD && praeguneKonsooliKysimusIndeks != -1) {
                        if (vastusTekst == konsooliKysimused[praeguneKonsooliKysimusIndeks].oigeVastusString) {
                            std::cout << "Fantastiline! Õige väljund!" << std::endl;
                            raamatukoguPraeguneOlek = RaamatukoguOlek::KÕIK_LAHENDATUD;
                            std::cout << "Kõik Raamatukogu mõistatused on lahendatud! Üks riiul nihkub ja paljastab loogikaskeemi." << std::endl;
                            Ese* auhind = findEseGlobal("loogikaskeem");
                            if (auhind) praeguneRuum->lisaEse(auhind);
                        } else {
                            std::cout << "See ei ole õige väljund. Proovi uuesti sama koodiga." << std::endl;
                        }
                    } else { std::cout << "Konsoolile pole ülesannet esitatud." << std::endl; }
                } else { std::cout << "Ei saa aru, millele soovid vastata ('" << sihtmärk << "')." << std::endl;}
            } else { std::cout << "Sa ei saa siin millelegi vastata." << std::endl; }
        } else {
             std::cout << "Ma ei saa aru, mida sa teha tahad ('" << input_orig << "'). Proovi 'abi'." << std::endl;
        }
    } else {
        bool oliSpetsiifilineKaskTeisestSeiklusest = false;
        if (valitudSeiklus != SeikluseTüüp::KLASSIKALINE_SEIKLUS && command_lower == "seadista") oliSpetsiifilineKaskTeisestSeiklusest = true;
        if (valitudSeiklus != SeikluseTüüp::PROGRAMMEERIMISE_MÕISTATUS &&
            (command_lower == "paiguta" || command_lower == "käivita" || command_lower == "aktiveeri" || command_lower == "vasta")) {
            oliSpetsiifilineKaskTeisestSeiklusest = true;
        }

        if(oliSpetsiifilineKaskTeisestSeiklusest) {
            std::cout << "See käsklus ei ole praeguses seikluses asjakohane." << std::endl;
        } else {
            std::cout << "Ma ei saa aru, mida sa teha tahad ('" << input_orig << "'). Proovi 'abi'." << std::endl;
        }
    }
}

void Mäng::mänguLoop() {
    std::string rida;
    while (mängKäib) {
        if (!mängija || !mängija->getAsub()) {
            std::cerr << "KRIITILINE VIGA mänguLoopis: Mängija või asukoht muutus kehtetuks!" << std::endl;
            mängKäib = false; break;
        }
        std::cout << "\n> ";
        if (!std::getline(std::cin, rida)) {
            if (std::cin.eof()) { std::cout << "\nOotamatu sisendi lõpp. Aitäh mängimast!" << std::endl; }
            else { std::cerr << "\nViga sisendi lugemisel." << std::endl; }
            mängKäib = false; break;
        }
        if (rida.empty()) { continue; }
        töötleKäsk(rida);
        if (mängija) {
            if (valitudSeiklus == SeikluseTüüp::KLASSIKALINE_SEIKLUS && mängija->kasOmabEset("kronomeeter")) {
                std::cout << "\n****************************************************************" << std::endl;
                std::cout << "!!!          PALJU ÕNNE, SA LEIDSID KRONOMEETRI!         !!!" << std::endl;
                std::cout << "Meistri suurim looming on sinu käes. Tema pärand elab edasi." << std::endl;
                std::cout << "****************************************************************" << std::endl;
                mängKäib = false;
            } else if (valitudSeiklus == SeikluseTüüp::PROGRAMMEERIMISE_MÕISTATUS && mängija->kasOmabEset("loogikaskeem")) {
                std::cout << "\n********************************************************************" << std::endl;
                std::cout << "!!! PALJU ÕNNE, SA LAHENDASID MEISTRI MÕISTATUSE JA LEIDSID LOOGIKASKEEMI! !!!" << std::endl;
                std::cout << "Sinu loogikaoskus ja C++ teadmised on end tõestanud!" << std::endl;
                std::cout << "********************************************************************" << std::endl;
                mängKäib = false;
            }
        }
    }
}

void Mäng::alusta() {
    std::cout << "\nTere tulemast Kellassepa Saladuste maailma!" << std::endl;
    std::cout << "Vali seiklus:" << std::endl;
    std::cout << "1. Klassikaline Seiklus (Leia kadunud kronomeeter)" << std::endl;
    std::cout << "2. Programmeerimise Mõistatus (Lahenda meistri loogikaülesanne)" << std::endl;

    int valik = 0;
    while (true) {
        std::cout << "Sisesta number (1 või 2): ";
        if (!(std::cin >> valik)) {
            std::cout << "Vigane sisend (mitte number). Proovi uuesti." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (valik == 1 || valik == 2) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        } else {
            std::cout << "Vigane valikunumber. Palun sisesta 1 või 2." << std::endl;
        }
    }

    if (valik == 1) { valitudSeiklus = SeikluseTüüp::KLASSIKALINE_SEIKLUS; }
    else { valitudSeiklus = SeikluseTüüp::PROGRAMMEERIMISE_MÕISTATUS; }

    try {
        looMaailm();
        if (!mängKäib && (!mängija || !mängija->getAsub())) { // Kontroll, kas looMaailm seadis mängKäib falseks
             std::cerr << "Mängu alustamine ebaõnnestus: Maailma loomine ebaõnnestus või mängija pole korrektselt seatud." << std::endl;
             puhastaMälu(); return;
        }
        kuvaSissejuhatus();
        if(mängija && mängija->getAsub()) mängija->getAsub()->kuvaKirjeldusTäis();
        else { // See ei tohiks juhtuda, kui eelnev kontroll on tehtud
            std::cerr << "Kriitiline viga: Mängija või tema asukoht puudub pärast sissejuhatust." << std::endl;
            mängKäib = false; puhastaMälu(); return;
        }
        mängKäib = true; // Veendu, et see on true, kui kõik on korras
        mänguLoop();
    } catch (const std::bad_alloc& e) {
        std::cerr << "Kriitiline viga: Mälu eraldamine ebaõnnestus! (" << e.what() << ")" << std::endl;
        mängKäib = false; puhastaMälu();
    } catch (const std::exception& e) {
        std::cerr << "Tekkis ootamatu viga alusta()-s: " << e.what() << std::endl;
        mängKäib = false; puhastaMälu();
    } catch (...) {
        std::cerr << "Tekkis tundmatu kriitiline viga alusta()-s!" << std::endl;
        mängKäib = false; puhastaMälu();
    }
}