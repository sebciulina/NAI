#include <any>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using mojafunkcja_t = std::function<double(double)>;

int main(int argc, char **argv) {
    using namespace std;
    map<string,double> mapa;
    map<string, mojafunkcja_t> formatery;
    //formatery["add"] = [](double a) {return a;};
    vector<double> argumenty;
    for (int i = 1; i < argc ; i++) {
        argumenty.push_back(stod(argv[i]));
    }
    for(auto a : argumenty){
        cout << "arg " << a << endl;
    }
    return 0;
}