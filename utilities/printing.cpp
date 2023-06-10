#include "printing.h"
#include "configuration.h"
#include "..\structures\solution_functions.h"

#include <iomanip>

namespace mhe {

    const int left_indentation_size = 24;
    const auto left_indentation = std::setw(left_indentation_size);

    std::ostream &print_config(std::ostream &o, const std::vector<int> &solutions_to_run) {
        o << "\n" << "* * * Configuration * * *" << "\n\n"
          << left_indentation << "Problem size: " << problem_size << "\n"
          << left_indentation << "Iterations: " << iterations << "\n"
          << left_indentation << "Selected solution: ";

        for (const auto &solution_num: solutions_to_run) {
            if (solution_num != solutions_to_run.at(0)) o << left_indentation << " ";
            o << solutions_titles[solution_num] << "\n";
        }

        o << left_indentation << "Tabu size: " << tabu_size << "\t(if applies)\n"
          << left_indentation << "Temperature function: " << temp_func << "\t(if applies)\n"
          << left_indentation << "Terminal condition: " << terminal_opt << "\t(if applies)\n"
          << left_indentation << "Crossover method: " << crossover_opt << "\t(if applies)\n"
          << left_indentation << "Alleles to change: " << mutation_bit_num << "\t(if applies)\n";

        return o;
    }

    std::ostream &print_graph(std::ostream &o, const indicators_t &indicators, const graph_t &graph) {

        if (get_vertices_num(indicators) <= 30) {

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
        }

        return o;
    }

    std::ostream &print_graph_data(std::ostream &o, const indicators_t &indicators, const graph_t &graph) {
        o << left_indentation << "Indicators: " << indicators_to_string(indicators) << "\n"
          << left_indentation << "Vertices (num): " << get_vertices_num(indicators) << "\n"
          << left_indentation << "Edges (num): " << get_edges_num(indicators, graph) << "\n"
          << left_indentation << "Max clique edges (num): " << get_k_edges_num(indicators) << "\n"
          << left_indentation << "Score: " << get_solution_score(indicators, graph) << "\n\n";
        return o;
    }

    std::ostream &print_graph_for_R(std::ostream &o, const indicators_t &indicators, const graph_t &graph) {
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
        o << graph.vertices[0] << "--" << graph.vertices[0] << ")" << "\n\n";

        return o;
    }

    std::ostream &print_graph_for_Graphviz(std::ostream &o, const indicators_t &indicators, const graph_t &graph) {
        o << "\n" << "graph {";

        for (int i = 0; i < indicators.size(); i++) {
            if (indicators[i]) {
                for (int j = 0; j < i + 1; j++) {
                    if (indicators[j] && graph.edges[i][j]) {
                        o << std::to_string(graph.vertices[i]) << "--"
                          << std::to_string(graph.vertices[j]) << ";\n";
                    }
                }
            }
        }
        o << graph.vertices[0] << "--" << graph.vertices[0] << "}" << "\n\n";

        return o;
    }

    std::ostream &print(std::ostream &o, const std::string &title, const indicators_t &indicators,
                        const graph_t &graph) {
        o << "\n" << "* * * " << title << " * * *" << "\n\n";
        print_graph(o, indicators, graph);
        print_graph_data(o, indicators, graph);

        return o;
    }

    std::string indicators_to_string(const indicators_t &indicators) {
        std::string indicators_string;
        for (auto indicator: indicators) indicators_string += std::to_string(indicator) + " ";
        return indicators_string;
    }
} // mhe
