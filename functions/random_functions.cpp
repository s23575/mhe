#include "random_functions.h"
#include "neighbours.h"
#include "../utilities/printing.h"

#include <random>
#include <map>
#include <iostream>

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
        int i = distr(rgen_random_solutions::rgen);
        current_solution[i].flip();
//        if (current_solution[a]) current_solution[a].flip();
        return current_solution;
    }

    indicators_t random_modify_normal_dist(indicators_t &current_solution, graph_t &graph) {
        std::vector<indicators_t> neighbourhood = generate_neighbourhood(current_solution);
        std::map<double, indicators_t> neigbours_with_scores;

        for (auto n: neighbourhood) {
            neigbours_with_scores[get_solution_score(n, graph)] = n;
        }

        double mean = get_solution_score(current_solution, graph);
//        std::cout << "Mean:" << mean << "\n";

        double stdev = 0;
        for (auto n: neigbours_with_scores) {
            stdev += pow((n.first - mean), 2);
        }
        stdev = sqrt(stdev / (double) neigbours_with_scores.size());
//        std::cout << "Stdev:" << stdev << "\n";

        std::normal_distribution<double> distr(mean, stdev);
        double goal = distr(rgen_random_solutions::rgen);
//        std::cout << "Goal:" << goal << "\n";

        double closest = neigbours_with_scores.begin()->first;
        for (auto n: neigbours_with_scores) {
            if (std::abs(goal - n.first) < std::abs(goal - closest)) closest = n.first;
        }

//        std::cout << "Normal:  " << indicators_to_string(neigbours_with_scores[closest]) << "\n"
//                  << " Score: " << get_solution_score(neigbours_with_scores[closest], graph) << "\n";

        return neigbours_with_scores[closest];
    }

} // mhe