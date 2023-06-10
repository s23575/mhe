#ifndef MHE_CONFIGURATION_H
#define MHE_CONFIGURATION_H

#include "../structures/graph_t.h"
#include "../structures/indicators_t.h"

#include <iostream>
#include <vector>
#include <string>

namespace mhe {

    extern int iterations;
    extern int problem_size;
    extern std::string filename;

    extern int tabu_size;
    extern int temp_func;
    extern int terminal_opt;
    extern int crossover_opt;
    extern int mutation_bit_num;

    std::vector<int> set_parameters_from_command_line(std::vector<std::string> &parameters);

    std::vector<int> set_parameters_from_standard_input();

    int find_parameter(std::vector<std::string> &parameters, const std::string &parameter_to_find);

    void get_parameters(std::vector<int> &solutions_to_run);

    void throw_parameters_error();

    void get_help();

    bool get_options_for_solution(const std::vector<int> &solutions_to_run, const int &sol);

} // mhe

#endif //MHE_CONFIGURATION_H