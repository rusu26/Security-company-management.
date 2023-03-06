#include <iostream>
#include <string.h>

#include "Societate.h"
#include "Persoana.h"

using namespace std;

// constructor
Societate::Societate(char* denumireIntrodusa, Adresa* adresaIntrodusa) {
    strcpy_s(denumire, denumireIntrodusa);
    adresa = adresaIntrodusa;
}

// destructor - folosit pentru a sterge stiva
// cu persoanele cu acces la cod, alocata dinamic
Societate::~Societate()
{
    PersList* aux;
    while (persoaneAcces != NULL)
    {
        aux = persoaneAcces->urm;
        delete persoaneAcces;
        persoaneAcces = aux;
    }
    delete adresa;
}

// obtine denumirea societatii
char* Societate::getDenumire() {
    return denumire;
}

// obtine obiectul adresei societatii
Adresa* Societate::getAdresa() {
    return adresa;
}

// obtine lista cu persoanele cu acces
PersList* Societate::getPersAcces() {
    return persoaneAcces;
}

// seteaza denumirea societatii
void Societate::setDenumire(char* denumireIntrodusa) {
    strcpy_s(denumire, denumireIntrodusa);
}

// seteaza adresa societatii
void Societate::setAdresa(Adresa* adresaIntrodusa) {
    adresa = adresaIntrodusa;
}

// adauga o persoana cu acces in lista
void Societate::adaugaPersAcces(Persoana* persNoua) {
    PersList* nou = new PersList;
    nou->pers = persNoua;
    nou->urm = persoaneAcces;
    persoaneAcces = nou;
}

// afiseaza pe ecran o societate
void Societate::afisare() {
    cout << "Denumire societate: " << getDenumire() << endl;
    cout << "Adresa societatii: "; getAdresa()->afisare();
    cout << "Persoane cu acces:" << endl;

    PersList* cap = getPersAcces();
    while (cap != NULL) {
        cout << "\t" << cap->pers->getNume() << " " << cap->pers->getPrenume() << endl;
        cap = cap->urm;
    }
}