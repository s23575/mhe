#ifndef MHE_NEIGHBOURS_H
#define MHE_NEIGHBOURS_H

#include "../structures/indicators_t.h"

namespace mhe {

    std::vector<indicators_t> generate_neighbourhood(indicators_t &current_solution, graph_t &graph);

    indicators_t best_neighbour(indicators_t &current_solution, graph_t& graph);

} // mhe

#endif //MHE_NEIGHBOURS_H
