#include "indicators_t.h"

namespace mhe {

    int get_edges_num(const indicators_t& indicators, const graph_t& graph) {
        int edges_num = 0;
        for (int i = 0; i < indicators.size(); i++) {
            if (indicators[i]) {
                for (int j = 0; j < i + 1; j++) if (indicators[j] && graph.edges[i][j]) edges_num++;
            }
        }
        return edges_num;
    }

    int get_vertices_num(const indicators_t& indicators, const graph_t& graph) {
        return static_cast<int>(std::count(indicators.begin(), indicators.end(), true));
    }

    int get_k_edges_num(const indicators_t& indicators, const graph_t& graph) {
        int vertices_num = get_vertices_num(indicators, graph);
        return (static_cast<int>(vertices_num) * (static_cast<int>(vertices_num) - 1)) / 2;
    }

    double get_goal(const indicators_t& indicators, const graph_t& graph) {
        int edges_ct = get_edges_num(indicators, graph);
        int k_edges_ct = get_k_edges_num(indicators, graph);
        return (get_vertices_num(indicators, graph) - (k_edges_ct - edges_ct)) * 1000
               * ((double) edges_ct / (double) k_edges_ct);
    }

} // mhe