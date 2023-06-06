#ifndef MHE_PARAMETERS_H
#define MHE_PARAMETERS_H

#include <vector>
#include <string>
#include "../structures/graph_t.h"
#include "../structures/indicators_t.h"

namespace mhe {

    std::vector<int> parameters_from_command_line(std::vector<std::string> parameters);
    std::vector<int> parameters_from_standard_input();

    void return_parameters(std::vector<int> &algorithms_to_run);
    void return_parameters_error();

} // mhe

#endif //MHE_PARAMETERS_H
