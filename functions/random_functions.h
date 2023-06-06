#ifndef MHE_RANDOM_FUNCTIONS_H
#define MHE_RANDOM_FUNCTIONS_H

#include "../structures/indicators_t.h"

namespace mhe {

    indicators_t random_solution(indicators_t &problem, graph_t &graph);
    indicators_t random_modify(indicators_t &current_solution);

} // mhe

#endif //MHE_RANDOM_FUNCTIONS_H
