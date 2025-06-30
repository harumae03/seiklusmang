# Seiklusmäng
Magnus Traks, Hannes Arumäe

Meie C++ projektiks saab olema lihtne tekstipõhine seiklusmäng, kuna see võimaldab meil rakendada loogilist mõtlemist ning probleemilahendusoskusi. Programm ehitatakse üles objekt-orienteeritult, kus mängumaailma erinevad asukohad (ruumid) ja nendes leiduvad objektid (esemed) on esindatud C++ klassidena, võimaldades neil omada unikaalseid omadusi ja käitumist; mängu peamine loogika keerleb ümber peamise tsükli, mis võtab vastu kasutaja tekstipõhiseid käsklusi (nt "mine põhja", "võta võti"), analüüsib neid ja uuendab vastavalt mängu seisundit, kuvades seejärel mängijale uut informatsiooni või tagasisidet; projekti arendamiseks kasutame C++ programmeerimiskeelt koos standardse teegiga (STL) erinevate andmestruktuuride (nt ruumide ja esemete haldamiseks) ja sisend-väljund operatsioonide jaoks, ning koodi kirjutamiseks ja kompileerimiseks plaanime kasutada CLionit.



1. Samm: Süžee ja Mehaanika Väljamõtlemine
Süžee Idee: "Kadunud Kellassepa Pärandus"
Taust: Mängija kehastub nooreks õpipoisiks, kes saabub oma vana ja ekstsentrilise kellassepast meistri töökotta pärast tema ootamatut kadumist. Meister oli tuntud mitte ainult kellade, vaid ka keerukate mehaaniliste mõistatuste ja automaatide loomise poolest. Kuulduste kohaselt peitis ta oma kõige väärtuslikuma loomingu – ajaga manipuleeriva kronomeetri – kuskile oma mitmetasandilisse, mõistatusi täis töökotta.
Eesmärk: Mängija peab uurima meistri töökoda, lahendama mehaanilisi mõistatusi, leidma vihjeid ja tööriistu ning lõpuks leidma üles kadunud kronomeetri. Võib-olla selgub mängu käigus ka midagi meistri kadumise kohta?
Keskkond: Kellassepa töökoda – täis tiksuvaid kelli, vedrusid, hammasrattaid, pooleliolevaid leiutisi, lukustatud kappe ja salakäike. Võib-olla on seal ka kummalisi, meistri loodud automaat-abilisi või -valvureid.
Põnevus: Mõistatused põhinevad loogikal, mehaanikal ja aja teemadel. Mängija peab võib-olla kombineerima esemeid, leidma õigeid hammasrattaid masinate käivitamiseks või isegi dešifreerima kellade abil jäetud sõnumeid.
Huvitav Mehaanika:
Keerukad Esemed: Esemed ei ole lihtsalt "võtmed". Need võivad olla hammasrattad, vedrud, spetsiifilised tööriistad (kruvikeeraja, luup, õlikann).
Kombineerimine: Mõned mõistatused võivad nõuda esemete kombineerimist inventaris (nt kombineeri käepide katkise kangiga). (Seda saame lisada hilisemas faasis, alustame lihtsamalt).
Masinatega Interaktsioon: Mängija saab uurida (uuri masinat), kasutada esemeid masinate peal (kasuta õli roostes kangil) või neid aktiveerida (käivita kellamehhanism).
Vihjed Keskkonnas: Kirjeldused on olulised. Seinal olevad märkmed, raamatud riiulil või isegi kellade seisud võivad anda vihjeid mõistatuste lahendamiseks.
(Vabatahtlik hilisemaks) Ajaelement: Kuna teema on kellad ja aeg, võiks hiljem lisada lihtsa ajaelemendi. Näiteks mõni sündmus toimub ainult kindlal "kellaajal" (mängusisene aeg, mis edeneb käskude arvuga) või mõni masin töötab vaid piiratud aja. Alustuseks jätame selle välja, et mitte liiga keeruliseks minna.
2. Samm: Põhistruktuuri ja Klasside Disain
Nagu kirjelduses mainitud, kasutame OOP-d. Peamised klassid võiksid olla:
Ese (Item):
Omadused: nimi (string), kirjeldus (string), kasutatav_koos (string, nt mille peal eset saab kasutada - võib olla tühi).
Meetodid: Konstruktor, getNimi(), getKirjeldus().
Ruum (Location/Room):
Omadused: nimi (string), kirjeldus (string), väljapääsud (map<string, Ruum*> - nt {"põhi", pointer_ruumile_põhjas}), esemed (vector<Ese*>).
Meetodid: Konstruktor, getNimi(), getKirjeldus(), lisaVäljapääs(suund, ruum), võtaEse(nimi), lisaEse(ese), getVäljapääs(suund), kuvaKirjeldus().
Mängija (Player):
Omadused: asukoht (Ruum*), inventar (vector<Ese*>).
Meetodid: Konstruktor, liigu(suund), võtaEse(nimi), paneEse(nimi), kuvaInventar(), getAsub()
Mäng (Game):
Omadused: mängija (Mängija), kõikRuumid (map<string, Ruum> - hoiab kõiki ruume), mängKäib (bool).
Meetodid: alusta(), töötleKäsk(käsk), looMaailm(), kuvaAbi(), mänguLoop().
