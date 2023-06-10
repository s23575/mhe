#include "graph_t.h"
#include "indicators_t.h"

#include <random>

namespace rgen_graph_t {
    std::random_device rd;
    std::mt19937 rgen(rd());
    // std::mt19937 rgen(123456789);
}

namespace mhe {

    graph_t::graph_t(){};

    graph_t::graph_t(const int &graph_size) {
        this->
                set_vertices(graph_size),
                set_edges(graph_size);
    }

    graph_t::graph_t(const int &graph_size, std::queue<bool> edges_queue) {
        this->
                set_vertices(graph_size),
                set_edges_from_file(graph_size, edges_queue);
    }


    void graph_t::set_vertices(const int &size) {
        for (int i = 0; i < size; i++) vertices.push_back(i);
    }

    void graph_t::set_edges(const int &size) {
        edges.resize(size, std::vector<bool>());
        indicators_t indicators = std::vector<bool>(size, true);

        for (int i = 0; i < size; i++) edges[i].resize(i + 1, false);

        do {
            for (int i = 0; i < size; i++) {
                std::uniform_int_distribution<int> distr(0, i);
                int j = distr(rgen_graph_t::rgen);
                if (j == i) edges[i][j] = false;
                else edges[i][j] = static_cast<bool>(distr(rgen_graph_t::rgen));
            }
//        } while (get_edges_num(size) < (size - 1));
        } while (get_edges_num(indicators, *this) < get_k_edges_num(indicators) * 3 / 4);
    }

    void graph_t::set_edges_from_file(const int &size, std::queue<bool> edges_queue) {
        edges.resize(size, std::vector<bool>());
        indicators_t indicators = std::vector<bool>(size, true);

        for (int i = 0; i < size; i++) edges[i].resize(i + 1, false);

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < i + 1; j++) {
                if (j == i) edges[i][j] = false;
                else {
                    edges[i][j] = edges_queue.front();
                    edges_queue.pop();
                }
            }
        }
    }

} // mhe