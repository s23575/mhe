#ifndef MHE_SIM_ANNEALING_H
#define MHE_SIM_ANNEALING_H

#include "../structures/indicators_t.h"
#include <functional>

namespace mhe {

    indicators_t sim_annealing(indicators_t &problem, const graph_t& graph, std::function<double(int)> temp);

} // mhe

#endif //MHE_SIM_ANNEALING_H
