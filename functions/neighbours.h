#ifndef MHE_NEIGHBOURS_H
#define MHE_NEIGHBOURS_H

#include "../structures/indicators_t.h"

namespace mhe {

    std::vector<indicators_t> generate_neighbourhood(const indicators_t &current_solution);

    indicators_t best_neighbour(const indicators_t &current_solution, const graph_t &graph);

} // mhe

#endif //MHE_NEIGHBOURS_H
