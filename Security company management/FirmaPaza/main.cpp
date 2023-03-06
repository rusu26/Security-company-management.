#include <iostream>
#include <fstream>
#include <string.h>

#include "Societate.h"
#include "Client.h"

using namespace std;



int main() {
    ifstream in("date.txt");
    ClientList* clienti = NULL;

    int existaInfo;

    // incarcare in memorie a valorilor deja salvate
    do {
        in >> existaInfo;
        // verifica daca mai exista clienti in fisier
        if (existaInfo && !in.eof()) adaugareClient(clienti, citireClientFisier(in));
    } while (existaInfo && !in.eof());
    cout << "Datele au fost incarcate din fisier cu succes!" << endl << endl;
    in.close();

    // comenzile de la tastatura
    while (true) {
        cout << endl;
        cout << "Introduceti o comanda:" << endl;
        cout << "0 - inchidere program" << endl;
        cout << "1 - afisarea tuturor clientilor" << endl;
        cout << "2 - afisarea detaliata a unui client" << endl;
        cout << "3 - sortare clienti" << endl;
        cout << "4 - afisarea locatiilor dintr-un anumit perimetru" << endl;
        cout << "5 - afisarea persoanelor de acces ale unui client" << endl;
        cout << "6 - calcul timp reactie client" << endl;
        cout << "7 - calcul timp reactie toti clientii" << endl;
        cout << "8 - adaugare client nou" << endl;
        cout << "9 - salvarea datelor" << endl;
        int comanda;
        cout << "Comanda: "; cin >> comanda;
        cout << endl;

        switch (comanda) {
        case 0: {
            cout << "Ar trebui sa salvati datele inainte sa inchideti programul." << endl;
            cout << "Sunteti sigur ca doriti sa-l inchideti?" << endl;
            cout << "0 - nu" << endl << "1 - da" << endl;
            int confirmare;
            cin >> confirmare;
            if (confirmare) {
                cout << "Programul a fost inchis!";
                return 0;
            }
            else break;
        }
        case 1: {
            parcurgereClienti(clienti);
            cout << endl;
            system("pause");
            break;
        }
        case 2: {
            int ordine;
            parcurgereClienti(clienti);
            cout << "Introduceti numarul de ordine al clientului: ";
            cin >> ordine;
            cout << endl;

            ClientList* aux = clienti;
            while (--ordine > 0)
                aux = aux->urm;
            if (aux != NULL)
                aux->client->afisare();
            else cout << "Nu exista un client cu acest numar de ordine!" << endl;
            system("pause");
            break;
        }
        case 3: {
            int tipSortare;
            cout << endl << "Tipuri de sortare:" << endl;
            cout << "1 - in functie de nume" << endl;
            cout << "2 - in functie de adresa" << endl;
            cout << "3 - in functie de numele societatii administrate" << endl;
            cout << "Introduceti tipul sortarii: "; cin >> tipSortare;
            cout << endl;

            switch (tipSortare) {
            case 1:
                clienti = sortare(clienti, &cmpNumeClient);
                break;
            case 2:
                clienti = sortare(clienti, &cmpAdresaClient);
                break;
            case 3:
                clienti = sortare(clienti, &cmpDenumireSocietate);
                break;
            }
            parcurgereClienti(clienti);
            system("pause");
            break;
        }
        case 4: {
            char perimetru[32];
            cin.get();
            cout << "Introdu perimetrul: ";  cin.getline(perimetru, 32);

            ClientList* clientiPerimetru = cautareClientiCartier(clienti, perimetru);

            cout << endl;
            parcurgereClienti(clientiPerimetru);
            cout << endl;

            system("pause");
            break;
        }
        case 5: {
            int ordine;
            parcurgereClienti(clienti);
            cout << "Introduceti numarul de ordine al clientului: ";
            cin >> ordine;
            cout << endl;

            ClientList* aux = clienti;
            while (--ordine > 0)
                aux = aux->urm;
            if (aux != NULL) {
                cout << "Client: " << aux->client->getPersoana()->getNume() << " " <<
                    aux->client->getPersoana()->getPrenume() << endl;
                Societate* societate = aux->client->getFunctie().societate;
                if (societate) {
                    PersList* persAcces = societate->getPersAcces();
                    cout << "Persoane cu acces in societate:" << endl;
                    while (persAcces != NULL) {
                        cout << "\t" << persAcces->pers->getNume() << " " << persAcces->pers->getPrenume() << endl;
                        persAcces = persAcces->urm;
                    }
                }

                else cout << "Acest client este persoana fizica, deci doar el are acces!" << endl;
            }
            else cout << "Nu exista un client cu acest numar de ordine!" << endl;
            cout << endl;
            system("pause");
            break;
        }
        case 6: {
            int ordine;
            parcurgereClienti(clienti);
            cout << "Introduceti numarul de ordine al clientului: ";
            cin >> ordine;
            cout << endl;

            ClientList* aux = clienti;
            while (--ordine > 0)
                aux = aux->urm;
            if (aux != NULL) {
                float timp = simulareClient(aux->client);
                if (timp > 0)
                    cout << "TIMP MEDIU REACTIE: " << timp << " MINUTE" << endl;
                else
                    cout << "Nu exista interventii la acest client!" << endl;

            }
            else cout << "Nu exista un client cu acest numar de ordine!" << endl;
            cout << endl;
            system("pause");
            break;
        }
        case 7: {
            float timp = simulareTotiClientii(clienti);
            if (timp > 0)
                cout << "TIMP MEDIU REACTIE PE TOATE INTERVENTIILE: " << timp << " MINUTE" << endl << endl;
            system("pause");
            break;
        }
        case 8: {
            adaugareClient(clienti, citireClientTastatura());
            system("pause");
            break;
        }
        case 9: {
            ofstream out("date.txt");
            salvareClienti(clienti, out);
            out.close();
            cout << "Datele au fost salvate cu succes!" << endl;
            system("pause");
        }
        }
    }
    return 0;
}