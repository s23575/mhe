#include "running.h"
#include "configuration.h"
#include "printing.h"
#include "../functions/random_functions.h"
#include "../solutions/sim_annealing.h"
#include "../structures/solution_functions.h"

#include <iostream>

namespace mhe {

    void run(std::vector<int> &solutions_to_run) {

        graph_t graph = graph_t(problem_size);
        indicators_t problem = indicators_t(problem_size, true);

        std::string problem_title = "Problem";
        print(std::cout, problem_title, problem, graph);
        print_graph_for_R(std::cout, problem, graph);
//        print_graph_for_Graphviz(std::cout, problem, graph);

        problem = random_solution(problem);

        indicators_t solution;

        solution_t t(sim_annealing);

        if (solutions_to_run[0] == 0) {
            solutions_to_run.clear();
            for (int i = 1; i < solutions.size(); i++) {
                solutions_to_run.push_back(i);
            }
        }

        for (auto solution_num: solutions_to_run) {
            if (solution_num == 1) solution = solutions[solution_num].function_one_param(problem);
            else if (solution_num == 6)
                solution = solutions[solution_num].function_three_params(problem, graph,
                                                                         [](int k) { return 1000.0 / k; });
            else solution = solutions[solution_num].function_two_params(problem, graph);
            print(std::cout, solutions_titles[solution_num], solution, graph);
        }
    }

} // mhe