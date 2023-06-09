#include "configuration.h"
#include "printing.h"
#include "../structures/solution_functions.h"

#include <iostream>

namespace mhe {

    int problem_size;
    int iterations;

    int tabu_size;

    std::vector<int> set_parameters_from_command_line(std::vector<std::string> &parameters) {
        std::vector<int> solutions_to_run;

        if (find_parameter(parameters, "-h") == 1) {
            get_help();
        } else {
            problem_size = find_parameter(parameters, "-p");
            iterations = find_parameter(parameters, "-i");

            auto parameter_iterator = std::find(parameters.begin(), parameters.end(), "-s");
            if (parameter_iterator != parameters.end()) {

                auto parameter_iterator_tmp = std::find_if(parameter_iterator, parameters.end(),
                                                           [](std::string &p) {
                                                               return (p == "-t" or p == "-p" or p == "-i");
                                                           });

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


            if (std::find_if(solutions_to_run.begin(), solutions_to_run.end(),
                             [&](int s) {
                                 return (s == 5 or s == 0);
                             }) != solutions_to_run.end()) {
                tabu_size = find_parameter(parameters, "-t");
            }

            get_parameters(solutions_to_run);
        }
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
        std::cout << "(Insert Enter twice to stop.)\n";

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

        if (std::find_if(solutions_to_run.begin(), solutions_to_run.end(),
                         [&](int s) {
                             return (s == 5 or s == 0);
                         }) != solutions_to_run.end()) {
            std::cout << "Provide tabu size (0 = unlimited size):\n";
            std::cin >> tabu_size;
        }

        get_parameters(solutions_to_run);

        return solutions_to_run;
    }

    int find_parameter(std::vector<std::string> &parameters, const std::string &parameter_to_find) {
        int variable = 0;
        auto parameter_iterator = std::find(parameters.begin(), parameters.end(), parameter_to_find);

        if (parameter_iterator != parameters.end()) {
            if (parameter_to_find == "-h") variable = 1;
            else {
                try { variable = std::stoi(*(parameter_iterator + 1)); }
                catch (const std::exception &) { throw_parameters_error(); }
            }
        } else {
            if (parameter_to_find == "-h") variable = 0;
            else throw_parameters_error();
        }
        return variable;
    }

    void get_parameters(std::vector<int> &solutions_to_run) {

        if (problem_size < 2 or iterations < 1 or solutions_to_run.empty() or tabu_size < 0) throw_parameters_error();

        std::sort(solutions_to_run.begin(), solutions_to_run.end());

        print_config(std::cout, solutions_to_run);
    }

    void throw_parameters_error() {
        std::cerr << "Error! Try to provide parameters once again...";
        std::exit(1);
    }

    void get_help() {
        std::cout << "Provide parameters to run the program - try to find the largest clique in a graph:\n"
                  << "-p" << "\t" << "size of the problem (graph) to solve\n"
                  << "-i" << "\t" << "number of iterations to solve the problem\n"
                  << "-s" << "\t" << "solutions to be applied to the problem:\n";
        for (const auto &s: solutions_titles) std::cout << "\t" << s << "\n";
        std::cout << "-t" << "\t" << "tabu size (if applies)\n";
    }

} // mhe