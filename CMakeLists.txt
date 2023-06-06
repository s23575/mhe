cmake_minimum_required(VERSION 3.24)
project (mhe)

set(CMAKE_CXX_STANDARD 20)

add_executable(mhe main.cpp structures/graph_t.cpp structures/graph_t.h structures/indicators_t.cpp structures/indicators_t.h functions/printing.cpp functions/printing.h functions/random_functions.cpp functions/random_functions.h solutions/brute_force.cpp solutions/brute_force.h solutions/hillclimb_solutions.cpp solutions/hillclimb_solutions.h functions/configuration.h functions/neighbours.cpp functions/neighbours.h solutions/tabu_search.cpp solutions/tabu_search.h solutions/sim_annealing.cpp solutions/sim_annealing.h solutions/generic_algorithm.cpp solutions/generic_algorithm.h functions/parameters.cpp functions/parameters.h functions/running.cpp functions/running.h)
