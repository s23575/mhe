#include "generic_algorithm.h"
#include "../functions/random_functions.h"
#include "../utilities/configuration.h"
#include "../utilities/printing.h"
#include <cstdio>
#include <random>

namespace rgen_generic_algorithm {
    std::random_device rd;
    std::mt19937 rgen(rd());
}
namespace mhe {

    indicators_t generic_algorithm(indicators_t &problem, const graph_t &graph) {

        std::vector<indicators_t> population = get_initial_population(problem, graph);
//        for (indicators_t p: population) {
//            printf("%s\n", indicators_to_string(p).c_str());
//        }
        int iteration = 0;
        while (terminal_condition(iteration)) {
            std::vector<double> fitnesses;
            for (indicators_t p: population) {
                fitnesses.push_back(fitness(p, graph));
//                printf("%f\n", fitnesses.back());
            }
            std::vector<indicators_t> parents = selection(fitnesses, population);
            std::vector<indicators_t> offsprings = crossover(parents);
            mutation(offsprings);
            population = offsprings;
        }
        return *std::max_element(population.begin(), population.end(),
                                 [&](auto l, auto r) {
                                     return fitness(l, graph) > fitness(r, graph);
                                 });
// TODO tak zapisywać funkcje z lambdą
// TODO elita
    }

    std::vector<indicators_t> get_initial_population(indicators_t &problem, graph_t graph) {
        std::vector<indicators_t> population;
        for (int i = 0; i < get_population_size(); i++) {
            population.push_back(random_solution(problem));
        }
        return population;
    }

    bool terminal_condition(int &iteration) {
        iteration++;
        return iteration <= iterations;
    }

    double fitness(indicators_t specimen, const graph_t &graph) {
        return (get_solution_score(specimen, graph) - get_min_score()) / (get_max_score() - get_min_score())
               * 10000;
    }

    std::vector<indicators_t> selection(std::vector<double> fitnesses, std::vector<indicators_t> population) {
        std::vector<indicators_t> selected_population;
        while (selected_population.size() < population.size()) {
            std::uniform_int_distribution<int> dist(0, static_cast<int>(population.size() - 1));
            int a_idx = dist(rgen_generic_algorithm::rgen);
            int b_idx = dist(rgen_generic_algorithm::rgen);
            if (fitnesses[a_idx] >= fitnesses[b_idx]) selected_population.push_back(population[a_idx]);
            else selected_population.push_back(population[b_idx]);
        }
        return selected_population;
    }

    std::vector<indicators_t> crossover(std::vector<indicators_t> population) {
        std::vector<indicators_t> offsprings;
        for (int i = 0; i < population.size(); i += 2) {
            auto [a, b] = crossover_pair(population[i], population[i + 1]);
            offsprings.push_back(a);
            offsprings.push_back(b);
        }
        return offsprings;
    }

    std::pair<indicators_t, indicators_t> crossover_pair(indicators_t parent_a, indicators_t parent_b) {
        indicators_t offspring_a(parent_a.begin(), parent_a.begin() + static_cast<int>(parent_a.size() / 2));
        indicators_t offspring_b(parent_b.begin(), parent_b.begin() + static_cast<int>(parent_b.size() / 2));
        offspring_a.insert(offspring_a.end(), parent_b.begin() + static_cast<int>(parent_b.size()) / 2,
                           parent_b.end());
        offspring_b.insert(offspring_b.end(), parent_a.begin() + static_cast<int>(parent_a.size()) / 2,
                           parent_a.end());

        return {offspring_a, offspring_b};
    }

    std::vector<indicators_t> mutation(std::vector<indicators_t> population) {
        std::transform(population.begin(), population.end(), population.begin(),
                       [](auto s) { return random_modify(s); });
        return population;
    }

} // mhe