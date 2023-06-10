#include "running.h"
#include "configuration.h"
#include "printing.h"
#include "../solutions/sim_annealing.h"
#include "../structures/solution_functions.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>
#include <queue>

namespace mhe {

    void run(std::vector<int> &solutions_to_run) {

        graph_t graph;

        if (filename.empty()) {
            graph = graph_t(problem_size);
        } else {
            graph = get_problem_from_file(filename);
        }

        print_config(std::cout, solutions_to_run);

//        graph_t graph = graph_t(problem_size);
        indicators_t problem = indicators_t(problem_size, true);

        std::string problem_title = "Problem";
        print(std::cout, problem_title, problem, graph);
        print_graph_for_R(std::cout, problem, graph);
//        print_graph_for_Graphviz(std::cout, problem, graph);

//        problem = random_solution(problem);

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
            else solution = solutions[solution_num].function_two_params(problem, graph);
            print(std::cout, solutions_titles[solution_num], solution, graph);
        }
    }

    graph_t get_problem_from_file(const std::string &file) {
        std::ifstream input(file);
        bool edge;
        std::queue<bool> edges_gueue;
        problem_size = 1;

        for (std::string line; getline(input, line);) {
            problem_size++;

            std::stringstream ss(line);
            std::istream_iterator<std::string> begin(ss);
            std::istream_iterator<std::string> end;
            std::vector<std::string> values(begin, end);

            for (auto &v: values) {
                edges_gueue.push(static_cast<bool>(std::stoi(v)));
            }
        }

        return {graph_t(problem_size, edges_gueue)};
    }

} // mhe