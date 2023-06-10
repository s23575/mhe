#include "sim_annealing.h"
#include "../utilities/configuration.h"
#include "../functions/random_functions.h"

#include <random>

namespace rgen_sim_annealing {
    std::random_device rd;
    std::mt19937 rgen(rd());
}

namespace mhe {

    indicators_t sim_annealing(const indicators_t &problem, const graph_t &graph) {
        indicators_t solution = problem;
        indicators_t best_solution = solution;
        indicators_t best_solution_globally = solution;

        std::function<double(int)> temp;

        if (temp_func == 0) {
            temp = [](int k) { return 1000.0 / k; };
//            std::cout << "Function No. 1" << "\n";
        } else {
            temp = [](int k) { return 1000.0 / log(k); };
//            std::cout << "Function No. 2" << "\n";
        }

        for (int i = 1; i < iterations; i++) {
//            solution = random_modify(solution);
            solution = random_modify_normal_dist(solution, graph);

            if (get_solution_score(solution, graph) >= get_solution_score(best_solution, graph)) {
                best_solution = solution;
                if (get_solution_score(best_solution, graph) >=
                    get_solution_score(best_solution_globally, graph)) {
                    best_solution_globally = best_solution;
                }

            } else {
                std::uniform_real_distribution<double> distr(0.0, 0.1);
                if (distr(rgen_sim_annealing::rgen) <
                    std::exp(-std::abs
                            (get_solution_score(solution, graph) -
                             get_solution_score(best_solution, graph)) / temp(i))) {
                    best_solution = solution;
                }
            }
        }
        return best_solution_globally;
    }

} // mhe