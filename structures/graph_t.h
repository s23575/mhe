#ifndef MHE_GRAPH_T_H
#define MHE_GRAPH_T_H

#include <vector>

namespace mhe {

    struct graph_t {

        std::vector<int> vertices;
        std::vector<std::vector<bool>> edges;

        graph_t(const int &graph_size);

        void set_vertices(const int &size);

        void set_edges(const int &size);

    };
} // mhe

#endif //MHE_GRAPH_T_H