#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <random>
#include <algorithm>

const int left_indentation_size = 24;
const auto left_indentation = std::setw(left_indentation_size);

const int iterations = 10486;
const int problem_size = 20;

std::random_device rd;
std::mt19937 rgen(rd());

// <-- Problem: graf -->

struct graph_t {
    int size;
    std::vector<bool> indicators;
    std::vector<int> vertices;
    std::vector<std::vector<bool>> edges;

    explicit graph_t(int graph_size) {  // TODO Doczytac: explicit
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
        } while (get_edges_ct() < (size - 1));
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

graph_t create_subgraph(graph_t &graph, const std::vector<int> &indicators) {
    graph_t subgraph = graph;
    for (auto indicator: indicators) {
        subgraph.flip_indicator(indicator);
    }
    return subgraph;
}

// <-- Rozwiązanie -->

graph_t random_solution(graph_t &problem) {
    graph_t solution = problem;
    std::uniform_int_distribution<int> distr(0, 1);
    for (int i = 0; i < solution.size; i++) {
        if (!static_cast<bool>(distr(rgen))) {
            solution.flip_indicator(i);
        }
    }
    return solution;
}

graph_t brute_force(graph_t &problem) {
    graph_t solution = problem;
    graph_t best_solution = problem;
    int j = 0;
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

graph_t random_modify(graph_t &problem) {
    std::uniform_int_distribution<int> distr(0, problem.size - 1);
    int a = distr(rgen);
    graph_t randomly_modified_solution = problem;
    randomly_modified_solution.flip_indicator(a);
    return randomly_modified_solution;
}

graph_t random_hillclimb(graph_t &problem) {
    graph_t solution = problem;
    graph_t best_solution = problem;
    for (int i = 0; i < iterations; i++) {
        solution = random_modify(solution);
        if (solution.get_goal() >= best_solution.get_goal()) {
            best_solution = solution;
        }
    }
    return best_solution;
}

int main() {

    std::cout << "\n" << "* * * Problem * * *" << "\n\n";
    graph_t graph = graph_t(problem_size);
    print_graph(std::cout, graph);

    std::cout << "\n" << "* * * Brute force * * *" << "\n\n";
    graph_t solution = brute_force(graph);
    print_graph(std::cout, solution);

    std::cout << "\n" << "* * * Random hillclimb * * *" << "\n\n";
    solution = random_hillclimb(graph);
    print_graph(std::cout, solution);

//    std::cout << "\n" << "* * * Random solution * * *" << "\n\n";
//    solution = random_solution(graph);
//    print_graph(std::cout, solution);

    return 0;
}