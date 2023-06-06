#include "configuration.h"
#include "printing.h"

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

    int tabu_size;

    std::vector<int> set_parameters_from_command_line(std::vector<std::string> &parameters) {
        std::vector<int> solutions_to_run;

        find_parameter(parameters, "-p", problem_size);
        find_parameter(parameters, "-i", iterations);

        auto parameter_iterator = std::find(parameters.begin(), parameters.end(), "-a");
        if (parameter_iterator != parameters.end()) {
            auto parameter_iterator_tmp = std::find(parameters.begin(), parameters.end(), "-t");
            std::transform(parameter_iterator + 1, parameter_iterator_tmp,
                           std::back_inserter(solutions_to_run),
                           [](const std::string &str) {
                               int solution_number;
                               try { solution_number = std::stoi(str); }
                               catch (const std::exception &) { throw_parameters_error(); }
                               if (solution_number < 0 or solution_number > 7) throw_parameters_error();
                               return solution_number;
                           });
        } else { throw_parameters_error(); }

        find_parameter(parameters, "-t", tabu_size);

        get_parameters(solutions_to_run);

        return solutions_to_run;
    }

    std::vector<int> set_parameters_from_standard_input() {
        std::vector<int> solutions_to_run;

        std::cout << "Provide problem size:\n";
        std::cin >> problem_size;

        std::cout << "\nProvide number of iterations:\n";
        std::cin >> iterations;

        std::cout << "\nChoose solution(s) by providing specific number (or numbers after Enter):\n";
        for (const auto &s: solutions_titles) std::cout << s << "\n";
        std::cout << "(Insert Enter twice to stop)\n";

        std::cin.ignore();
        std::string input_line;

        while (true) {
            std::getline(std::cin, input_line);
            if (input_line.empty()) {
                break;
            }
            try { solutions_to_run.push_back(std::stoi(input_line)); }
            catch (const std::exception &) { throw_parameters_error(); }
            if (solutions_to_run.back() < 0 or solutions_to_run.back() > 7) throw_parameters_error();
        }

        if (std::find(solutions_to_run.begin(), solutions_to_run.end(), 5) != solutions_to_run.end()) {
            std::cout << "Provide tabu size (0 = unlimited size):\n";
            std::cin >> tabu_size;
        }

        get_parameters(solutions_to_run);

        return solutions_to_run;
    }

    void find_parameter(std::vector<std::string> &parameters, std::string &parameter_to_find, int &variable) {
        std::vector<std::string>::iterator parameter_iterator;
        parameter_iterator = std::find(parameters.begin(), parameters.end(), parameter_to_find);
        if (parameter_iterator != parameters.end()) {
            try { variable = std::stoi(parameters[(parameter_iterator - parameters.begin()) + 1]); }
            catch (const std::exception &) { throw_parameters_error(); }
        } else { throw_parameters_error(); }
    }

    void get_parameters(std::vector<int> &solutions_to_run) {

        if (problem_size <= 0 or iterations <= 0 or solutions_to_run.empty() or tabu_size < 0) throw_parameters_error();

        std::sort(solutions_to_run.begin(), solutions_to_run.end());

        print_config(std::cout, solutions_to_run);
    }

    void throw_parameters_error() {
        std::cerr << "Error! Try to provide parameters once again..."; // TODO: Help
        std::exit(1);
    }

} // mhe