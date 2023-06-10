#include "neighbours.h"
#include "../utilities/printing.h"

#include <iostream>

namespace mhe {

    std::vector<indicators_t> generate_neighbourhood(const indicators_t &current_solution) {
        std::vector<indicators_t> neighbourhood;
        indicators_t neighbour = current_solution;

        for (int i = 0; i < current_solution.size(); i++) {
            neighbour[i].flip();
//            std::cout << "Neighbour: " << indicators_to_string(neighbour) << "\n";
            if (get_vertices_num(neighbour) > 1) {
                neighbourhood.push_back(neighbour);
            }
        }
//        std::cout << "\n";

        return neighbourhood;
    }

    indicators_t best_neighbour(const indicators_t &current_solution, const graph_t &graph) {

        std::vector<indicators_t> neighbourhood = generate_neighbourhood(current_solution);

        return *std::max_element(neighbourhood.begin(), neighbourhood.end(),
                                 [&](auto l, auto r) {
                                     return get_solution_score(l, graph) < get_solution_score(r, graph);
                                 });
    }
} // mhe