#include <iostream>
#include "Interventie.h"

using namespace std;

// constructor
Interventie::Interventie(Data dataIntr, Persoana* agentIntr, float timpIntr)
{
    data = dataIntr;
    agent = agentIntr;
    timpMediuKm = timpIntr;
}

// destructor
Interventie::~Interventie() {
    delete agent;
}


// obtine obiectul de data a unei interventii
Data Interventie::getData() {
    return data;
}

// obtine agentul deplasat la interventie
Persoana* Interventie::getAgent() {
    return agent;
}

// obtine timpul mediu / KM de deplasare al agentului catre client
float Interventie::getTimpMediuKM() {
    return timpMediuKm;
}

// seteaza data calendaristica a interventiei
void Interventie::setData(Data dataIntrodusa) {
    data = dataIntrodusa;
}

// seteaza agentul deplasat la interventie
void Interventie::setAgent(Persoana* agentIntrodus) {
    agent = agentIntrodus;
}

// seteaza timpul mediu de deplasare
void Interventie::setTimpMediuKM(float timpIntrodus) {
    timpMediuKm = timpIntrodus;
}

// afiseaza o interventie
void Interventie::afisare() {
    cout << "\tData: " << data.zi << "." << data.luna << "." << data.an << endl;
    cout << "\tAgent deplasat: " << agent->getNume() << " " << agent->getPrenume() << endl;
    cout << "\tTimp mediu / KM: " << timpMediuKm << endl;
}