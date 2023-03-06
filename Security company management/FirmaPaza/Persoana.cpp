#include <iostream>
#include <string.h>

#include "Persoana.h"

using namespace std;

// constructor
Persoana::Persoana(char* numeIntrodus, char* prenumeIntrodus) {
    strcpy_s(nume, numeIntrodus);
    strcpy_s(prenume, prenumeIntrodus);
}

// destructor
Persoana::~Persoana() {
    delete ci;
}

// obtine numele
char* Persoana::getNume() {
    return nume;
}

// obtine prenumele
char* Persoana::getPrenume() {
    return prenume;
}

// obtine numarul de telefon
char* Persoana::getNumarTelefon() {
    return numarTelefon;
}

// obtine cartea de indentitate a persoanei
CarteIdentitate* Persoana::getCI() {
    return ci;
}

// seteaza numele persoanei
void Persoana::setNume(char* numeIntrodus) {
    strcpy_s(nume, numeIntrodus);
}

// seteaza prenumele persoanei
void Persoana::setPrenume(char* prenumeIntrodus) {
    strcpy_s(prenume, prenumeIntrodus);
}

// seteaza numarul de telefon
void Persoana::setNumarTelefon(char* numarTelefonIntr) {
    strcpy_s(numarTelefon, numarTelefonIntr);
}

// seteaza cartea de identitate
void Persoana::setCI(CarteIdentitate* ciIntrodus) {
    ci = ciIntrodus;
}