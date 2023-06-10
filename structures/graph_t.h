#ifndef MHE_GRAPH_T_H
#define MHE_GRAPH_T_H

#include <vector>
#include <queue>

namespace mhe {

    struct graph_t {

        std::vector<int> vertices;
        std::vector<std::vector<bool>> edges;

        graph_t();

        graph_t(const int &graph_size);

        graph_t(const int &graph_size, std::queue<bool> edges_queue);

        void set_vertices(const int &size);

        void set_edges(const int &size);

        void set_edges_from_file(const int &size, std::queue<bool> edges_queue);

    };
} // mhe

#endif //MHE_GRAPH_T_H