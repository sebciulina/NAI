#include <iostream>
#include <vector>
#include <functional>
#include <random>
#include <chrono>


std::mt19937 mt_generator((std::random_device())());

using domain_t = std::vector<double>;

domain_t hill_climbing(const std::function<double(domain_t)> &f, domain_t start_point, std::function<std::vector<domain_t>(domain_t)> get_close_points, int max_iterations) {
    domain_t best_p = start_point;
    for (int iteration = 0; iteration < max_iterations; iteration++) {
        auto close_points = get_close_points(best_p);
        auto best_neighbour = *std::min_element(close_points.begin(), close_points.end(), [f](auto a, auto b){return f(a) > f(b);});
        if (f(best_neighbour) < f(best_p)) best_p = best_neighbour;
    }
    return best_p;
}

domain_t brute_force_method(const std::function<double(domain_t)> &f, domain_t start_point, int max_iterations) {
    auto current_p = start_point;
    auto best_p = current_p;
    for (int i = 0; i < max_iterations; i++) {
        if (f(current_p) < f(best_p)) {
            best_p = current_p;
        }
        current_p = start_point;
    }
    return best_p;
}

domain_t simulated_annealing(const std::function<double(domain_t)> &f, domain_t start_point, int max_iterations){
    auto best_p = start_point;
    std::vector<domain_t> vector;
    std::uniform_real_distribution<double> uk(0,1);
    double ukValue = uk(mt_generator);
    vector.push_back(best_p);

    for (int i = 0; i < max_iterations; ++i) {
        auto tk = start_point;
        if(f(tk) <= f(best_p)){
            vector.push_back(best_p);
        } else {
            if (ukValue < exp(-(std::abs(f(tk) - f(best_p)) / (1 / log(i))))) {
                best_p = tk;
                vector.push_back(best_p);
            }
        }
    }
    return best_p;
}

int main() {

    auto booth_f_v = [](domain_t x) {return pow((x[0]+ 2*x[1] - 7),2) + pow((2*x[0]+x[1]-5),2);};
    auto matayas_f_v = [](domain_t x) { return 0.26 * (x[0] * x[0] + x[1] * x[1]) - (0.48 * x[0] * x[1]); };
    auto beale_f_v = [](domain_t x) {return pow((1.5-x[0]+x[0]*x[1]),2) + pow(2.25-x[0]+x[0]*x[1]*x[1],2) + pow(2.265-x[0]+x[0]*x[1]*x[1]*x[1],2);};

    auto get_random_point = []() -> domain_t {
        std::uniform_real_distribution<double>distr(-4,4);
        return {distr(mt_generator), distr(mt_generator)};
    };
    auto get_close_points_random = [](domain_t p0) -> std::vector<domain_t> {
        std::uniform_real_distribution<double>distr(-4,4);
        return {{distr(mt_generator), distr(mt_generator)}};
    };
    std::cout << "----Booth----" << std::endl;

    auto start = std::chrono::high_resolution_clock::now();
    auto best_booth_hill = hill_climbing(booth_f_v, get_random_point(), get_close_points_random,1000000);
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "hill_climbing x = " << best_booth_hill[0] << " y = " << best_booth_hill[1] << " time = " << elapsed.count() << std::endl;

    start = std::chrono::high_resolution_clock::now();
    auto best_booth_brute = brute_force_method(booth_f_v, get_random_point(), 1000000);
    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;
    std::cout << "brute_force_method x = " << best_booth_brute[0] << " y = " << best_booth_brute[1] << " time = " << elapsed.count() << std::endl;

    start = std::chrono::high_resolution_clock::now();
    auto best_booth_annealing = simulated_annealing(booth_f_v, get_random_point() , 1000000);
    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;
    std::cout << "simulated_annealing x = " << best_booth_annealing[0] << " y = " << best_booth_annealing[1] << " time = " << elapsed.count() << std::endl;

    std::cout << "----Matyas----" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    auto best_matyas_hill = hill_climbing(matayas_f_v, get_random_point(), get_close_points_random,1000000);
    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;
    std::cout << "hill_climbing x = " << best_matyas_hill[0] << " y = " << best_matyas_hill[1] << " time = " << elapsed.count() << std::endl;

    start = std::chrono::high_resolution_clock::now();
    auto best_matyas_brute = brute_force_method(matayas_f_v, get_random_point(), 1000000);
    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;
    std::cout << "brute_force_method x = " << best_matyas_brute[0] << " y = " << best_matyas_brute[1] << " time = " << elapsed.count() << std::endl;

    start = std::chrono::high_resolution_clock::now();
    auto best_matyas_annealing = simulated_annealing(matayas_f_v, get_random_point() , 1000000);
    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;
    std::cout << "simulated_annealing x = " << best_matyas_annealing[0] << " y = " << best_matyas_annealing[1] << " time = " << elapsed.count() << std::endl;

    std::cout << "----Beale----" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    auto best_beale_hill = hill_climbing(beale_f_v, get_random_point(), get_close_points_random,1000000);
    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;
    std::cout << "hill_climbing x = " << best_beale_hill[0] << " y = " << best_beale_hill[1] << " time = " << elapsed.count() << std::endl;

    start = std::chrono::high_resolution_clock::now();
    auto best_beale_brute = brute_force_method(beale_f_v, get_random_point(), 1000000);
    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;
    std::cout << "brute_force_method x = " << best_beale_brute[0] << " y = " << best_beale_brute[1] << " time = " << elapsed.count() << std::endl;

    start = std::chrono::high_resolution_clock::now();
    auto best_beale_annealing = simulated_annealing(beale_f_v, get_random_point() , 1000000);
    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;
    std::cout << "simulated_annealing x = " << best_beale_annealing[0] << " y = " << best_beale_annealing[1] << " time = " << elapsed.count() << std::endl;

    return 0;
}