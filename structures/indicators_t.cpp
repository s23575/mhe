#include "indicators_t.h"
#include "../utilities/configuration.h"

namespace mhe {

    int get_edges_num(const indicators_t &indicators, const graph_t &graph) {
        int edges_num = 0;
        for (int i = 0; i < indicators.size(); i++) {
            if (indicators[i]) {
                for (int j = 0; j < i + 1; j++) if (indicators[j] && graph.edges[i][j]) edges_num++;
            }
        }
        return edges_num;
    }

    int get_vertices_num(const indicators_t &indicators) {
        return static_cast<int>(std::count(indicators.begin(), indicators.end(), true));
    }

    int get_k_edges_num(const indicators_t &indicators) {
        return k_edges(get_vertices_num(indicators));
    }

    double get_solution_score(const indicators_t &indicators, const graph_t &graph) {
        return score(get_vertices_num(indicators), get_k_edges_num(indicators),
                     get_edges_num(indicators, graph));
    }

    double get_min_score() {
        return score(problem_size, k_edges(problem_size), problem_size - 1);
    }

    double get_max_score() {
        return problem_size * 1000;
    }

    double score(const int &vertices_num, const int &k_edges_num, const int &edges_num) {
        return (vertices_num * 1000 * (double) edges_num / (double) k_edges_num) - ((k_edges_num - edges_num) * 500);
//        return (vertices_num * 1000 * (double) edges_num / (double) k_edges_num) - ((k_edges_num - edges_num) * 1000);
//        return (vertices_num * 1000 * (double) edges_num);
    }

    int k_edges(const int &vertices) {
        return ((vertices) * (vertices - 1)) / 2;
    }

} // mhe