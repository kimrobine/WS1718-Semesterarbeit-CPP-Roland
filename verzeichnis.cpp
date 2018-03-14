#include "verzeichnis.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//Ausgabe-Funktion


/* Funktion zum Auslesen der Ausgangs-XML-Datei */
void Verzeichnis::auslesenXML(){

    // Öffnen der XML-Datei
    ifstream datei("flugdatenListe.xml");

    // Deklaration des Vektoren(String) für Nutzung als Puffer
    vector<string> puffer;

    // Schleife, die jede Zeile sichern soll
    for(string zeile; getline(datei,zeile);){
        puffer.push_back(zeile);
    }

   puffer.erase(puffer.begin());
   puffer.pop_back();

   /* Einteilung der Passagierdaten in 10er-Blöcke, um die Informationen spezifisch jedem
    * Passagier zuordnen zu können */
    for(auto i = 0u; i < puffer.size(); i += 10) {
        string zeilenProPassagier[10];
        for (int j = 0; j < 10; ++j) {
            zeilenProPassagier[j] = puffer.at(i+j);
        }
        Passagier x (zeilenProPassagier);
        datenIndex.push_back(x);
    }
}


/* Funktion zum Auslesen der TXT-Datei */
void Verzeichnis::auslesenTXT() {

    // Öffnen der TXT-Datei
    ifstream datei("zolldatenListe.txt");

    for(string zeile; getline(datei, zeile);) {

        /* mit Hilfe des strings passagierSitz soll jede Zeile bis zum Semikolon
         * (nach der verbindenden Sitznummer und vor der Nationalität) durchsucht werden */

        string passagierSitz = zeile.substr(0,zeile.find(';'));

        //Aufruf der Suche-Funktion, um Nationalität aus TXT rauszusuchen & zu speichern
    }
}


//Suche-Funktion



void Verzeichnis::neueXMLerstellen(string neuerDateiname) {
    //Mit ofstream soll Ausgabedatei (konvertierte XML) erzeugt werden
    ofstream XMLdatei;
    XMLdatei.open(neuerDateiname);
    //konvertiertes Verzeichnis soll auch mit ursprünglichem Tag aus erster XML starten
    XMLdatei << "<flugdaten> \n";

    for(auto i = 0u; i < datenIndex.size(); ++i) {
        vector<string> uebergangsPassagierStrings = datenIndex.at(i).neueXMLerstellen();
        for(auto j = 0u; j < uebergangsPassagierStrings.size(); ++j) {
            XMLdatei << uebergangsPassagierStrings.at(j) << "\n";
        }
    }
    //neues Verzeichnis soll auch mit ursprünglich schließendem Tag enden
    XMLdatei << "</flugdaten>";
    //neue Datei wird geschlossen
    XMLdatei.close();
}