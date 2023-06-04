#ifndef MHE_PRINTING_H
#define MHE_PRINTING_H

#include "../structures/indicators_t.h"
#include <ostream>

namespace mhe {

    std::ostream &print_graph(std::ostream &o, indicators_t& indicators, graph_t& graph);
    std::ostream &print_graph_data(std::ostream &o, indicators_t& indicators, graph_t& graph);
    std::ostream &print_graph_for_R(std::ostream &o, indicators_t& indicators, graph_t& graph);

    std::ostream &print(std::ostream &o, std::string title, indicators_t& indicators, graph_t& graph);

    std::string indicators_to_string(indicators_t& indicators);

} // mhe

#endif //MHE_PRINTING_H
