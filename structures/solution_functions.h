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
        std::function<indicators_t(indicators_t &, graph_t &, std::function<double(int)>)> function_three_params;
        std::function<indicators_t(indicators_t &, graph_t &, int, int, int)> function_more_params;

        explicit solution_t();

        explicit solution_t(std::function<indicators_t(indicators_t &)>);

        explicit solution_t(std::function<indicators_t(indicators_t &, graph_t &)>);

        explicit solution_t(std::function<indicators_t(indicators_t &, graph_t &, std::function<double(int)>)>);

        explicit solution_t(std::function<indicators_t(indicators_t &, graph_t &, int, int, int)>);
    };

    extern std::vector<solution_t> solutions;

    extern std::vector<std::string> solutions_titles;

} // mhe

#endif //MHE_SOLUTION_FUNCTIONS_H
