#include <cstdio>
#include "hillclimb_solutions.h"
#include "../functions/settings.h"
#include "../functions/random_functions.h"
#include "../functions/neighbours.h"
#include "../functions/printing.h"

namespace mhe {

    indicators_t hillclimb_random(indicators_t &problem, const graph_t &graph) {
        indicators_t solution = problem;
        indicators_t best_solution = solution;
        for (int i = 0; i < get_iterations(); i++) {
            random_modify(solution);
            if (get_goal(solution, graph) >= get_goal(best_solution, graph)) {
                best_solution = solution;
            }
        }
        return best_solution;
    }

    indicators_t hillclimb_deterministic(indicators_t &problem, const graph_t& graph) {
        indicators_t solution = problem;
        indicators_t best_solution = solution;
        for (int i = 0; i < get_iterations(); i++) {
            solution = best_neighbour(solution, graph);
            if (get_goal(solution, graph) >= get_goal(best_solution, graph)) {
                best_solution = solution;
            }
        }
        return best_solution;
    }

} // mhe