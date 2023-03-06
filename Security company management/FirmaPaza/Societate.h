#pragma once

#include "Persoana.h"

// clasa societate - cand un client are un contract
// pentru o societate comerciala (nu persoana fizica)
class Societate
{
private:
    char denumire[128];
    Adresa* adresa;
    // stiva alocata dinamic ce contine
    // persoanele cu acces la codul de armare / dezarmare
    PersList* persoaneAcces = NULL;
public:
    // constructor
    Societate(char*, Adresa*);

    //destructor
    ~Societate();

    // getters
    char* getDenumire();
    Adresa* getAdresa();
    PersList* getPersAcces();

    // setters
    void setDenumire(char*);
    void setAdresa(Adresa*);

    // metodele clasei
    void afisare(); // afiseaza societatea
    void adaugaPersAcces(Persoana*); // adauga persoana acces in lista
};