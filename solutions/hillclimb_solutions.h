#ifndef MHE_HILLCLIMB_SOLUTIONS_H
#define MHE_HILLCLIMB_SOLUTIONS_H

#include "../structures/indicators_t.h"

namespace mhe {

    indicators_t hillclimb_random(indicators_t &problem, const graph_t& graph);

    indicators_t hillclimb_deterministic(indicators_t &problem, const graph_t& graph);

} // mhe

#endif //MHE_HILLCLIMB_SOLUTIONS_H
