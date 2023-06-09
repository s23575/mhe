#include "tabu_search.h"
#include "../utilities/configuration.h"
#include "../functions/neighbours.h"
#include "../utilities/printing.h"

#include <iostream>
#include <set>
#include <queue>

namespace mhe {

    indicators_t tabu_search(const indicators_t &problem, const graph_t &graph) {

        const indicators_t &solution = problem;
        indicators_t best_solution = solution;

        std::set<indicators_t> tabu_set;
        std::set<indicators_t>::iterator tabu_iterator;
        std::queue<std::set<indicators_t>::iterator> tabu_iterators_queue;

        indicators_t next_solution = solution;

        for (int i = 0; i < iterations; i++) {
            tabu_iterator = tabu_set.insert(next_solution).first;

            if (tabu_size > 0) {
                tabu_iterators_queue.push(tabu_iterator);
                if (tabu_iterators_queue.size() > tabu_size) {
                    tabu_set.erase(tabu_iterators_queue.front());
                    tabu_iterators_queue.pop();
                }
            }

            indicators_t tabu_last_element = *tabu_iterator;
            std::vector<indicators_t> neighbourhood = generate_neighbourhood(tabu_last_element);

//            std::cout << "Tabu last element: " << indicators_to_string(tabu_last_element) << "\n";
//            std::cout << "Tabu size: " << tabu_set.size() << "\n";
//            std::cout << "Tabu elements: " << indicators_to_string(tabu_last_element) << "\n";
//            for (auto t : tabu_set) {
//                std::cout << indicators_to_string(t) << "\n";
//            }
//            std::cout << "\n";

            neighbourhood.erase(std::remove_if(neighbourhood.begin(), neighbourhood.end(),
                                               [&](indicators_t neighbour) {
                                                   return tabu_set.contains(neighbour);
                                               }), neighbourhood.end());

            if (neighbourhood.empty()) {
                printf("(I ate my tail...)\n");
                return best_solution;
            }

            next_solution = *std::max_element(neighbourhood.begin(), neighbourhood.end(),
                                              [&](auto l, auto r) {
                                                  return get_solution_score(l, graph) <
                                                         get_solution_score(r, graph);
                                              });

            if (get_solution_score(next_solution, graph) >= get_solution_score(best_solution, graph)) {
                best_solution = next_solution;
            }
        }
        return best_solution;

    }

} // mhe