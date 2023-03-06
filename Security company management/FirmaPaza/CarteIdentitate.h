#pragma once

#include "Adresa.h"

// contine informatii ce pot fi regasite
// in cartea de identitate a unei persoane
class CarteIdentitate
{
private:
    int numar;
    char serie[3];
    Adresa* adresa;
public:
    // constructor
    CarteIdentitate(int, char*, Adresa*);
    // destructor
    ~CarteIdentitate();

    // getters - obtin valorile atributelor private
    int getNumar();
    char* getSerie();
    Adresa* getAdresa();

    // setters - seteaza valorile atributelor private
    void setNumar(int);
    void setSerie(char*);
    void setAdresa(Adresa*);

    // alte metode
    void afisare();
};
