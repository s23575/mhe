#ifndef MHE_TABU_SEARCH_H
#define MHE_TABU_SEARCH_H

#include "../structures/indicators_t.h"

namespace mhe {

    indicators_t tabu_search(const indicators_t &problem, const graph_t &graph);

} // mhe40


#endif //MHE_TABU_SEARCH_H
