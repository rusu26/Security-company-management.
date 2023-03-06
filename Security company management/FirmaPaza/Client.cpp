#include <iostream>
#include <string.h>

#include "Client.h"

using namespace std;

// constructor
Client::Client(Persoana* persIntr, char* tipCtr, int codIntr, float distIntr)
{
    persoana = persIntr;
    strcpy_s(tipContract, tipCtr);
    cod = codIntr;
    distantaKm = distIntr;
}

// destructor - folosit pentru a sterge stiva (istoric interventii) cu interventiile, alocata dinamic
Client::~Client()
{
    IntervList* aux;
    while (istoricInterventii != NULL)
    {
        aux = istoricInterventii->urm;
        delete istoricInterventii;
        istoricInterventii = aux;
    }
    delete persoana;
}

// obtine informatiile personale ale clientului
Persoana* Client::getPersoana() {
    return persoana;
}

// obtine tipul contractului
char* Client::getTipContract() {
    return tipContract;
}

// obtine codul de armare / dezarmare
int Client::getCod() {
    return cod;
}

// obtine distanta client - sediu paza
float Client::getDistanta() {
    return distantaKm;
}

// obtine functia clientului din cadrul unei societati comerciale
Functie Client::getFunctie() {
    return functie;
}

// obtine istoricul interventiilor la un anumit client
IntervList* Client::getIstoricInterventii() {
    return istoricInterventii;
}

// seteaza informatiile personale
void Client::setPersoana(Persoana* persIntrodusa) {
    persoana = persIntrodusa;
}

// seteaza tipul contractului
void Client::setTipContract(char* tipIntrodus) {
    strcpy_s(tipContract, tipIntrodus);
}

// seteaza codul de armare / dezarmare
void Client::setCod(int codIntrodus) {
    cod = codIntrodus;
}

// seteaza distanta client - sediu paza
void Client::setDistanta(float distantaIntrodusa) {
    distantaKm = distantaIntrodusa;
}

// seteaza functia clientului din cadrul societatii
// pe care o reprezinta
void Client::setFunctie(Functie functieIntrodusa) {
    functie = functieIntrodusa;
}

// adauga o interventie in lista
void Client::adaugaInterventie(Interventie* intervNoua) {
    IntervList* nou = new IntervList;
    nou->interv = intervNoua;
    nou->urm = istoricInterventii;
    istoricInterventii = nou;
}

//punctul 2 - afiseaza informatiile unui client
void Client::afisare() {
    cout << "Nume: " << getPersoana()->getNume() << " " << getPersoana()->getPrenume() << endl;
    cout << "Numar telefon: " << getPersoana()->getNumarTelefon() << endl;
    cout << "Carte identitate: ";  getPersoana()->getCI()->afisare();
    cout << "Tip contract: " << getTipContract() << endl;
    cout << "Distanta: " << getDistanta() << "km" << endl;
    cout << "Functie: " << getFunctie().denumire << endl;
    if (getFunctie().societate != NULL) {
        cout << "*Societatea reprezentata:" << endl;
        getFunctie().societate->afisare();
    }
    cout << "Istoric interventii:" << endl;
    IntervList* cap = getIstoricInterventii();

    int numarInterventii = 0;
    while (cap != NULL) {
        cout << "Interventia #" << ++numarInterventii << endl;
        cap->interv->afisare();
        cap = cap->urm;
    }

    cout << endl << endl;
}

// parcurge lista cu clienti si afiseaza informatii elementare
void parcurgereClienti(ClientList* cap) {
    int numar = 0;
    while (cap != NULL) {
        cout << "Client #" << ++numar << ": ";
        cout << cap->client->getPersoana()->getNume() << " ";
        cout << cap->client->getPersoana()->getPrenume() << endl;
        cout << "\t Adresa: "; cap->client->getPersoana()->getCI()->getAdresa()->afisare();
        cap = cap->urm;
    }
}

// adauga un client in lista
void adaugareClient(ClientList*& cap, Client* client) {
    ClientList* nodNou = new ClientList;
    nodNou->client = client;
    nodNou->urm = cap;
    cap = nodNou;
}

// diferite chei de sortare
// sortare in functie de numele clientului
bool cmpNumeClient(Client* a, Client* b) {
    return strcmp(a->getPersoana()->getNume(), b->getPersoana()->getNume()) > 0
        || strcmp(a->getPersoana()->getPrenume(), b->getPersoana()->getPrenume()) > 0;
}

