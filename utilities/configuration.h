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

    extern int tabu_size;

    std::vector<int> set_parameters_from_command_line(std::vector<std::string> &parameters);

    std::vector<int> set_parameters_from_standard_input();

    void find_parameter(std::vector<std::string> &parameters, std::string parameter_to_find, int &variable);

    void get_parameters(std::vector<int> &solutions_to_run);

    void throw_parameters_error();

    inline int get_population_size() { return problem_size ^ 2; }

} // mhe

#endif //MHE_CONFIGURATION_H