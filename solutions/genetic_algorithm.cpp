#include "genetic_algorithm.h"
#include "../functions/random_functions.h"
#include "../utilities/printing.h"

#include <random>

namespace rgen_genetic_algorithm {
    std::random_device rd;
    std::mt19937 rgen(rd());
}

namespace mhe {

    indicators_t genetic_algorithm(const indicators_t &problem, const graph_t &graph, const int &terminal_opt,
                                   const int &crossover_opt,
                                   const int &mutation_bit_num) {

        int iteration = 0;
        double specimen_score = 0;
        double best_specimen_score = 0;

        std::vector<indicators_t> population = get_initial_population(problem);

        while (true) {
            std::vector<double> fitnesses;

            for (indicators_t p: population) {
                specimen_score = get_solution_score(p, graph);
                if (specimen_score > best_specimen_score) best_specimen_score = specimen_score;
//                std::cout << specimen_score << "\n";
                fitnesses.push_back(fitness(specimen_score));
//                std::cout << fitnesses.back() << "\n";
            }

            if (terminal_condition(terminal_opt, iteration, best_specimen_score)) {
                break;
            }

            std::vector<indicators_t> elite = get_elite(population, graph);
            std::vector<indicators_t> parents = selection(fitnesses, population);
            parents.insert(parents.end(), elite.begin(), elite.end());
            std::vector<indicators_t> offsprings = crossover(parents, crossover_opt);
            offsprings = mutation(offsprings, mutation_bit_num);
            population = offsprings;
        }

        return *std::max_element(population.begin(), population.end(),
                                 [&](auto l, auto r) {
                                     return fitness(get_solution_score(l, graph)) <
                                            fitness(get_solution_score(r, graph));
                                 });
    }

    std::vector<indicators_t> get_initial_population(const indicators_t &problem) {
        std::vector<indicators_t> population;
        for (int i = 0; i < get_population_size(); i++) {
            population.push_back(random_solution(problem));
        }
        return population;
    }

    bool terminal_condition(const int &terminal_opt, int &iteration, const double &best_specimen_score) {
        if (terminal_opt == 1) {
            if (((int) best_specimen_score) % 1000 == 0 and best_specimen_score > (get_max_score() / 2)) {
                std::cout << "(Solution good enough!)" << "\n";
                return true;
            }
        }
        iteration++;
//        return iteration > iterations;
        return iteration > (iterations / 2);
    }

    double fitness(double specimen_score) {
        return (specimen_score - get_min_score()) / (get_max_score() - get_min_score())
               * 10000;
    }

    std::vector<indicators_t> get_elite(std::vector<indicators_t> &population, const graph_t &graph) {
        std::vector<indicators_t> elite(problem_size);
        std::partial_sort(population.rbegin(), (population.rbegin() + problem_size), population.rend(),
                          [&](indicators_t &l, indicators_t &r) {
                              return get_solution_score(l, graph) >
                                     get_solution_score(r, graph);
                          });
        std::copy((population.end() - problem_size), population.end(), elite.begin());
//        std::cout << "Before resizing: " << population.size() << "\n";
        population.resize(population.size() - problem_size);
//        std::cout << "After resizing: " << population.size() << "\n";

        return elite;
    }

    std::vector<indicators_t> selection(const std::vector<double> &fitnesses,
                                        const std::vector<indicators_t> &population) {
        std::vector<indicators_t> selected_population;
        while (selected_population.size() < population.size()) {
            std::uniform_int_distribution<int> dist(0, static_cast<int>(population.size() - 1));
            int a_idx = dist(rgen_genetic_algorithm::rgen);
            int b_idx = dist(rgen_genetic_algorithm::rgen);
            if (fitnesses[a_idx] >= fitnesses[b_idx]) selected_population.push_back(population[a_idx]);
            else selected_population.push_back(population[b_idx]);
        }
        return selected_population;
    }

    std::vector<indicators_t> crossover(const std::vector<indicators_t> &population, const int &crossover_opt) {
//        std::cout << "Parents: " << "\n";
//        for (indicators_t p: population) {
//            std::cout << indicators_to_string(p) << "\n";
//        }

        std::vector<indicators_t> offsprings;
        for (int i = 0; i < population.size(); i += 2) {
//            std::cout << "Parents: \n" << indicators_to_string(population[i]) << "\n"
//                      << indicators_to_string(population[i + 1]) << "\n";
            auto [a, b] = crossover_pair(population[i],
                                         population[(i + 1) % population.size()],
                                         crossover_opt);
//            std::cout << "Offsprings: \n" << indicators_to_string(a) << "\n"
//                      << indicators_to_string(b) << "\n";
            offsprings.push_back(a);
            offsprings.push_back(b);
        }

//        std::cout << "Offsprings: " << "\n";
//        for (indicators_t o: offsprings) {
//            std::cout << indicators_to_string(o) << "\n";
//        }

        return offsprings;
    }

    std::pair<indicators_t, indicators_t> crossover_pair(const indicators_t &parent_a, const indicators_t &parent_b,
                                                         const int &crossover_opt) {

        indicators_t offspring_a;
        indicators_t offspring_b;

        if (crossover_opt == 0) {
            int crossover_size = static_cast<int>(parent_a.size() / 2);

            offspring_a.insert(offspring_a.end(), parent_a.begin(), parent_a.begin() + crossover_size);
            offspring_b.insert(offspring_b.end(), parent_b.begin(), parent_b.begin() + crossover_size);

            offspring_a.insert(offspring_a.end(), parent_b.begin() + crossover_size, parent_b.end());
            offspring_b.insert(offspring_b.end(), parent_a.begin() + crossover_size, parent_a.end());

        } else {
            offspring_a = parent_a;
            offspring_b = parent_b;
            std::uniform_int_distribution<int> distr(0, 1);

            for (int i = 0; i < offspring_a.size(); i++) {
                if (static_cast<bool>(distr(rgen_genetic_algorithm::rgen))) {
                    std::swap(offspring_a[i], offspring_b[i]);
                }
            }
        }

        return {offspring_a, offspring_b};
    }

    std::vector<indicators_t> mutation(std::vector<indicators_t> population, int mutation_bit_num) {
        if (mutation_bit_num < 1) mutation_bit_num = 1;
        if (mutation_bit_num > problem_size) mutation_bit_num = problem_size;

//        std::cout << "Before mutation: " << "\n";
//        for (indicators_t p: population) {
//            std::cout << indicators_to_string(p) << "\n";
//        }

        std::transform(population.begin(), population.end(), population.begin(),
                       [mutation_bit_num](auto s) {
//                           std::cout << "Before mutation: " << indicators_to_string(s) << "\n";
                           for (int i = 0; i < mutation_bit_num; i++) s = random_modify(s);
//                           std::cout << "After mutation:  " << indicators_to_string(s) << "\n";
                           return s;
                       });

//        std::cout << "After mutation: " << "\n";
//        for (indicators_t p: population) {
//            std::cout << indicators_to_string(p) << "\n";
//        }

        return population;
    }

} // mhe