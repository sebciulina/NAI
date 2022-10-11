#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cmath>

using mojafunkcja_t = std::function<double(double, double)>;
using vector_t = std::vector<std::string>;
using formatery_t = std::map<std::string,mojafunkcja_t>;

void wypisz(formatery_t fun, vector_t argumenty) {
    using namespace std;

    auto wybranaFunkcja = fun[argumenty.at(1)];

    string a2 = argumenty.at(2);
    string a3 = argumenty.at(3);

    double a = stod(a2);
    double b = stod(a3);

    cout << wybranaFunkcja(a,b);
}


int main(int argc, char **argv) {
    using namespace std;

    map<string,double> mapa;
    formatery_t formatery;

    formatery["add"] = [](double a, double b) {return a+b;};
    formatery["mod"] = [](double a, double b) {return fmod(a,b);};
    formatery["sin"] = [](double a, double b) {return sin(a);};

    try {
        vector<string> argumenty(argv, argv + argc);
        cout << "Wynik: ";
        wypisz(formatery, argumenty);
    }
    catch (std::out_of_range aor){
        cout << "Podaj argument. Dostepne to: ";
        for (auto [k, v] : formatery) cout << " " << k;
        cout << endl;
    }
    catch (std::bad_function_call bfc){
        cout << "Nie podano poprawnej nazwy funkcji. Dostepne to:" << endl;
        cout << "add   sumuje dwie wartosci" << endl;
        cout << "mod   oblicza wartosc reszty z dzielenia" << endl;
        cout << "sin   liczy wartosc funkcji sinus dla jednego argumentu." << endl;

    }


    return 0;
}