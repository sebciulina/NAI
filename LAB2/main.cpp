#include <iostream>
#include <vector>
#include <functional>
#include <random>
#include <map>

auto brute_force = [](auto f, auto domain) {
    auto current_p = domain();
    auto best_point = current_p;
    try {
        while (true) {
            if (f(static_cast<std::vector<double>>(current_p)) < f(static_cast<std::vector<double>>(best_point))) {
                best_point = current_p;
            }
            current_p = domain();
        }
    } catch (std::exception &e) {
    }
    return best_point;
};

using domain_t = std::vector<double>;
std::random_device rd;
std::mt19937 mt_generator(rd());
domain_t hill_climbing(const std::function<double(domain_t)> &f, domain_t minimal_d, domain_t maximal_d, int max_iterations) {
    domain_t current_p(minimal_d.size());
    for (int i = 0; i < minimal_d.size(); i++) {
        std::uniform_real_distribution<double> dist(minimal_d[i], maximal_d[i]);
        current_p[i] = dist(mt_generator);
    }
    for (int iteration = 0; iteration < max_iterations; iteration++) {
        domain_t new_p(minimal_d.size());
        for (int i = 0; i < minimal_d.size(); i++) {
            std::uniform_real_distribution<double> dist(-1.0/128.0, 1.0/128.0);
            new_p[i] = current_p[i] + dist(mt_generator);
        }
        if (f(current_p) > f(new_p)) {
            current_p = new_p;
        }
    }
    return current_p;
}

int main(int argc, char **argv) {
    std::map<std::string, std::function<double(std::vector<double>)>> formatery_b,formatery_h;
    std::vector<std::string> argumenty(argv, argc + argv);
    formatery_b["sphere"] = [](std::vector<double> x) {return x[0]*x[0];};
    formatery_b["himmelblaus"] = [](std::vector<double> x) {return pow((x[0]*x[0]+x[1]-11),2) + pow(x[0]+x[1]*x[1]-7,2);};
    formatery_b["matyas"] = [](std::vector<double> x) {return 0.26*(x[0]*x[0]+x[1]*x[1])-(0.48*x[0]*x[1]);};
    double current_sphere_x = std::stod(argumenty.at(2));
    auto sphere_generator = [&]() {
        current_sphere_x+= 1.0/128.0;
        if (current_sphere_x >= std::stod(argumenty.at(3))) throw std::invalid_argument("finished");
        return current_sphere_x;
    };
    auto best_point = brute_force(formatery_b.at(argumenty.at(1)), sphere_generator);
    std::cout << "best x = " << best_point << std::endl;

    formatery_h["sphere"] = [](domain_t x) {return x[0]*x[0];};
    formatery_h["himmelblaus"] = [](domain_t x) {return pow((x[0]*x[0]+x[1]-11),2) + pow(x[0]+x[1]*x[1]-7,2);};
    formatery_h["matyas"] = [](domain_t x) {return 0.26*(x[0]*x[0]+x[1]*x[1])-(0.48*x[0]*x[1]);};

    auto best2 = hill_climbing(formatery_h.at(argumenty.at(1)), {std::stod(argumenty.at(2))},{std::stod(argumenty.at(3))},10000);
    std::cout << "best x = " << best2[0] << std::endl;
    return 0;
}