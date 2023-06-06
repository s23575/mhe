#include "configuration.h"

#include <iostream>

namespace mhe {

    int problem_size;
    int iterations;

    std::vector<std::string> solutions_titles = {
            "0 - All of the listed",
            "1 - Random solution",
            "2 - Brute force",
            "3 - Random hillclimb",
            "4 - Deterministic hillclimb",
            "5 - Tabu search",
            "6 - Simulated annealing",
            "7 - Generic algorithm"
    };

    std::vector<int> set_parameters_from_command_line(std::vector<std::string> &parameters) {
        std::vector<int> solutions_to_run;

        for (int i = 0; i < parameters.size(); i++) {

            if (parameters[i] == "-p") {
                try { problem_size = std::stoi(parameters[i + 1]); }
                catch (const std::exception &) { throw_parameters_error(); }

            } else if (parameters[i] == "-i") {
                try { iterations = std::stoi(parameters[i + 1]); }
                catch (const std::exception &) { throw_parameters_error(); }

            } else if (parameters[i] == "-a") {
                std::transform(parameters.begin() + i + 1, parameters.end(), std::back_inserter(solutions_to_run),
                               [](const std::string &str) {
                                   int algorithm_number;
                                   try { algorithm_number = std::stoi(str); }
                                   catch (const std::exception &) { throw_parameters_error(); }
                                   if (algorithm_number < 0 or algorithm_number > 7) throw_parameters_error();
                                   return algorithm_number;
                               });
            }
        }

        get_parameters(solutions_to_run);

        return solutions_to_run;
    }

    std::vector<int> set_parameters_from_standard_input() {
        std::vector<int> solutions_to_run;

        std::cout << "Provide problem size:\n";
        std::cin >> problem_size;

        std::cout << "Provide number of iterations:\n";
        std::cin >> iterations;

        std::cout << "Choose solution(s) by providing specific number (or numbers):\n";
        for (const auto &s: solutions_titles) std::cout << s << "\n";
        std::cout << "(Enter \"X\" or \"x\" to stop)\n";

        std::cin.ignore();
        std::string input_line;

        while (true) {
            std::getline(std::cin, input_line);
            if (input_line == "X" or input_line == "x") {
                break;
            }
            try { solutions_to_run.push_back(std::stoi(input_line)); }
            catch (const std::exception &) { throw_parameters_error(); }
            if (solutions_to_run.back() < 0 or solutions_to_run.back() > 7) throw_parameters_error();
        }

        get_parameters(solutions_to_run);

        return solutions_to_run;
    }

    void get_parameters(std::vector<int> &solutions_to_run) {

        if (problem_size == 0 or iterations == 0 or solutions_to_run.empty()) { throw_parameters_error(); }

        std::cout << "\n" << "* * * Configuration * * *" << "\n\n"
                  << "Problem size: " << problem_size << "\n"
                  << "Iterations: " << iterations << "\n"
                  << "Selected solution: \n";

        std::sort(solutions_to_run.begin(), solutions_to_run.end());
        for (auto solution_num: solutions_to_run) {
            std::cout << solutions_titles[solution_num] << "\n";
        }
    }

    void throw_parameters_error() {
        std::cout << "Error! Try to provide parameters once again..."; // TODO: Help
        std::exit(1);
    }

} // mhe