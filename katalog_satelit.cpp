#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <limits>
#include <cstdlib>
#include <memory>
#include <windows.h>


using namespace std;

class Satelita {
public:
    Satelita(const string& nazwa, double wysokoscOrbity, double predkosc, double czasZycia)
        : nazwa(nazwa), wysokoscOrbity(wysokoscOrbity), predkosc(predkosc), czasZycia(czasZycia) {}

    Satelita(istringstream& iss) {
    iss >> nazwa;
    iss >> wysokoscOrbity;
    iss >> predkosc;
    iss >> czasZycia;
}



    virtual void wyswietlInfo() const {
        cout << "Nazwa: " << nazwa << "\n";
        cout << "Wysokosc orbity: " << wysokoscOrbity << " km\n";
        cout << "Predkosc: " << predkosc << " km/s\n";
        cout << "Czas zycia orbity: " << czasZycia << " lat\n";
        cout << "------------------------\n";
    }

    const string& pobierzNazwe() const {
        return nazwa;
    }

    double pobierzWysokoscOrbity() const {
        return wysokoscOrbity;
    }

    double pobierzPredkosc() const {
        return predkosc;
    }

    void edytujInfo() {
    cout << "Edycja informacji dla satelity: " << nazwa << "\n";

    cout << "Nowa wysokosc orbity (w kilometrach): ";
    while (!(cin >> wysokoscOrbity)) {
        cout << "Bledne dane! Podaj poprawna wysokosc orbity (w kilometrach): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Nowa predkosc satelity (w km/s): ";
    while (!(cin >> predkosc)) {
        cout << "Bledne dane! Podaj poprawna predkosc satelity (w km/s): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Nowy czas zycia orbity (w latach): ";
    while (!(cin >> czasZycia)) {
        cout << "Bledne dane! Podaj poprawny czas zycia orbity (w latach): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

    friend ostream& operator<<(ostream& os, const Satelita& satelita) {
        os << "Nazwa: " << satelita.nazwa << "\n";
        os << "Wysokosc orbity: " << satelita.wysokoscOrbity << " km\n";
        os << "Predkosc: " << satelita.predkosc << " km/s\n";
        os << "Czas zycia orbity: " << satelita.czasZycia << " lat\n";
        os << "------------------------\n";
        return os;
    }
    friend bool porownajSatelity(const Satelita* s1, const Satelita* s2) {
        return s1->pobierzWysokoscOrbity() < s2->pobierzWysokoscOrbity();
    }




private:
    string nazwa;
    double wysokoscOrbity;
    double predkosc;
    double czasZycia;
};


class SatelitaKomunikacyjny : public Satelita {
public:
    SatelitaKomunikacyjny(const string& nazwa, double wysokoscOrbity, double predkosc, double czasZycia, const string& czestotliwosc)
        : Satelita(nazwa, wysokoscOrbity, predkosc, czasZycia), czestotliwosc(czestotliwosc) {}

    SatelitaKomunikacyjny(istringstream& iss) : Satelita(iss) {
    iss >> czestotliwosc;
}



    void wyswietlInfo() const override {
        Satelita::wyswietlInfo();
        cout << "Czestotliwosc: " << czestotliwosc << "\n";
    }

    void edytujInfo()  {
    Satelita::edytujInfo();


    cout << "Nowa czestotliwosc komunikacji (wpisz liczbe): ";
    while (!(cin >> czestotliwosc)) {
        cout << "Bledne dane! Podaj poprawna czestotliwosc komunikacji (wpisz liczbe): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}
    friend ostream& operator<<(ostream& os, const SatelitaKomunikacyjny& satelita) {
        os << static_cast<const Satelita&>(satelita);
        os << "Czestotliwosc: " << satelita.czestotliwosc << "\n";
        return os;
    }

private:
    string czestotliwosc;
};

void zapiszDoPliku(const vector<unique_ptr<Satelita>>& katalog, const string& nazwaPliku) {
    ofstream plik(nazwaPliku + ".txt");  // pozniej wroce
    if (plik.is_open()) {
        for (const auto& satelita : katalog) {
            plik << *satelita;
        }
        plik.close();
        cout << "Katalog zostal zapisany do pliku: " << nazwaPliku + ".txt" << "\n";
    } else {
        cout << "Blad przy próbie zapisu do pliku.\n";
    }
}


vector<string> pobierzDostepnePliki() {
    vector<string> dostepnePliki;
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile("*", &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        cout << "Blad przy probie odczytu katalogu.\n";
        return dostepnePliki;
    }

    do {
        string nazwaPliku = findFileData.cFileName;
        if (nazwaPliku.find(".txt") != string::npos) {
            dostepnePliki.push_back(nazwaPliku);
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);

    return dostepnePliki;
}

void wczytajZPliku(vector<unique_ptr<Satelita>>& katalog, const string& nazwaPliku) {
  //wczysci
    katalog.clear();

    ifstream plik(nazwaPliku + ".txt");  // tu mi doda txt zebym nie musial pisac
    if (plik.is_open()) {
        string linia;
        while (getline(plik, linia)) {
            istringstream iss(linia);
            string typSatelity;
            iss >> typSatelity;

            if (typSatelity == "Nazwa:") {
                katalog.push_back(make_unique<Satelita>(iss));
            } else if (typSatelity == "Czestotliwosc:") {
                katalog.push_back(make_unique<SatelitaKomunikacyjny>(iss));
            }
        }
        plik.close();
        cout << "Katalog zostal wczytany z pliku: " << nazwaPliku + ".txt" << "\n";
    } else {
        cout << "Blad przy probie odczytu pliku.\n";
    }
}

void usunSatelite(vector<unique_ptr<Satelita>>& katalog, const string& nazwa) {
    auto it = remove_if(katalog.begin(), katalog.end(), [nazwa](const unique_ptr<Satelita>& satelita) {
        return satelita->pobierzNazwe() == nazwa;
    });

    if (it != katalog.end()) {
        cout << "Satelita " << nazwa << " zostal usuniety.\n";
        katalog.erase(it, katalog.end());
    } else {
        cout << "Satelita o nazwie " << nazwa << " nie istnieje w katalogu.\n";
    }
}



void wyswietlStatystyki(const vector<unique_ptr<Satelita>>& katalog) {
    if (katalog.empty()) {
        cout << "Katalog jest pusty. Brak statystyk.\n";
        return;
    }

    double sumaWysokosciOrbity = 0.0;
    double maxPredkosc = katalog.front()->pobierzPredkosc();

    for (const auto& satelita : katalog) {
        sumaWysokosciOrbity += satelita->pobierzWysokoscOrbity();
        maxPredkosc = max(maxPredkosc, satelita->pobierzPredkosc());
    }

    double sredniaWysokoscOrbity = sumaWysokosciOrbity / katalog.size();

    cout << "Statystyki Katalogu:\n";
    cout << "Srednia wysokosc orbity: " << sredniaWysokoscOrbity << " km\n";
    cout << "Maksymalna predkosc: " << maxPredkosc << " km/s\n";
    cout << "Liczba satelitow: " << katalog.size() << "\n";
}


int main() {
    vector<unique_ptr<Satelita>> katalogSatelitow;
    katalogSatelitow.push_back(make_unique<Satelita>("ISS", 420, 7.66, 34));
katalogSatelitow.push_back(make_unique<Satelita>("Teleskop Hubble'a", 547, 7.66, 35));
katalogSatelitow.push_back(make_unique<Satelita>("Satelity GPS", 20200, 3.89, 10));
katalogSatelitow.push_back(make_unique<SatelitaKomunikacyjny>("Astra 1KR", 20200, 2.5, 10,"1.023 MHz"));
katalogSatelitow.push_back(make_unique<Satelita>("Landsat 8", 705, 7.61, 20));
katalogSatelitow.push_back(make_unique<Satelita>("GOES-16", 35786, 3.07, 15));

katalogSatelitow.push_back(make_unique<Satelita>("Satelity Starlink", 550 , 2.52, 20));

katalogSatelitow.push_back(make_unique<Satelita>("Landsat 10", 834, 7.66, 15));

    char wybor;
    do {
        cout << "Menu:\n";
        cout << "1. Dodaj satelite\n";
        cout << "2. Wyswietl katalog\n";
        cout << "3. Zapisz do pliku\n";

        cout << "4. Edytuj satelite\n";
        cout << "5. Statystyki katalogu\n";
        cout<<"6. Usun satelite" << endl;
        cout << "7. Wyjscie\n";

        cout << "Wybierz opcje: ";
        cin >> wybor;

        switch (wybor) {
            case '1': {
                string typSatelity;
                    cout << "Podaj typ satelity (1.Podstawowy / 2.Komunikacyjny). Wpisz 1 lub 2: ";
                    cin >> typSatelity;

    if (typSatelity != "1" && typSatelity != "2") {
        cout << "Nieprawidlowy typ satelity.\n";
        break;
    }

    string nazwa;
    double wysokoscOrbity, predkosc, czasZycia;

                cout << "Podaj nazwe satelity: ";
                cin >> nazwa;


                cout << "Podaj wysokosc orbity (w kilometrach): ";
                while (!(cin >> wysokoscOrbity)) {
                    cout << "Bledne dane! Podaj poprawna wysokosc orbity (w kilometrach): ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // tu mi udrzuca
                }

                cout << "Podaj predkosc satelity (w km/s): ";
                while (!(cin >> predkosc)) {
                    cout << "Bledne dane! Podaj poprawna predkosc satelity (w km/s): ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // tu tez
                }

                cout << "Podaj czas zycia orbity (w latach): ";
                while (!(cin >> czasZycia)) {
                    cout << "Bledne dane! Podaj poprawny czas zycia orbity (w latach): ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // tu tez
                }

                if (typSatelity == "1") {
        katalogSatelitow.push_back(make_unique<Satelita>(nazwa, wysokoscOrbity, predkosc, czasZycia));
    } else if (typSatelity == "2") {
        string czestotliwosc;
        cout << "Podaj czestotliwosc komunikacji: ";
        cin >> czestotliwosc;
        katalogSatelitow.push_back(make_unique<SatelitaKomunikacyjny>(nazwa, wysokoscOrbity, predkosc, czasZycia, czestotliwosc));
    }
    break;
}
            case '2':
                for (const auto& satelita : katalogSatelitow) {
                    satelita->wyswietlInfo();
                }
                break;
            case '3': {
                string nazwaPliku;
                cout << "Podaj nazwe pliku do zapisu: ";
                cin >> nazwaPliku;
                zapiszDoPliku(katalogSatelitow, nazwaPliku);
                break;
            }

            case '4': {
    if (katalogSatelitow.empty()) {
        cout << "Katalog jest pusty. Nie ma satelitów do edycji.\n";
        break;
    }

    cout << "Dostepne satelity do edycji:\n";
    for (const auto& satelita : katalogSatelitow) {
        cout << satelita->pobierzNazwe() << "\n";
    }

    string nazwaDoEdycji;
    cout << "Podaj nazwe satelity do edycji: ";
    cin >> nazwaDoEdycji;

    auto it = find_if(katalogSatelitow.begin(), katalogSatelitow.end(),
                      [nazwaDoEdycji](const unique_ptr<Satelita>& satelita) {
                          return satelita->pobierzNazwe() == nazwaDoEdycji;
                      });

    if (it != katalogSatelitow.end()) {
        (*it)->edytujInfo();
        cout << "Satelita zostaL edytowany.\n";
    } else {
        cout << "Satelita o nazwie " << nazwaDoEdycji << " nie istnieje w katalogu.\n";
    }
    break;
}

            case '5':
                wyswietlStatystyki(katalogSatelitow);
                break;
                case '6': {
    if (katalogSatelitow.empty()) {
        std::cout << "Katalog jest pusty. Nie ma satelitow do usuniecia.\n";
        break;
    }

    std::cout << "Dostepne satelity do usuniecia:\n";
    for (const auto& satelita : katalogSatelitow) {
        std::cout << satelita->pobierzNazwe() << "\n";
    }

    std::string nazwaDoUsuniecia;
    std::cout << "Podaj nazwe satelity do usuniecia: ";
    std::cin >> nazwaDoUsuniecia;

    usunSatelite(katalogSatelitow, nazwaDoUsuniecia);
    break;
}
            case '7':
                cout << "Do widzenia!\n";
                break;
            default:
                cout << "Nieprawidlowy wybor. Sprobuj ponownie.\n";

        }
        cout << "Nacisnij przycisk Enter, aby kontynuowac...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();  // to do entera trzeba czekac pozniej
        system("clear || cls");
    } while (wybor != '7');


    return 0;
}
