#include "hillclimb_solutions.h"
#include "../utilities/configuration.h"
#include "../functions/random_functions.h"
#include "../functions/neighbours.h"
#include "../utilities/printing.h"

#include <iostream>

namespace mhe {

    indicators_t hillclimb_random(indicators_t &problem, graph_t &graph) {
        indicators_t solution = problem;
        indicators_t best_solution = solution;
        for (int i = 0; i < iterations; i++) {
            solution = random_modify(solution);
            if (get_solution_score(solution, graph) >= get_solution_score(best_solution, graph)) {
                best_solution = solution;
//                std::cout << "Best solution: " << indicators_to_string(best_solution) << " Score: "
//                          << get_solution_score(best_solution, graph) << "\n";
            }
        }
        return best_solution;
    }

    indicators_t hillclimb_deterministic(indicators_t &problem, graph_t &graph) {
        indicators_t solution = problem;
//        std::cout << "\nSolution: " << indicators_to_string(solution) << " Score: "
//                  << get_solution_score(solution, graph) << "\n";
        indicators_t best_solution = solution;
        for (int i = 0; i < iterations; i++) {
            solution = best_neighbour(solution, graph);
//            std::cout << "Best neighbour: " << indicators_to_string(solution) << " Score: "
//                      << get_solution_score(solution, graph) << "\n";
            if (get_solution_score(solution, graph) >= get_solution_score(best_solution, graph)) {
                best_solution = solution;
//                std::cout << "\nBest solution: " << indicators_to_string(best_solution) << " Score: "
//                          << get_solution_score(best_solution, graph) << "\n";
            }
        }
        return best_solution;
    }

} // mhe