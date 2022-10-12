#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cmath>

using mojafunkcja_t = std::function<double(std::vector<double>)>;
using vector_t = std::vector<std::string>;
using formatery_t = std::map<std::string,mojafunkcja_t>;

void wypisz(formatery_t fun, vector_t argumenty) {
    using namespace std;

    auto wybranaFunkcja = fun[argumenty.at(1)];

    vector<double> v;

    for(int i = 2 ; i <  argumenty.size() ; i++){
        v.push_back(stod(argumenty.at(i)));
    }

    cout << "Wynik: " << wybranaFunkcja(v);
}


int main(int argc, char **argv) {
    using namespace std;

    map<string,double> mapa;
    formatery_t formatery;

    formatery["add"] = [](vector<double> v) {return v[0]+v[1];};
    formatery["mod"] = [](vector<double> v) {return fmod(v[0],v[1]);};
    formatery["sin"] = [](vector<double> v) {return sin(v[0]);};

    try {
        vector<string> argumenty(argv, argv + argc);
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