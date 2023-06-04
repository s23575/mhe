#include "indicators_t.h"
#include "../functions/settings.h"

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
        return k_edges(vertices_num);
    }

    double get_solution_goal(const indicators_t& indicators, const graph_t& graph) {
        int vertices_num = get_vertices_num(indicators, graph);
        int k_edges_num = get_k_edges_num(indicators, graph);
        int edges_num = get_edges_num(indicators, graph);
        return goal(vertices_num, k_edges_num, edges_num);
    }

    double get_min_goal() {
        int vertices_num = get_problem_size();
        int edges_num = get_problem_size() - 1;
        int k_edges_num = k_edges(get_problem_size());
        return goal(vertices_num, k_edges_num, edges_num);
    }

    double get_max_goal() {
        return get_problem_size() * 1000;
    }

    double goal (int vertices, int k_edges, int edges) {
        return (vertices * 1000 * (double) edges / (double) k_edges) - ((k_edges - edges) * 1000);
    }

    int k_edges (int vertices) {
        return ((vertices) * (vertices - 1)) / 2;
    }

} // mhe