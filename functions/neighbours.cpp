#include <cstdio>
#include "neighbours.h"
#include "printing.h"

namespace mhe {

    std::vector<indicators_t> generate_neighbourhood(indicators_t &current_solution) {
        std::vector<indicators_t> neighbourhood;
        indicators_t neighbour = current_solution;
        printf("Neighbourhood: %s\n", indicators_to_string(neighbour).c_str());
        for (int i = 0; i < current_solution.size(); i++) {
            neighbour[i].flip();
            printf("%s\n", indicators_to_string(neighbour).c_str());
            neighbourhood.push_back(neighbour);
        }
        printf("\n");
        return neighbourhood;
    }

    indicators_t best_neighbour(indicators_t &current_solution, const graph_t &graph) {
        std::vector<indicators_t> neighbourhood = generate_neighbourhood(current_solution);
        return *std::max_element(neighbourhood.begin(), neighbourhood.end(),
                                 [&](auto l, auto r)
                                 { return get_goal(l, graph) < get_goal(r, graph); });
    }

    // TODO Zdefiniowanie sąsiedztwa: - wszystkie, z jednym zmienionym, - wszystkie, z jednym zmienionym, ale tylko
    //  dodatnim, - zamiana dwóch sąsiadujących

    // TODO Zmienić "size()" na "get_size_problem()"

} // mhe