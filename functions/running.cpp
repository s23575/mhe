#include "running.h"
#include "configuration.h"
#include "printing.h"
#include "random_functions.h"
#include "../solutions/brute_force.h"
#include "../solutions/hillclimb_solutions.h"
#include "../solutions/tabu_search.h"
#include "../solutions/sim_annealing.h"
#include "../solutions/generic_algorithm.h"

#include <iostream>

namespace mhe {

    void run(const std::vector<int>& algorithms_to_run) {

        graph_t graph = graph_t(get_problem_size());
        indicators_t problem = indicators_t(get_problem_size(), true);

        print(std::cout, "Problem", problem, graph);
        print_graph_for_R(std::cout, problem, graph);

        std::vector<std::string> titles {
            "",
            "Random solution",
            "Brute force",
            "Hillclimb random",
            "Hillclimb deterministic",
            "Tabu search",
            "Simulated annealing",
            "Generic algorithm",
        };

        std::vector<std::function<indicators_t(indicators_t &, graph_t &)>> algorithms{
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
        for (auto a: algorithms_to_run) {
            if (a == 0) {
                for (int i = 1; i < algorithms.size(); i++) {
                    solution = algorithms[i](problem,graph);
                    print(std::cout, titles[i], solution, graph);
                }
                break;
            } else {
                solution = algorithms[a](problem, graph);
                print(std::cout, titles[a], problem, graph);
            }
        }
    }

} // mhe