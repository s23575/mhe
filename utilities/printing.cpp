#include <iomanip>
#include "printing.h"

const int left_indentation_size = 24;
const auto left_indentation = std::setw(left_indentation_size);

namespace mhe {

    std::ostream &print_graph(std::ostream &o, indicators_t &indicators, graph_t &graph) {
        int vertex_size = static_cast<int>(std::to_string(indicators.size() - 1).length());
        o << left_indentation << "Graph: "
          << std::setw(vertex_size) << " " << " ";
        for (int i = 0; i < indicators.size(); i++) {
            if (indicators[i]) o << std::setw(vertex_size) << graph.vertices[i] << " ";
        }
        o << "\n";
        for (int i = 0; i < indicators.size(); i++) {
            if (indicators[i]) {
                o << left_indentation << " "
                  << std::setw(vertex_size) << graph.vertices[i] << " ";
                for (int j = 0; j < i + 1; j++) {
                    if (indicators[j]) o << std::setw(vertex_size) << graph.edges[i][j] << " ";
                }
                o << "\n";
            }
        }
        return o;
    }

    std::ostream &print_graph_data(std::ostream &o, indicators_t &indicators, graph_t &graph) {
        o << left_indentation << "Indicators: " << indicators_to_string(indicators) << "\n"
          << left_indentation << "Vertices (num): " << get_vertices_num(indicators, graph) << "\n"
          << left_indentation << "Edges (num): " << get_edges_num(indicators, graph) << "\n"
          << left_indentation << "Max clique edges (num): " << get_k_edges_num(indicators, graph) << "\n"
          << left_indentation << "Score: " << get_solution_score(indicators, graph) << "\n";
        return o;
    }

    std::ostream &print_graph_for_R(std::ostream &o, indicators_t &indicators, graph_t &graph) {
        o << "\n" << "g <- graph_from_literal(";

        for (int i = 0; i < indicators.size(); i++) {
            if (indicators[i]) {
                for (int j = 0; j < i + 1; j++) {
                    if (indicators[j] && graph.edges[i][j]) {
                        o << std::to_string(graph.vertices[i]) << "--"
                          << std::to_string(graph.vertices[j]) << ",\n";
                    }
                }
            }
        }
        o << graph.vertices[0] << "--" << graph.vertices[0] << ")" << "\n";

        return o;
    }
    // TODO print_graph_for_GraphViz

    std::ostream &print(std::ostream &o, std::string title, indicators_t& indicators, graph_t& graph) {
        o << "\n" << "* * * " << title << " * * *" << "\n\n";
        print_graph(o, indicators, graph);
        print_graph_data(o, indicators, graph);

        return o;
    }

    std::string indicators_to_string(indicators_t &indicators) {
        std::string indicators_string;
        for (auto indicator: indicators) indicators_string += to_string(indicator) + " ";
        return indicators_string;
    }
} // mhe