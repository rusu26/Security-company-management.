#include <iostream>
#include <string.h>

#include "Adresa.h"

using namespace std;

// constructor adresa
Adresa::Adresa(char* cartierIntr, char* stradaIntr, int numarIntr) {
    strcpy_s(cartier, cartierIntr);
    strcpy_s(strada, stradaIntr);
    numar = numarIntr;
}

// obtine cartierul adresei
char* Adresa::getCartier() {
    return cartier;
}

// obtine strada adresei
char* Adresa::getStrada() {
    return strada;
}

// obtine numarul adresei
int Adresa::getNumar() {
    return numar;
}

// seteaza denumirea cartierului
void Adresa::setCartier(char* cartierIntr) {
    strcpy_s(cartier, cartierIntr);
}

// seteaza numele strazii
void Adresa::setStrada(char* stradaIntr) {
    strcpy_s(strada, stradaIntr);
}

// seteaza numarul adresei
void Adresa::setNumar(int numarIntr) {
    numar = numarIntr;
}

// afiseaza adresa
void Adresa::afisare() {
    cout << "cartier " << getCartier() << ", strada " << getStrada() << ", nr " << getNumar() << endl;
}