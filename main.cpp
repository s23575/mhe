#include "utilities/configuration.h"
#include "utilities/running.h"

#include <string>

int main(int argc, char *argv[]) {

    using namespace mhe;

    std::vector<int> solutions_to_run;

    if (argc == 1) {
        solutions_to_run = set_parameters_from_standard_input();
    } else {
        // -h
        // -p 20 -i 2048 -s 3 4 5 6 -t 20
        // -s 3 4 5 6 -t 30 -p 20 -i 2048
        std::vector<std::string> parameters(argv + 1, argv + argc);
        solutions_to_run = set_parameters_from_command_line(parameters);
    }

    if (!solutions_to_run.empty()) run(solutions_to_run);

    return 0;
}