// sortare in functie de adresa clientului
bool cmpAdresaClient(Client* a, Client* b) {
    Adresa* adresaA = a->getPersoana()->getCI()->getAdresa();
    Adresa* adresaB = b->getPersoana()->getCI()->getAdresa();
    return strcmp(adresaA->getCartier(), adresaB->getCartier()) > 0
        || strcmp(adresaB->getStrada(), adresaB->getStrada()) > 0
        || adresaA->getNumar() > adresaB->getNumar();
}

// sortare in functie de denumirea societatii
bool cmpDenumireSocietate(Client* a, Client* b) {
    Societate* socA = a->getFunctie().societate;
    Societate* socB = b->getFunctie().societate;
    if (socA != NULL && socB != NULL)
        return strcmp(socA->getDenumire(), socB->getDenumire()) > 0;
    else return false;
}

// interschimbarea a doi pointeri Client
// functie folosita la sortare
void interschimbareClienti(Client** a, Client** b) {
    Client* aux = *a;
    *a = *b;
    *b = aux;
}

//punctul 2 - sortare
ClientList* sortare(ClientList* cap, bool (*cheieSortare)(Client*, Client*)) {
    ClientList* aux = cap;
    int n = 0;
    while (cap != NULL) {
        ++n;
        cap = cap->urm;
    }
    while (n--) {
        cap = aux;
        while (cap->urm != NULL) {
            if (cheieSortare(cap->client, cap->urm->client))
                interschimbareClienti(&cap->client, &cap->urm->client);
            cap = cap->urm;
        }
    }

    cap = aux;
    return cap;
}

//punctul 4 - cautarea clientilor dintr-un anumit cartier
ClientList* cautareClientiCartier(ClientList* cap, char* cartier) {
    ClientList* listaNoua = NULL;
    while (cap != NULL) {
        if (strcmp(cap->client->getPersoana()->getCI()->getAdresa()->getCartier(), cartier) == 0) {
            ClientList* nodNou = new ClientList;
            nodNou->client = cap->client;
            nodNou->urm = listaNoua;
            listaNoua = nodNou;
        }
        cap = cap->urm;
    }

    return listaNoua;
}

//punctul 6 - simularea timpilor de reactie ai interventiilor unui client
float simulareClient(Client* client) {
    cout << "Simulare timpi reactie pentru " << client->getPersoana()->getNume() << " " << client->getPersoana()->getPrenume() << endl;
    cout << "Adresa client: "; client->getPersoana()->getCI()->getAdresa()->afisare();
    cout << "Distanta client - sediu paza: " << client->getDistanta() << endl << endl;
    IntervList* cap = client->getIstoricInterventii();

    int numarInterventii = 0;
    float timpTotal = 0;
    while (cap != NULL) {
        cout << "Interventia #" << ++numarInterventii << endl;
        cap->interv->afisare();
        float timpInterventie = client->getDistanta() * cap->interv->getTimpMediuKM();
        cout << "TIMP REACTIE: " << timpInterventie << " MINUTE" << endl << endl;
        timpTotal += timpInterventie;
        cap = cap->urm;
    }
    return timpTotal / numarInterventii;
}

//punctul 7 - simularea timpilor de reactie ai interventiilor tuturor clientilor
float simulareTotiClientii(ClientList* cap) {
    int clienti = 0;
    float timpTotal = 0;
    while (cap != NULL) {
        float timpClient = simulareClient(cap->client);
        if (timpClient > 0) {
            clienti++;
            cout << "TIMP MEDIU REACTIE CLIENT: " << timpClient << " MINUTE" << endl << endl;;
            timpTotal += timpClient;
        }
        cap = cap->urm;
    }
    return timpTotal / clienti;
}

