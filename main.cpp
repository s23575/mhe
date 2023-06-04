#include <iostream>
#include "structures/graph_t.h"
#include "functions/printing.h"
#include "functions/random_functions.h"
#include "solutions/brute_force.h"
#include "functions/settings.h"
#include "solutions/hillclimb_solutions.h"
#include "solutions/tabu_search.h"
#include "solutions/sim_annealing.h"
#include "solutions/generic_algorithm.h"

// TODO Uporządkować, kiedy argument przez referencję, a kiedy przez kopię

int main() {

    using namespace mhe;

        graph_t graph = graph_t(get_problem_size());

        indicators_t problem = indicators_t(get_problem_size(), true);
        print(std::cout, "Problem", problem, graph);
//    print_graph_for_R(std::cout, problem, graph);

//        indicators_t random_sol = random_solution(problem);
//        print(std::cout, "Random solution", random_sol, graph);
//
//        indicators_t solution = brute_force(problem, graph);
//        print(std::cout, "Brute force", solution, graph);
//
//        indicators_t solution_random_hillclimb = hillclimb_random(random_sol, graph);
//        print(std::cout, "Random hillclimb", solution_random_hillclimb, graph);
//
//        indicators_t solution_deterministic_hillclimb = hillclimb_deterministic(random_sol, graph);
//        print(std::cout, "Deterministic hillclimb", solution_deterministic_hillclimb, graph);
//
//        indicators_t solution_tabu_search = tabu_search(random_sol, graph);
//        print(std::cout, "Tabu search", solution_tabu_search, graph);
//
//        indicators_t solution_sim_annealing = sim_annealing(random_sol, graph,
//                                                                      [](int k) { return 1000.0 / k; });
//        print(std::cout, "Simulated annealing", solution_sim_annealing, graph);

        indicators_t soultion_generic_algorithm = generic_algorithm(problem, graph);
        print(std::cout, "Generic algorithm", soultion_generic_algorithm, graph);

    return 0;
}