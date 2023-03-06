#include <iostream>
#include <string.h>

#include "CarteIdentitate.h"

using namespace std;


// constructor
CarteIdentitate::CarteIdentitate(int numarIntr, char* serieIntr, Adresa* adresaIntr)
{
    numar = numarIntr;
    strcpy_s(serie, serieIntr);
    adresa = adresaIntr;
}

// destructor
CarteIdentitate::~CarteIdentitate() {
    delete adresa;
}

// obtine numarul ci
int CarteIdentitate::getNumar() {
    return numar;
}

// obtine seria ci
char* CarteIdentitate::getSerie() {
    return serie;
}

// obtine adresa ci
Adresa* CarteIdentitate::getAdresa() {
    return adresa;
}

// seteaza numarul ci
void CarteIdentitate::setNumar(int numarIntrodus) {
    numar = numarIntrodus;
}

// seteaza seria ci
void CarteIdentitate::setSerie(char* serieIntrodusa) {
    strcpy_s(serie, serieIntrodusa);
}

// seteaza adresa ci
void CarteIdentitate::setAdresa(Adresa* adresaIntrodusa) {
    adresa = adresaIntrodusa;
}

// afiseaza cartea de identitate
void CarteIdentitate::afisare() {
    cout << "seria " << getSerie() << ", numar " << getNumar() << ", domiciliat in ";
    getAdresa()->afisare();
}