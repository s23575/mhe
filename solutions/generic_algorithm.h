#ifndef MHE_GENERIC_ALGORITHM_H
#define MHE_GENERIC_ALGORITHM_H

#include "../structures/indicators_t.h"
#include "../utilities/configuration.h"

#include <cmath>

namespace mhe {

    indicators_t generic_algorithm(indicators_t &problem, graph_t &graph, int terminal_opt, int crossover_opt,
                                   int mutation_bit_num);

    std::vector<indicators_t> get_initial_population(indicators_t &problem);

    bool terminal_condition(int &terminal_opt, int &iteration, double &specimen_score);

    double fitness(double specimen_score);

    std::vector<indicators_t> selection(std::vector<double> fitnesses, std::vector<indicators_t> &population);

    std::vector<indicators_t> crossover(std::vector<indicators_t> &population, int &crossover_opt);

    std::pair<indicators_t, indicators_t> crossover_pair(indicators_t &parent_a, indicators_t &parent_b,
                                                         int &crossover_opt);

    std::vector<indicators_t> mutation(std::vector<indicators_t> population, int mutation_bit_num);

    inline int get_population_size() { return pow(problem_size, 2); }
//    inline int get_population_size() { return problem_size; }

} // mhe

#endif //MHE_GENERIC_ALGORITHM_H
