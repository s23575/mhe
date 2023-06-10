#ifndef MHE_GENETIC_ALGORITHM_H
#define MHE_GENETIC_ALGORITHM_H

#include "../structures/indicators_t.h"
#include "../utilities/configuration.h"

#include <cmath>

namespace mhe {

    indicators_t genetic_algorithm(const indicators_t &problem, const graph_t &graph, const int &terminal_opt,
                                   const int &crossover_opt, const int &mutation_bit_num);

    std::vector<indicators_t> get_initial_population(const indicators_t &problem);

    bool terminal_condition(const int &terminal_opt, int &iteration, const double &specimen_score);

    double fitness(double specimen_score);

    std::vector<indicators_t> get_elite(std::vector<indicators_t> &population, const graph_t &graph);

    std::vector<indicators_t> selection(const std::vector<double> &fitnesses,
                                        const std::vector<indicators_t> &population);

    std::vector<indicators_t> crossover(const std::vector<indicators_t> &population, const int &crossover_opt);

    std::pair<indicators_t, indicators_t> crossover_pair(const indicators_t &parent_a, const indicators_t &parent_b,
                                                         const int &crossover_opt);

    std::vector<indicators_t> mutation(std::vector<indicators_t> population, int mutation_bit_num);

    inline int get_population_size() { return ((int) pow(problem_size, 2)); }
//    inline int get_population_size() { return problem_size; }

} // mhe

#endif //MHE_GENETIC_ALGORITHM_H
