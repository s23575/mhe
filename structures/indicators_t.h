#ifndef MHE_INDICATORS_T_H
#define MHE_INDICATORS_T_H

#include "graph_t.h"

#include <vector>

namespace mhe {

    using indicators_t = std::vector<bool>;

    int get_edges_num(const indicators_t &indicators, const graph_t &graph);

    int get_vertices_num(const indicators_t &indicators, const graph_t &graph);

    int get_k_edges_num(const indicators_t &indicators, const graph_t &graph);

    double get_solution_score(const indicators_t &indicators, const graph_t &graph);

    double get_min_score();

    double get_max_score();

    double score(int vertices_num, int k_edges_num, int edges_num);

    int k_edges(int vertices);
} // mhe

#endif //MHE_INDICATORS_T_H
