#include <iostream>
#include "structures/graph_t.h"
#include "functions/printing.h"
#include "functions/random_functions.h"
#include "solutions/brute_force.h"
#include "functions/settings.h"
#include "solutions/hillclimb_solutions.h"
#include "solutions/tabu_search.h"
#include "solutions/sim_annealing.h"

// TODO Uporządkować, kiedy argument przez referencję, a kiedy przez kopię

int main() {

    std::cout << "\n" << "* * * Problem * * *" << "\n\n";
    mhe::graph_t graph = mhe::graph_t(mhe::get_problem_size());
    mhe::indicators_t problem = mhe::indicators_t(mhe::get_problem_size(), true);

    mhe::print_graph(std::cout, problem, graph);
    mhe::print_graph_data(std::cout, problem, graph);
//    mhe::print_graph_for_R(std::cout, problem, graph);

    std::cout << "\n" << "* * * Random solution * * *" << "\n\n";
    mhe::indicators_t random_sol = mhe::random_solution(problem);
    mhe::print_graph(std::cout, random_sol, graph);
    mhe::print_graph_data(std::cout, random_sol, graph);

//    std::cout << "\n" << "* * * Brute force * * *" << "\n\n";
//    mhe::indicators_t solution = mhe::brute_force(problem, graph);
//    mhe::print_graph(std::cout, solution, graph);
//    mhe::print_graph_data(std::cout, solution, graph);

//    std::cout << "\n" << "* * * Random hillclimb * * *" << "\n\n";
//    mhe::indicators_t solution_random_hillclimb = mhe::hillclimb_random(random_sol, graph);
//    mhe::print_graph(std::cout, solution_random_hillclimb, graph);
//    mhe::print_graph_data(std::cout, solution_random_hillclimb, graph);

//    std::cout << "\n" << "* * * Deterministic hillclimb * * *" << "\n\n";
//    mhe::indicators_t solution_deterministic_hillclimb = mhe::hillclimb_deterministic(random_sol, graph);
//    mhe::print_graph(std::cout, solution_deterministic_hillclimb, graph);
//    mhe::print_graph_data(std::cout, solution_deterministic_hillclimb, graph);

    std::cout << "\n" << "* * * Tabu search * * *" << "\n\n";
    mhe::indicators_t solution_tabu_search = mhe::tabu_search(random_sol, graph);
    mhe::print_graph(std::cout, solution_tabu_search, graph);
    mhe::print_graph_data(std::cout, solution_tabu_search, graph);
//
//    std::cout << "\n" << "* * * Simulated annealing * * *" << "\n\n"; // TODO sprawdzić inny sposób kalkulacji temp.
//    mhe::indicators_t solution_sim_annealing = mhe::sim_annealing(random_sol, graph,
//                                                                  [](int k) { return 10000.0 / k; });
//    mhe::print_graph(std::cout, solution_sim_annealing, graph);
//    mhe::print_graph_data(std::cout, solution_sim_annealing, graph);

    return 0;
}