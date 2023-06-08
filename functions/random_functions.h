#ifndef MHE_RANDOM_FUNCTIONS_H
#define MHE_RANDOM_FUNCTIONS_H

#include "../structures/indicators_t.h"

namespace mhe {

    indicators_t random_solution(indicators_t &problem);

    indicators_t random_modify(indicators_t &current_solution);

    indicators_t random_modify_normal_dist(indicators_t &current_solution, graph_t &graph);

} // mhe

#endif //MHE_RANDOM_FUNCTIONS_H
