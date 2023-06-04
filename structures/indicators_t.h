#ifndef MHE_INDICATORS_T_H
#define MHE_INDICATORS_T_H

#include <vector>
#include "graph_t.h"

namespace mhe {

    using indicators_t = std::vector<bool>;

    int get_edges_num(const indicators_t& indicators, const graph_t& graph);
    int get_vertices_num(const indicators_t& indicators, const graph_t& graph);
    int get_k_edges_num(const indicators_t& indicators, const graph_t& graph);
    double get_solution_goal(const indicators_t& indicators, const graph_t& graph);

    double get_min_goal();
    double get_max_goal();

    double goal (int vertices, int k_edges, int edges);
    int k_edges (int vertices);
} // mhe

#endif //MHE_INDICATORS_T_H
