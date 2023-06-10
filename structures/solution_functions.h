#ifndef MHE_SOLUTION_FUNCTIONS_H
#define MHE_SOLUTION_FUNCTIONS_H

#include "indicators_t.h"

#include <utility>
#include <functional>
#include <string>

namespace mhe {

    struct solution_t {
        std::function<indicators_t(indicators_t &)> function_one_param;
        std::function<indicators_t(indicators_t &, graph_t &)> function_two_params;

        solution_t();

        solution_t(std::function<indicators_t(indicators_t &)>);

        solution_t(std::function<indicators_t(indicators_t &, graph_t &)>);

    };

    extern std::vector<solution_t> solutions;

    extern std::vector<std::string> solutions_titles;

} // mhe

#endif //MHE_SOLUTION_FUNCTIONS_H