// incarcarea datelor din fisier in memorie
Client* citireClientFisier(ifstream& in) {
    char nume[32], prenume[32], numarTelefon[16], serieCI[3],
        cartier[32], strada[32], tipContract[32],
        denumireFunctie[32], denumireSocietate[128],
        cartierSoc[32], stradaSoc[32];
    int numarCI, numarAdresa, cod, areSoc,
        arePersAcces, numarAdresaSoc, areInterventii;
    float distanta;

    in.get();
    in.getline(nume, 32);
    in.getline(prenume, 32);
    in.getline(numarTelefon, 16);

    in >> numarCI >> serieCI;
    in.get();
    in.getline(cartier, 32);
    in.getline(strada, 32);
    in >> numarAdresa;
    in.get();
    in.getline(tipContract, 32);
    in >> cod >> distanta;
    Persoana* pers = new Persoana(nume, prenume);
    pers->setNumarTelefon(numarTelefon);

    Adresa* adresa = new Adresa(cartier, strada, numarAdresa);
    CarteIdentitate* ci = new CarteIdentitate(numarCI, serieCI, adresa);

    pers->setCI(ci);

    in >> areSoc;
    in.get();

    Client* client = new Client(pers, tipContract, cod, distanta);

    if (areSoc) {
        in.getline(denumireFunctie, 32);
        in.getline(denumireSocietate, 128);
        in.getline(cartierSoc, 32);
        in.getline(stradaSoc, 32);
        in >> numarAdresaSoc;
        in.get();
        Adresa* adresaSoc = new Adresa(cartierSoc, stradaSoc, numarAdresaSoc);
        Societate* societate = new Societate(denumireSocietate, adresaSoc);

        do {
            in >> arePersAcces;
            in.get();
            if (arePersAcces) {
                char numePers[32], prenumePers[32];
                in.getline(numePers, 32);
                in.getline(prenumePers, 32);
                societate->adaugaPersAcces(new Persoana(numePers, prenumePers));
            }
        } while (arePersAcces);

        Functie functie;
        strcpy_s(functie.denumire, denumireFunctie);
        functie.societate = societate;
        client->setFunctie(functie);

    }

    do {
        in >> areInterventii;
        in.get();
        if (areInterventii) {
            int zi, luna, an;
            float timpMediuKM;
            in >> zi >> luna >> an;
            in.get();
            char numeAgent[32], prenumeAgent[32];
            in.getline(numeAgent, 32);
            in.getline(prenumeAgent, 32);
            in >> timpMediuKM;
            in.get();
            Data data; data.zi = zi, data.luna = luna, data.an = an;
            client->adaugaInterventie(new Interventie(data, new Persoana(numeAgent, prenumeAgent), timpMediuKM));
        }
    } while (areInterventii);

    return client;
}

// adaugarea unui nou client de la tastatura
Client* citireClientTastatura() {
    char nume[32], prenume[32], numarTelefon[16], serieCI[3],
        localitate[32], strada[32], tipContract[32],
        denumireFunctie[32], denumireSocietate[128],
        localitateSoc[32], stradaSoc[32];
    int numarCI, numarAdresa, cod, areSoc,
        arePersAcces, numarAdresaSoc, areInterventii;
    float distanta;

    cin.get();
    cout << "Nume client: "; cin.getline(nume, 32);
    cout << "Prenume client: ";  cin.getline(prenume, 32);
    cout << "Numar telefon: ";  cin.getline(numarTelefon, 16);

    cout << "Numar CI: "; cin >> numarCI;
    cout << "Serie CI: "; cin >> serieCI;
    cin.get();

    cout << "Localitate: "; cin.getline(localitate, 32);
    cout << "Strada: "; cin.getline(strada, 32);
    cout << "Numar: "; cin >> numarAdresa;
    cin.get();

    cout << "Tip contract: ";  cin.getline(tipContract, 32);
    cout << "Cod armare/dezarmare: ";  cin >> cod;
    cout << "Distanta client - sediu paza: "; cin >> distanta;
    Persoana* pers = new Persoana(nume, prenume);
    pers->setNumarTelefon(numarTelefon);

    Adresa* adresa = new Adresa(localitate, strada, numarAdresa);
    CarteIdentitate* ci = new CarteIdentitate(numarCI, serieCI, adresa);

    pers->setCI(ci);

    cout << "Clientul este reprezentantul unei socitati comerciale?" << endl;
    cout << "0 - nu" << endl << "1 - da" << endl; cin >> areSoc;
    cin.get();

    Client* client = new Client(pers, tipContract, cod, distanta);

    if (areSoc) {
        cout << "Functia clientului in societate: "; cin.getline(denumireFunctie, 32);
        cout << "Denumirea societatii: "; cin.getline(denumireSocietate, 128);
        cout << "Localitate societate: "; cin.getline(localitateSoc, 32);
        cout << "Strada societate: "; cin.getline(stradaSoc, 32);
        cout << "Numar adresa societate:"; cin >> numarAdresaSoc;
        cin.get();
        Adresa* adresaSoc = new Adresa(localitateSoc, stradaSoc, numarAdresaSoc);
        Societate* societate = new Societate(denumireSocietate, adresaSoc);

        do {
            cout << "Introduceti persoana cu acces?" << endl;
            cout << "0 - nu" << endl << "1 - da" << endl; cin >> arePersAcces;
            cin.get();
            if (arePersAcces) {
                char numePers[32], prenumePers[32];
                cout << "Introduceti numele persoanei: "; cin.getline(numePers, 32);
                cout << "Introduceti prenumele persoanei: "; cin.getline(prenumePers, 32);
                societate->adaugaPersAcces(new Persoana(numePers, prenumePers));
            }
        } while (arePersAcces);

        Functie functie;
        strcpy_s(functie.denumire, denumireFunctie);
        functie.societate = societate;
        client->setFunctie(functie);

    }

    do {
        cout << "Introduceti interventii?" << endl;
        cout << "0 - nu" << endl << "1 - da" << endl; cin >> areInterventii;
        cin.get();
        if (areInterventii) {
            int zi, luna, an;
            float timpMediuKM;
            cout << "Data interventie" << endl;
            cout << "Zi: "; cin >> zi;
            cout << "Luna: "; cin >> luna;
            cout << "An:"; cin >> an;
            cin.get();
            char numeAgent[32], prenumeAgent[32];
            cout << "Numele agentului: "; cin.getline(numeAgent, 32);
            cout << "Prenumele agentului: "; cin.getline(prenumeAgent, 32);
            cout << "Timpul mediu / KM: "; cin >> timpMediuKM;
            cin.get();
            Data data; data.zi = zi, data.luna = luna, data.an = an;
            client->adaugaInterventie(new Interventie(data, new Persoana(numeAgent, prenumeAgent), timpMediuKM));
        }
    } while (areInterventii);

    cout << "Datele clientului introdus:" << endl;
    client->afisare();
    return client;
}

