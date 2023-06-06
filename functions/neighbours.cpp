#include "neighbours.h"
#include "../utilities/printing.h"

#include <iostream>

namespace mhe {

    std::vector<indicators_t> generate_neighbourhood(indicators_t &current_solution, graph_t &graph) {
        std::vector<indicators_t> neighbourhood;
        indicators_t neighbour = current_solution;
        for (int i = 0; i < current_solution.size(); i++) {
            neighbour[i].flip();
//            std::cout << "Neighbour: " << indicators_to_string(neighbour) << " Score: "
//                      << get_solution_score(neighbour, graph) << "\n";
            neighbourhood.push_back(neighbour);
        }
        return neighbourhood;
    }

    indicators_t best_neighbour(indicators_t &current_solution, graph_t &graph) {
        std::vector<indicators_t> neighbourhood = generate_neighbourhood(current_solution, graph);
        return *std::max_element(neighbourhood.begin(), neighbourhood.end(),
                                 [&](auto l, auto r) {
                                     return get_solution_score(l, graph) < get_solution_score(r, graph);
                                 });
    }
} // mhe