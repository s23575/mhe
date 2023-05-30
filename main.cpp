#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <iomanip>
#include <random>
#include <algorithm>
#include <list>

// TODO Uporządkować, kiedy argument przez referencję, a kiedy przez kopię

const int left_indentation_size = 24;
const auto left_indentation = std::setw(left_indentation_size);

const int iterations = 1024;
const int problem_size = 10;

std::random_device rd;
std::mt19937 rgen(rd());

// <-- Problem: graf -->

struct graph_t {    // TODO Przenieść do osobonego pliku
    int size;
    std::vector<bool> indicators;
    std::vector<int> vertices;
    std::vector<std::vector<bool>> edges;

    explicit graph_t(int graph_size) {  // TODO Doczytać: explicit
        size = graph_size;
        indicators = std::vector<bool>(size, true);
        this->
                set_vertices(),
                set_edges();
    }

    void set_vertices() {
        for (int i = 0; i < size; i++) vertices.push_back(i);
    }

    void set_edges() {
        std::uniform_int_distribution<int> distr(0, 1);
        edges.resize(size, std::vector<bool>(size));
        do {
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    if (j == i) edges[i][j] = false;
                    else if (i > j) edges[i][j] = edges[j][i];
                    else edges[i][j] = static_cast<bool>(distr(rgen));
                }
            }
//        } while (get_edges_ct() < (size - 1));
        } while (get_edges_ct() < get_k_edges_ct() * 3 / 4);
    }

    int get_edges_ct() {
        int edges_ct = 0;
        for (int i = 0; i < size; i++) {
            if (indicators[i]) {
                for (int j = 0; j < size; j++) if (indicators[j] && edges[i][j]) edges_ct++;
            }
        }
        return edges_ct / 2;
    }

    int get_k_edges_ct() {
        int vertices_ct = get_vertices_ct();
        return (static_cast<int>(vertices_ct) * (static_cast<int>(vertices_ct) - 1)) / 2;
    }

    int get_vertices_ct() {
        int vertices_ct = 0;
        for (auto indicator: indicators) if (indicator) vertices_ct++;
        return vertices_ct;
    }

    std::string get_indicators() {
        std::string s;
        for (auto indicator: indicators) s += to_string(indicator) + " ";
        return s;
    }

    void flip_indicator(int i) {
        indicators[i].flip();
    }

    double get_goal() {
        int edges_ct = get_edges_ct();
        int k_edges_ct = get_k_edges_ct();
        return (static_cast<int>(get_vertices_ct()) - (k_edges_ct - edges_ct)) * 1000
               * ((double) edges_ct / (double) k_edges_ct);
    }
};

// <-- Drukowanie -->

std::ostream &operator<<(std::ostream &o, const graph_t &graph) {
    int vertex_size = static_cast<int>(std::to_string(graph.size - 1).length());
    o << left_indentation << "Graph: "
      << std::setw(vertex_size) << " " << " ";
    for (int i = 0; i < graph.size; i++) {
        if (graph.indicators[i]) o << std::setw(vertex_size) << graph.vertices[i] << " ";
    }
    o << "\n";
    for (int i = 0; i < graph.size; i++) {
        if (graph.indicators[i]) {
            o << left_indentation << " "
              << std::setw(vertex_size) << graph.vertices[i] << " ";
            for (int j = 0; j < graph.size; j++) {
                if (graph.indicators[j]) std::cout << std::setw(vertex_size) << graph.edges[i][j] << " ";
            }
            o << "\n";
        }
    }
    return o;
}

std::ostream &print_graph(std::ostream &o, graph_t &graph) {
    o << graph << left_indentation << "Indicators: " << graph.get_indicators()
      << "\n" << left_indentation << "Vertices (ct.): " << graph.get_vertices_ct() << "\n"
      << left_indentation << "Edges (ct.): " << graph.get_edges_ct() << "\n"
      << left_indentation << "Max clique edges (ct.): " << graph.get_k_edges_ct() << "\n"
      << left_indentation << "Goal: " << graph.get_goal() << "\n";
    return o;
}

