#include "solution_functions.h"
#include "../functions/random_functions.h"
#include "../solutions/hillclimb_solutions.h"
#include "../solutions/tabu_search.h"
#include "../solutions/brute_force.h"
#include "../solutions/sim_annealing.h"
#include "../solutions/generic_algorithm.h"

namespace mhe {

    solution_t::solution_t() {}

    solution_t::solution_t(std::function<indicators_t(indicators_t &)> function) {
        this->function_one_param = std::move(function);
    }

    solution_t::solution_t(std::function<indicators_t(indicators_t &, graph_t &)> function) {
        this->function_two_params = std::move(function);
    }

    solution_t::solution_t(
            std::function<indicators_t(indicators_t &, graph_t &, std::function<double(int)>)> function) {
        this->function_three_params = std::move(function);
    }

    std::vector<solution_t> solutions = {
            solution_t(),
            solution_t(random_solution),
            solution_t(brute_force),
            solution_t(hillclimb_random),
            solution_t(hillclimb_deterministic),
            solution_t(tabu_search),
            solution_t(sim_annealing),
            solution_t(generic_algorithm)
    };

    std::vector<std::string> solutions_titles = {
            "0 - All of the listed",
            "1 - Random solution",
            "2 - Brute force",
            "3 - Random hillclimb",
            "4 - Deterministic hillclimb",
            "5 - Tabu search",
            "6 - Simulated annealing",
            "7 - Generic algorithm"
    };
} // mhe