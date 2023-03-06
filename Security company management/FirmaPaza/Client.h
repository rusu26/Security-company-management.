#pragma once

#include <fstream>

#include "Interventie.h"
#include "Persoana.h"
#include "Societate.h"

using namespace std;

struct Functie {
    // pointerul ramane null daca este persoana fizica
    Societate* societate;
    char denumire[32] = "Persoana fizica";
};

// clasa client: persoana fizica sau administrator societate comerciala
class Client {
private:
    Persoana* persoana;
    char tipContract[32];
    int cod;
    float distantaKm;
    Functie functie;
    // stiva (alocata dinamic) cu toate interventiile la acest client
    IntervList* istoricInterventii = NULL;
public:
    Client(Persoana*, char*, int, float);
    ~Client();

    // getters - obtine valorile atributelor private
    Persoana* getPersoana();
    char* getTipContract();
    int getCod();
    float getDistanta();
    Functie getFunctie();
    IntervList* getIstoricInterventii();

    // setters - seteaza valorile atributelor private
    void setPersoana(Persoana*);
    void setTipContract(char*);
    void setCod(int);
    void setDistanta(float);
    void setFunctie(Functie);

    // alte metode ale clasei
    void afisare();
    void adaugaInterventie(Interventie*);
};

// lista alocata dinamic ce contine clienti
struct ClientList {
    Client* client;
    ClientList* urm;
};

// parcurge lista cu clienti
void parcurgereClienti(ClientList*);

// adauga un client in lista
void adaugareClient(ClientList*&, Client*);

// diferite chei de sortare
// sortare in functie de numele clientului
bool cmpNumeClient(Client*, Client*);
// sortare in functie de adresa clientului
bool cmpAdresaClient(Client*, Client*);
//sortare in functie de denumirea societatii comerciale
bool cmpDenumireSocietate(Client*, Client*);

//punctul 2 - sortarea listei cu clienti
ClientList* sortare(ClientList* cap, bool (*cheieSortare)(Client*, Client*));

//punctul 4 - cautarea unui client dintr-un anumit cartier
ClientList* cautareClientiCartier(ClientList*, char*);

//punctul 6 - simularea timpilor de reactie
// la fiecare interventie la un client
// returneaza timpul mediu de reactie
float simulareClient(Client*);

//punctul 7 - simularea timpilor de reactie la toti clientii
// returneaza timpul mediu de reactie
float simulareTotiClientii(ClientList*);

// incarca clientii din fisier
Client* citireClientFisier(ifstream&);

// citesti de la tastatura un client nou
Client* citireClientTastatura();

// salveaza clientii din memorie in fisier
void salvareClienti(ClientList*, ofstream&);