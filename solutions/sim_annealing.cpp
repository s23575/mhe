#include <random>
#include "sim_annealing.h"
#include "../functions/settings.h"
#include "../functions/random_functions.h"

namespace rgen_sim_annealing {
    std::random_device rd;
    std::mt19937 rgen(rd());
}

namespace mhe {

    indicators_t sim_annealing(indicators_t &problem, const graph_t &graph, std::function<double(int)> temp) {
        indicators_t solution = problem;
        indicators_t best_solution = solution;
        indicators_t best_solution_globally = solution;

        for (int i = 1; i < get_iterations(); i++) {
            solution = random_modify(solution);
            if (get_solution_goal(solution, graph) >= get_solution_goal(best_solution, graph)) {
                best_solution = solution;
                if (get_solution_goal(best_solution, graph) >= get_solution_goal(best_solution_globally, graph)) {
                    best_solution_globally = best_solution;
                }
            } else {
                std::uniform_real_distribution<double> u(0.0, 0.1);
                if (u(rgen_sim_annealing::rgen) <
                    std::exp(-std::abs
                            (get_solution_goal(solution, graph) - get_solution_goal(best_solution, graph)) / temp(i)))
                {
                    best_solution = solution;
                }
            }
        }
        return best_solution_globally;
    }

} // mhe