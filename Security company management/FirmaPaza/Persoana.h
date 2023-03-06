#pragma once

#include "CarteIdentitate.h"

// contine informatii specifice unei persoane
class Persoana
{
private:
    char nume[32];
    char prenume[32];
    char numarTelefon[16] = "";
    CarteIdentitate* ci = NULL;
public:
    // constructor
    Persoana(char*, char*);

    //destructor
    ~Persoana();

    // getters - obtine valorile atributelor private
    char* getNume();
    char* getPrenume();
    char* getNumarTelefon();
    CarteIdentitate* getCI();

    // setters - seteaza valorile atributelor private
    void setNume(char*);
    void setPrenume(char*);
    void setNumarTelefon(char*);
    void setCI(CarteIdentitate*);

    // alte metode ale clasei
    void editare();
};

// lista alocata dinamic cu persoane
struct PersList {
    Persoana* pers;
    PersList* urm;
};

