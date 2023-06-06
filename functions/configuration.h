#include <functional>

#ifndef MHE_CONFIGURATION_H

namespace mhe {

    extern int problem_size;
    extern int iterations;

    inline int get_iterations() { return iterations; }

    inline int get_problem_size() { return problem_size; }

    inline int get_population_size() { return problem_size^2; }

    inline double get_sim_annealing_temp(int k) { return 1000.0 / k; };

#define MHE_CONFIGURATION_H

} // mhe

#endif //MHE_CONFIGURATION_H
