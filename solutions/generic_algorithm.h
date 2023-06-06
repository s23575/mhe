#ifndef MHE_GENERIC_ALGORITHM_H
#define MHE_GENERIC_ALGORITHM_H

#include "../structures/indicators_t.h"

namespace mhe {

    indicators_t generic_algorithm(indicators_t &problem, const graph_t &graph);
    std::vector<indicators_t> get_initial_population(indicators_t &problem, graph_t graph);
    bool terminal_condition(int& iteration);
    double fitness(indicators_t specimen, const graph_t &graph);
    std::vector<indicators_t> selection (std::vector<double> fitnesses, std::vector<indicators_t> population);
    std::vector<indicators_t> crossover (std::vector<indicators_t> population);
    std::pair<indicators_t, indicators_t > crossover_pair(indicators_t parent_a, indicators_t parent_b);
    std::vector<indicators_t> mutation (std::vector<indicators_t> population);

} // mhe

#endif //MHE_GENERIC_ALGORITHM_H
