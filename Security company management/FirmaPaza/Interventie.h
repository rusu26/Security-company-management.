#pragma once

#include "Persoana.h"

struct Data {
    int zi, luna, an;
};

// contine informatii referitoare la o interventie
class Interventie
{
private:
    Data data; // data la care a avut loc interventia
    Persoana* agent; // agentul deplasat la fata locului
    float timpMediuKm; // timpul mediu de deplasare (folosit la calcularea timpului de reactie)
public:
    // constructor
    Interventie(Data, Persoana*, float);

    // destructor
    ~Interventie();

    // getters - obtine valorile atributelor private
    Data getData();
    Persoana* getAgent();
    float getTimpMediuKM();

    // setters - seteaza valorile atributelor private
    void setData(Data);
    void setAgent(Persoana*);
    void setTimpMediuKM(float);

    // metodele clasei
    void afisare();
};

// lista alocata dinamic cu interventii
struct IntervList {
    Interventie* interv;
    IntervList* urm;
};