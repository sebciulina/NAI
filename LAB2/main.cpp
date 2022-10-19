#include <iostream>
#include <vector>
#include <functional>
#include <random>
#include <map>


using domain_t = std::vector<double>;
std::random_device rd;
std::mt19937 mt_generator(rd());

domain_t
hill_climbing(const std::function<double(domain_t)> &f, domain_t minimal_d, domain_t maximal_d, int max_iterations) {
    domain_t current_p(minimal_d.size());
    for (int i = 0; i < minimal_d.size(); i++) {
        std::uniform_real_distribution<double> dist(minimal_d[i], maximal_d[i]);
        current_p[i] = dist(mt_generator);
    }
    for (int iteration = 0; iteration < max_iterations; iteration++) {
        domain_t new_p(minimal_d.size());
        for (int i = 0; i < minimal_d.size(); i++) {
            std::uniform_real_distribution<double> dist(-1.0 / 128.0, 1.0 / 128.0);
            double picked = current_p[i] + dist(mt_generator);
            if (minimal_d[i] < picked && maximal_d[i] > picked) {
                new_p[i] = picked;
            }
        }
        if (f(current_p) > f(new_p)) {
            current_p = new_p;
        }
    }
    return current_p;
}

int main(int argc, char **argv) {
    std::map<std::string, std::function<double(std::vector<double>)>> formatery_h;
    std::vector<std::string> argumenty(argv, argc + argv);

    formatery_h["sphere"] = [](domain_t x) { return x[0] * x[0]; };
    formatery_h["matyas"] = [](domain_t x) { return 0.26 * (x[0] * x[0] + x[1] * x[1]) - (0.48 * x[0] * x[1]); };
    formatery_h["rosenbrock"] = [](domain_t x) { return 100 * pow((x[0] - (x[0] * x[0])), 2) + pow((1 - x[0]), 2); };
    try {
        auto best = hill_climbing(formatery_h.at(argumenty.at(1)), {std::stod(argumenty.at(2))},
                                  {std::stod(argumenty.at(3))}, 10000);
        if (argumenty.at(1) == "matyas") {
            std::cout << "best x = " << best[0] << std::endl;
            std::cout << "best y = " << best[1] << std::endl;
        } else {
            std::cout << "best x = " << best[0] << std::endl;
        }

    }
    catch (std::out_of_range oof) {
        std::cout << "Podano zla funkcje!" << std::endl;
    }
    return 0;
}