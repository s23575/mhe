#include "tabu_search.h"
#include "../functions/settings.h"
#include "../functions/neighbours.h"
#include "../functions/printing.h"
#include <set>
#include <cstdio>

namespace mhe {

    indicators_t tabu_search(indicators_t &problem, const graph_t &graph) {

        indicators_t solution = problem;
        indicators_t best_solution = solution;

        std::set<indicators_t> tabu_set;
        indicators_t next_solution = solution;

        for (int i = 0; i < get_iterations(); i++) {
            indicators_t tabu_last_element = *tabu_set.insert(next_solution).first;
            std::vector<indicators_t> neighbourhood = generate_neighbourhood(tabu_last_element);

            neighbourhood.erase(std::remove_if(neighbourhood.begin(), neighbourhood.end(),
                                               [&](indicators_t neigbour) {
                                                   return tabu_set.contains(neigbour);
                                               }), neighbourhood.end());

            if (neighbourhood.empty()) {
                printf("(Ate my tail...)\n");
                return best_solution;
            }

            next_solution = *std::max_element(neighbourhood.begin(), neighbourhood.end(),
                                                           [&](auto l, auto r) {
                                                               return get_goal(l, graph) < get_goal(r, graph);
                                                           });

            if (get_goal(next_solution, graph) >= get_goal(best_solution, graph)) {
                best_solution = next_solution;
            }

            tabu_set.insert(next_solution);
        }
        return best_solution;

    }

} // mhe