#ifndef MHE_PRINTING_H
#define MHE_PRINTING_H

#include "../structures/indicators_t.h"

#include <ostream>

namespace mhe {

    std::ostream &print_config(std::ostream &o, const std::vector<int> &solutions_to_run);

    std::ostream &print_graph(std::ostream &o, const indicators_t &indicators, const graph_t &graph);

    std::ostream &print_graph_data(std::ostream &o, const indicators_t &indicators, const graph_t &graph);

    std::ostream &print_graph_for_R(std::ostream &o, const indicators_t &indicators, const graph_t &graph);

    std::ostream &print_graph_for_Graphviz(std::ostream &o, const indicators_t &indicators, const graph_t &graph);

    std::ostream &print(std::ostream &o, const std::string &title, const indicators_t &indicators,
                        const graph_t &graph);

    std::string indicators_to_string(const indicators_t &indicators);

} // mhe

#endif //MHE_PRINTING_H
