#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <random>
#include <algorithm>

const int left_indentation_size = 24;

// <-- Generator liczb pseudolosowych
std::random_device rd;
std::mt19937 rgen(rd());

// <-- Problem: graf -->
struct graph_t {
    int size;
    std::vector<bool> indicators;
    std::vector<int> vertices;
    std::vector<std::vector<bool>> edges;

    explicit graph_t(int graph_size) {  // TODO Doczytac: explicit, static, [[nodiscard]], const method
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
    o << std::setw(left_indentation_size) << "Graph: "
      << std::setw(vertex_size) << " " << " ";
    for (int i = 0; i < graph.size; i++) {
        if (graph.indicators[i]) o << std::setw(vertex_size) << graph.vertices[i] << " ";
    }
    o << "\n";
    for (int i = 0; i < graph.size; i++) {
        if (graph.indicators[i]) {
            o << std::setw(left_indentation_size) << " "
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
    o << graph << std::setw(left_indentation_size) << "Indicators: " << graph.get_indicators()
      << "\n" << std::setw(left_indentation_size) << "Vertices (ct.): " << graph.get_vertices_ct() << "\n"
      << std::setw(left_indentation_size) << "Edges (ct.): " << graph.get_edges_ct() << "\n"
      << std::setw(left_indentation_size) << "Max clique edges (ct.): " << graph.get_k_edges_ct() << "\n"
      << std::setw(left_indentation_size) << "Goal: " << graph.get_goal() << "\n";
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

graph_t random_solution(graph_t &problem) { // TODO Przypadki z 1 wierzchołkiem (Goal: nan)
    graph_t solution = problem;
    std::uniform_int_distribution<int> distr(0, 1);
    for (int i = 0; i < solution.size; i++) {
        if (!static_cast<bool>(distr(rgen))) {
            solution.flip_indicator(i);
        }
    }
    return solution;
}

graph_t brute_force(graph_t &problem) { //TODO sprawdzic, czy generuja sie wszystkie rozwiazania
    graph_t solution = problem;
    graph_t best_solution = problem;
    int j = 0;
    for (int i = 0; i < solution.size; i++) {
        solution.flip_indicator(i);
        do {
            j++;
            std::cout << j << " " << solution.get_goal() << "\n";
            if (solution.get_goal() >= best_solution.get_goal()) {
                best_solution = solution;
//                std::cout << j << " " << best_solution.get_goal() << "\n";
            }
        } while (std::next_permutation(solution.indicators.begin(), solution.indicators.end()));
    }
    std::cout << j << "\n";
    return best_solution;
}

int main() {
    graph_t graph = graph_t(10);

    print_graph(std::cout, graph);

//    std::cout << brute_force(graph);

    std::cout << "\n" << "* * * Remove vertex * * *" << "\n\n";

    graph_t subgraph = create_subgraph(graph, {2});
    print_graph(std::cout, subgraph);

    std::cout << "\n" << "* * * Add vertex * * *" << "\n\n";

    graph_t subgraph_2 = create_subgraph(subgraph, {2, 3});
    print_graph(std::cout, subgraph_2);

    std::cout << "\n" << "* * * Random solution * * *" << "\n\n";

    graph_t random_subgraph = random_solution(graph);
    print_graph(std::cout, random_subgraph);

    return 0;
}