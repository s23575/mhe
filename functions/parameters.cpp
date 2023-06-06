#include "parameters.h"

#include <iostream>

namespace mhe {

    int problem_size;
    int iterations;

    std::vector<int> parameters_from_command_line(std::vector<std::string> parameters) {
        std::vector<int> algorithms_to_run;

        for (int i = 0; i < parameters.size(); i++) {

            if (parameters[i] == "-p") {
                try { problem_size = std::stoi(parameters[i + 1]); }
                catch (const std::exception &) { return_parameters_error(); }

            } else if (parameters[i] == "-i") {
                try { iterations = std::stoi(parameters[i + 1]); }
                catch (const std::exception &) { return_parameters_error(); }

            } else if (parameters[i] == "-a") {
                std::transform(parameters.begin() + i + 1, parameters.end(), std::back_inserter(algorithms_to_run),
                               [](const std::string &str) {
                                   int algorithm_number;
                                   try { algorithm_number = std::stoi(str); }
                                   catch (const std::exception &) { return_parameters_error(); }
                                   if (algorithm_number < 0 or algorithm_number > 7) return_parameters_error();
                                   return algorithm_number;
                               });
            }
        }

        return_parameters(algorithms_to_run);

        return algorithms_to_run;
    }

    std::vector<int> parameters_from_standard_input() {
        std::vector<int> algorithms_to_run;

        std::cout << "Provide problem size:\n";
        std::cin >> problem_size;

        std::cout << "Provide number of iterations:\n";
        std::cin >> iterations;

        std::cout << "Choose algorithm(s) by providing specific number (or numbers):\n"
                  << "1 - Random solution" << "\n"
                  << "2 - Brute force" << "\n"
                  << "3 - Random hillclimb" << "\n"
                  << "4 - Deterministic hillclimb" << "\n"
                  << "5 - Tabu search" << "\n"
                  << "6 - Simulated annealing" << "\n"
                  << "7 - Generic algorithm" << "\n"
                  << "0 - All of the above-mentioned" << "\n"
                  << "(Enter \"X\" to stop)\n";

        std::cin.ignore();
        std::string input_line;

        while (true) {
            std::getline(std::cin, input_line);
            if (input_line == "X") {
                break;
            }
            try { algorithms_to_run.push_back(std::stoi(input_line)); }
            catch (const std::exception &) { return_parameters_error(); }
            if (algorithms_to_run.back() < 0 or algorithms_to_run.back() > 7) return_parameters_error();
        }

        return_parameters(algorithms_to_run);

        return algorithms_to_run;
    }

    void return_parameters(std::vector<int> &algorithms_to_run) {

        if (problem_size == 0 or iterations == 0 or algorithms_to_run.empty()) { return_parameters_error(); }

        std::cout << "Problem size: " << problem_size << "\n";
        std::cout << "Iterations: " << iterations << "\n";
        std::cout << "Selected algorithms: ";

        std::sort(algorithms_to_run.begin(), algorithms_to_run.end());
        for (auto a: algorithms_to_run) { std::cout << a << ", "; }
        std::cout << "\n";
    }

    void return_parameters_error() {
        std::cout << "Error! Try to provide parameters once again..."; // TODO: Help
        std::exit(1);
    }

} // mhe