#pragma once

// contine informatii referitoare la adresa
// unui client, fie a unei societati comerciale
class Adresa
{
private:
    char cartier[32];
    char strada[32];
    int numar;
public:
    Adresa(char*, char*, int);

    // getters - obtin valorile atributelor private
    char* getCartier();
    char* getStrada();
    int getNumar();

    // setters - seteaza valorile atributelor private
    void setCartier(char*);
    void setStrada(char*);
    void setNumar(int);

    // metodele clasei
    void afisare();
};
