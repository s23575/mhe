#include "solution_functions.h"
#include "../functions/random_functions.h"
#include "../solutions/hillclimb_solutions.h"
#include "../solutions/tabu_search.h"
#include "../solutions/brute_force.h"
#include "../solutions/sim_annealing.h"
#include "../solutions/genetic_algorithm.h"

namespace mhe {

    solution_t::solution_t() {}

    solution_t::solution_t(std::function<indicators_t(indicators_t &)> function) {
        this->function_one_param = std::move(function);
    }

    solution_t::solution_t(std::function<indicators_t(indicators_t &, graph_t &)> function) {
        this->function_two_params = std::move(function);
    }

    std::vector<solution_t> solutions = {
            solution_t(),
            solution_t(random_solution),
            solution_t(brute_force),
            solution_t(hillclimb_random),
            solution_t(hillclimb_deterministic),
            solution_t(tabu_search),
            solution_t(sim_annealing),
            solution_t(genetic_algorithm)
    };

    std::vector<std::string> solutions_titles = {
            "0\t- all of the listed",
            "1\t- random solution",
            "2\t- brute force",
            "3\t- random hillclimb",
            "4\t- deterministic hillclimb",
            "5\t- tabu search",
            "6\t- simulated annealing",
            "7\t- genetic algorithm"
    };
} // mhe