graph_t create_subgraph(graph_t &graph, const std::vector<int> &subgraph_indicators) {
    graph_t subgraph = graph;
    for (auto subgraph_indicator : subgraph_indicators) {
        subgraph.flip_indicator(subgraph_indicator);
    }
    return subgraph;
}

// <-- Rozwiązanie -->

// <-- <-- Losowe rozwiązanie

graph_t random_solution(graph_t problem) {
    graph_t solution = std::move(problem);
    std::uniform_int_distribution<int> distr(0, 1);
    for (int i = 0; i < solution.size; i++) {
        if (!static_cast<bool>(distr(rgen))) {
            solution.flip_indicator(i);
        }
    }
    return solution;
}

// <-- <-- Brutalna siła

graph_t brute_force(graph_t problem) {
    graph_t solution = std::move(problem);
    graph_t best_solution = solution;
    std::fill(solution.indicators.begin(), solution.indicators.end(), true);
    for (int i = 0; i < solution.size; i++) {
        solution.flip_indicator(i);
        do {
            if (solution.get_goal() >= best_solution.get_goal()) {
                best_solution = solution;
            }
        } while (std::next_permutation(solution.indicators.begin(), solution.indicators.end()));
    }
    return best_solution;
}

// <-- <-- Algorytm wspinaczkowy (losowy)

void random_modify(graph_t &current_solution) {
    std::uniform_int_distribution<int> distr(0, current_solution.size - 1);
    int a = distr(rgen);
    current_solution.flip_indicator(a); // Zamiana tylko dodanich wskaźników?
}

graph_t hillclimb_random(graph_t problem) {
    graph_t solution = std::move(problem);
    graph_t best_solution = solution;
    for (int i = 0; i < iterations; i++) {
        random_modify(solution);
        if (solution.get_goal() >= best_solution.get_goal()) {
            best_solution = solution;
        }
    }
    return best_solution;
}

// <-- <-- Algorytm wspinaczkowy (deterministyczny)

std::vector<graph_t> generate_neighbourhood(graph_t &current_solution) {
    std::vector<graph_t> neighbourhood;
    for (int i = 0; i < current_solution.size; i++) {
        graph_t neighbour = current_solution;
        neighbour.flip_indicator(i);
        neighbourhood.push_back(neighbour);
    }
    return neighbourhood;
};

graph_t best_neighbour(graph_t &current_solution) {
    std::vector<graph_t> neighbourhood = generate_neighbourhood(current_solution);
    return *std::max_element(neighbourhood.begin(), neighbourhood.end(),
                             [](auto l, auto r) { return l.get_goal() < r.get_goal(); });
}

graph_t hillclimb_deterministic(graph_t problem) {
    graph_t solution = std::move(problem);
    graph_t best_solution = solution;
    for (int i = 0; i < iterations; i++) {
        solution = best_neighbour(solution);
        if (solution.get_goal() >= best_solution.get_goal()) {
            best_solution = solution;
        }
    }
    return best_solution;
}

// <-- <-- Algorytm tabu (deterministyczny)

int main() {

    std::cout << "\n" << "* * * Problem * * *" << "\n\n";
    graph_t problem = graph_t(problem_size);
    print_graph(std::cout, problem);

    std::cout << "\n" << "* * * Random solution * * *" << "\n\n";
    graph_t random_sol = random_solution(problem);
    print_graph(std::cout, random_sol);

    std::cout << "\n" << "* * * Brute force * * *" << "\n\n";
    graph_t solution = brute_force(random_sol);
    print_graph(std::cout, solution);

    std::cout << "\n" << "* * * Random hillclimb * * *" << "\n\n";
    solution = hillclimb_random(random_sol);
    print_graph(std::cout, solution);

    std::cout << "\n" << "* * * Deterministic hillclimb * * *" << "\n\n";
    solution = hillclimb_deterministic(random_sol);
    print_graph(std::cout, solution);

    return 0;
}