// salvarea clientilor din memorie in fisier
void salvareClienti(ClientList* cap, ofstream& out) {
    while (cap != NULL) {
        out << 1 << endl;
        out << cap->client->getPersoana()->getNume() << endl;
        out << cap->client->getPersoana()->getPrenume() << endl;
        out << cap->client->getPersoana()->getNumarTelefon() << endl;
        out << cap->client->getPersoana()->getCI()->getNumar() << endl;
        out << cap->client->getPersoana()->getCI()->getSerie() << endl;
        out << cap->client->getPersoana()->getCI()->getAdresa()->getCartier() << endl;
        out << cap->client->getPersoana()->getCI()->getAdresa()->getStrada() << endl;
        out << cap->client->getPersoana()->getCI()->getAdresa()->getNumar() << endl;
        out << cap->client->getTipContract() << endl;
        out << cap->client->getCod() << endl;
        out << cap->client->getDistanta() << endl;
        if (cap->client->getFunctie().societate != NULL) {
            out << 1 << endl;
            out << cap->client->getFunctie().denumire << endl;
            out << cap->client->getFunctie().societate->getDenumire() << endl;
            out << cap->client->getFunctie().societate->getAdresa()->getCartier() << endl;
            out << cap->client->getFunctie().societate->getAdresa()->getStrada() << endl;
            out << cap->client->getFunctie().societate->getAdresa()->getNumar() << endl;
            PersList* persAcces = cap->client->getFunctie().societate->getPersAcces();
            while (persAcces != NULL) {
                out << 1 << endl;
                out << persAcces->pers->getNume() << endl;
                out << persAcces->pers->getPrenume() << endl;
                persAcces = persAcces->urm;
            }
            out << 0 << endl;
        }
        else out << 0 << endl;
        IntervList* interventii = cap->client->getIstoricInterventii();
        while (interventii != NULL) {
            out << 1 << endl;
            out << interventii->interv->getData().zi << endl;
            out << interventii->interv->getData().luna << endl;
            out << interventii->interv->getData().an << endl;
            out << interventii->interv->getAgent()->getNume() << endl;
            out << interventii->interv->getAgent()->getPrenume() << endl;
            out << interventii->interv->getTimpMediuKM() << endl;
            interventii = interventii->urm;
        }
        out << 0 << endl;
        cap = cap->urm;
    }
    out << 0;
}