#include <iostream>
#include <vector>
#include <functional>
#include <random>
std::random_device rd;
std::mt19937 mt_generator(rd());

using chromosome_t = std::vector<int>;
using population_t = std::vector<chromosome_t>;

population_t generate_population(int size) {
    using namespace std;
    population_t pop;

    for (int i = 0; i < size; ++i) {
        chromosome_t ch;

        for (int j = 0; j < size ; ++j) {
            uniform_int_distribution<int> uni(0, 1);
            ch.push_back(uni(mt_generator));
        }
        pop.push_back(ch);
    }

    return pop;
}

std::pair<double, double> decode(chromosome_t chromosome) {
    double x = 0.0;
    double y = 0.0;

    for (int i = 0; i < chromosome.size() / 2; i++) {
        x = x * 2 + chromosome[i];
    }

    for (int i = chromosome.size() / 2; i < chromosome.size(); i++) {
        y = y * 2 + chromosome[i];
    }

    x = x / pow(2.0, (chromosome.size() / 2 - 4)) - 8;
    y = y / pow(2.0, (chromosome.size() / 2 - 4)) - 8;

    return {x, y};
}

auto booth_f_v = [](std::pair<double, double> p) {
    return pow((p.first+ 2*p.second - 7),2) + pow((2*p.first+p.second-5),2);
};

double fintess_function(std::pair<double,double> pop) {
    return 1.0 / (std::abs(booth_f_v(pop)));
}

int main() {
    population_t population = generate_population(100 + (22990 % 10) * 2);

    for (auto &chromosome: population) {
        auto decoded = decode(chromosome);
        std::cout << "x= " << decoded.first << ", y= " << decoded.second << " | fitness = " << fintess_function(decoded) << std::endl;
    }
}