#include "running.h"
#include "configuration.h"
#include "printing.h"
#include "../functions/random_functions.h"
#include "../solutions/brute_force.h"
#include "../solutions/hillclimb_solutions.h"
#include "../solutions/tabu_search.h"
#include "../solutions/sim_annealing.h"
#include "../solutions/generic_algorithm.h"

#include <iostream>
#include <functional>

namespace mhe {

    void run(const std::vector<int> &solutions_to_run) {

        graph_t graph = graph_t(problem_size);
        indicators_t problem = indicators_t(problem_size, true);

        print(std::cout, "Problem", problem, graph);
        print_graph_for_R(std::cout, problem, graph);

        std::vector<std::function<indicators_t(indicators_t &, graph_t &)>> solutions{
                nullptr,
                random_solution,
                brute_force,
                hillclimb_random,
                hillclimb_deterministic,
                tabu_search,
                sim_annealing,
                generic_algorithm,
        };

        indicators_t solution;
        for (auto solution_num: solutions_to_run) {
            if (solution_num == 0) {
                for (int i = 1; i < solutions.size(); i++) {
                    solution = solutions[i](problem, graph);
                    print(std::cout, solutions_titles[i], solution, graph);
                }
                break;
            } else {
                solution = solutions[solution_num](problem, graph);
                print(std::cout, solutions_titles[solution_num], problem, graph);
            }
        }
    }

} // mhe