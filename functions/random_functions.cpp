#include "random_functions.h"
#include <random>

namespace rgen_random_solutions {
    std::random_device rd;
    std::mt19937 rgen(rd());
}

namespace mhe {

    indicators_t random_solution(indicators_t &problem) {
        indicators_t solution = problem;
        std::uniform_int_distribution<int> distr(0, 1);
        for (auto &&i: solution) {
            if (!static_cast<bool>(distr(rgen_random_solutions::rgen))) {
                i.flip();
            }
        }
        return solution;
    }

    indicators_t random_modify(indicators_t &current_solution) {
        std::uniform_int_distribution<int> distr(0, static_cast<int>(current_solution.size() - 1));
        int a = distr(rgen_random_solutions::rgen);
        current_solution[a].flip(); // TODO zmiana tylo dodatnich wskaźników?
        return current_solution;
    }

} // mhe