#include "configuration.h"
#include "printing.h"
#include "../structures/solution_functions.h"

#include <iostream>

namespace mhe {

    int problem_size;
    int iterations;
    std::string filename;

    int tabu_size;
    int temp_func;
    int terminal_opt;
    int crossover_opt;
    int mutation_bit_num;

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


            if (get_options_for_solution(solutions_to_run, 5)) {
                tabu_size = find_parameter(parameters, "-t");
            }

            if (get_options_for_solution(solutions_to_run, 6)) {
                temp_func = find_parameter(parameters, "-f");
            }

            if (get_options_for_solution(solutions_to_run, 7)) {
                terminal_opt = find_parameter(parameters, "-e");
            }

            if (get_options_for_solution(solutions_to_run, 7)) {
                crossover_opt = find_parameter(parameters, "-c");
            }

            if (get_options_for_solution(solutions_to_run, 7)) {
                mutation_bit_num = find_parameter(parameters, "-m");
            }

            get_parameters(solutions_to_run);
        }
        return solutions_to_run;
    }

    std::vector<int> set_parameters_from_standard_input() {
        std::vector<int> solutions_to_run;
        std::string input_line;

        std::cout << "Load problem from file (provide filename or insert enter to skip):\n";
        std::getline(std::cin, input_line);
        filename = input_line;

        if (filename.empty()) {
            std::cout << "Provide problem size:\n";
            std::cin >> problem_size;
        }

        std::cout << "\nProvide number of iterations:\n";
        std::cin >> iterations;

        std::cout << "\nChoose solution(s) by providing specific number (or numbers after Enter):\n";
        for (const auto &s: solutions_titles) std::cout << s << "\n";
        std::cout << "(Insert Enter twice to stop.)\n";

        std::cin.ignore();

        while (true) {
            std::getline(std::cin, input_line);
            if (input_line.empty()) {
                break;
            }
            try { solutions_to_run.push_back(std::stoi(input_line)); }
            catch (const std::exception &) { throw_parameters_error(); }
            if (solutions_to_run.back() < 0 or solutions_to_run.back() > 7) throw_parameters_error();
        }

        if (get_options_for_solution(solutions_to_run, 5)) {
            std::cout << "\nProvide tabu size for tabu algorithm: \n"
                      << "0\t- unlimited size,\n"
                      << "other\t- (value) limited size\n";
            std::cin >> tabu_size;
        }

        if (get_options_for_solution(solutions_to_run, 6)) {
            std::cout << "\nProvide temperature function for simulated annealing: \n"
                      << "0\t- ( 1000.0 / k ),\n"
                      << "other\t- 1 / ln(k)\n";
            std::cin >> temp_func;
        }

        if (get_options_for_solution(solutions_to_run, 7)) {
            std::cout << "\nProvide terminal condition for genetic algorithm: \n"
                      << "0\t- iterations,\n"
                      << "other\t- good enough score (max score / value)\n";
            std::cin >> terminal_opt;
        }

        if (get_options_for_solution(solutions_to_run, 7)) {
            std::cout << "\nProvide crossover method for genetic algorithm: \n"
                      << "0\t- one point crossover, in middle,\n"
                      << "other\t- crossover of random alleles pairs\n";
            std::cin >> crossover_opt;
        }

        if (get_options_for_solution(solutions_to_run, 7)) {
            std::cout << "\nProvide number of alleles to change (randomly) for genetic algorithm: \n";
            std::cin >> mutation_bit_num;
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

        if ((problem_size < 2 and filename.empty()) or iterations < 1 or solutions_to_run.empty() or
            tabu_size < 0)
            throw_parameters_error();

        std::sort(solutions_to_run.begin(), solutions_to_run.end());

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
        std::cout << "-t" << "\t" << "tabu size (if applies)\n"
                  << "-f" << "\t" << "temperature function for simulated annealing (if applies):\n"
                  << "\t0\t- 1000.0 / k,\n"
                  << "\tother\t- 1 / ln(k)\n"
                  << "-e" << "\t" << "terminal condition for genetic algorithm (if applies):\n"
                  << "\t0\t- iterations,\n"
                  << "\tother\t- good enough score (max score / value)\n"
                  << "-c" << "\t" << "crossover method for genetic algorithm (if applies):\n"
                  << "\t0\t- one point crossover, in middle,\n"
                  << "\tother\t- crossover of random alleles pairs\n"
                  << "-m" << "\t" << "number of alleles to change (randomly) for genetic algorithm (if applies)\n";
    }

    bool get_options_for_solution(const std::vector<int> &solutions_to_run, const int &sol) {
        return (std::find_if(solutions_to_run.begin(), solutions_to_run.end(),
                             [&](int s) {
                                 return (s == sol or s == 0);
                             }) != solutions_to_run.end());
    }
} // mhe