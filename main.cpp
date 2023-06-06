#include <string>

#include "functions/parameters.h"
#include "functions/running.h"

// TODO Uporządkować, kiedy argument przez referencję, a kiedy przez kopię

int main(int argc, char *argv[]) {

    using namespace mhe;

    std::vector<int> algorithms_to_run;

    if (int{argc} == 1) {
        algorithms_to_run = parameters_from_standard_input();
    } else {
        // -p 20 -i 2048 -a 3 4 5 6
        std::vector<std::string> args;
        std::copy(argv + 1, argv + argc, std::back_inserter(args));
        algorithms_to_run = parameters_from_command_line(args);
    }

    run(algorithms_to_run);

    return 0;
}