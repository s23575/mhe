#ifndef MHE_RUNNING_H
#define MHE_RUNNING_H

#include "../structures/graph_t.h"

#include <vector>
#include <string>

namespace mhe {

    void run(std::vector<int> &solutions_to_run);

    graph_t get_problem_from_file(const std::string& file);

} // mhe

#endif //MHE_RUNNING_H
