#include "brute_force.h"

namespace mhe {

    indicators_t brute_force(indicators_t &problem, const graph_t& graph) {
        indicators_t solution = problem;
        indicators_t best_solution = solution;
        for (auto &&i: solution) {
            i.flip();
            do {
                if (get_solution_score(solution, graph) >= get_solution_score(best_solution, graph)) {
                    best_solution = solution;
                }
            } while (std::next_permutation(solution.begin(), solution.end()));
        }
        return best_solution;
    }
} // mhe