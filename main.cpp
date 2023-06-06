#include "utilities/configuration.h"
#include "utilities/running.h"

#include <string>

int main(int argc, char *argv[]) {

    using namespace mhe;

    std::vector<int> solutions_to_run;

    if (int{argc} == 1) {
        solutions_to_run = set_parameters_from_standard_input();
    } else {
        // -p 20 -i 2048 -a 3 4 5 6
        std::vector<std::string> parameters;
        std::copy(argv + 1, argv + argc, std::back_inserter(parameters));
        solutions_to_run = set_parameters_from_command_line(parameters);
    }

    run(solutions_to_run);

    return 0;
}