#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <random>
#include <algorithm>

// <-- Generator liczb pseudolosowych
std::random_device rd;
std::mt19937 rgen(rd());

// <-- Problem: graf -->
struct graph_t {
    int size;
    std::vector<bool> indicators;
    std::vector<int> vertices;
    std::vector<std::vector<bool>> edges;
    int indicators_num;
    int k_edges_num{};
    int edges_num{};

    explicit graph_t(int graph_size) {  // TODO Doczytac: explicit, static, [[nodiscard]], const method
        size = graph_size;
        indicators = std::vector<bool>(size, true);
        indicators_num = size;
        this ->
            set_vertices(),
            set_edges(),
            set_edges_num(),
            set_k_edges_num();
    }

    void set_indicator(int i) {
        indicators[i].flip();
    }

    void set_vertices() {
        for (int i = 0; i < size; i++) vertices.push_back(i);
    }

    void set_edges() {
        std::uniform_int_distribution<int> distr(0, 1);
        bool b;
        for (int i = 0; i < size; i++) { // TODO do... while... dopoki nie ma minimalnej liczby krawedzi
            edges.emplace_back();
            for (int j = 0; j < size; j++) {
                if (j == i) edges[i].push_back(false);
                else if (i > j) edges[i].push_back(edges[j][i]);
                else {
                    b = static_cast<int>(distr(rgen));
                    edges[i].push_back(b);
                }
            }
        }
    }

    void set_indicators_num() {
        indicators_num = 0;
        for (auto indicator : indicators) if (indicator) indicators_num++;
    }

    void set_edges_num() {
        edges_num = 0;
        for (int i = 0; i < size; i++) {
            if (indicators[i]) {
                for (int j = 0; j < size; j++) if (indicators[j] && edges[i][j]) edges_num++;
            }
        }
        edges_num = edges_num / 2;
    }

    void set_k_edges_num() {
        k_edges_num = 0;
        k_edges_num = (static_cast<int>(indicators_num) * (static_cast<int>(indicators_num) - 1)) / 2;
    }

    double get_goal() {
        this -> set_indicators_num(),
                set_edges_num(),
                set_k_edges_num();
        return (static_cast<int>(indicators_num) - (k_edges_num - edges_num)) * 1000
               * ((double)edges_num / (double)k_edges_num);
    }

};

std::ostream &operator<<(std::ostream &o, graph_t g) { // TODO Dopracowac "rysowanie" (std::setw, największy wierzchołek)
    int char_size = static_cast<int>(std::to_string(g.size).length() - 1);
    o << std::setw(char_size) << " " << " ";
    for (int i = 0; i < g.size; i++) {
        if (g.indicators[i]) o << std::setw(char_size) << g.vertices[i] << " ";
    }
    o << "\n";
    for (int i = 0; i < g.size; i++) {
        if (g.indicators[i]) {
            o << std::setw(char_size - 1) << g.vertices[i] << " ";
            for (int j = 0; j < g.size; j++) {
                if (g.indicators[j]) std::cout << std::setw(char_size) << g.edges[i][j] << " ";
            }
            o << "\n";
        }
    }
    return o;
}

// <-- Rozwiązanie -->

graph_t random_solution(graph_t &problem) { // TODO Przypadki z 1 wierzchołkiem (Goal: nan)
    graph_t solution = problem;
    std::uniform_int_distribution<int> distr(0, 1);
    for (int i = 0; i < solution.size; i++) {
        if (!static_cast<bool>(distr(rgen))) {
            solution.set_indicator(i);
        }
    }
    return solution;
}

graph_t brute_force (graph_t &problem) { //TODO sprawdzic, czy generuja sie wszystkie rozwiazania
    graph_t solution = problem;
    graph_t best_solution = problem;
    int j = 0;
    for (int i = 0; i < solution.size; i++) {
        solution.indicators[i].flip();
        do {
            j++;
            solution.set_indicators_num();
            solution.set_edges_num();
            solution.set_k_edges_num();
            if (solution.get_goal() >= best_solution.get_goal()) {
                best_solution = solution;
                std::cout << j << " " << best_solution.get_goal() << "\n";
            }
        } while (std::next_permutation(solution.indicators.begin(), solution.indicators.end()));
    }
    std::cout << j << "\n";
    return best_solution;
}



int main() {
    graph_t graph = graph_t(20);

    std::cout << "Graph: \n" << graph; // TODO Drukowanie grafu i informacji o nim
    std::cout << "Indicators: ";
    for (auto indicator : graph.indicators) {
        std::cout << indicator << " ";
    }
    std::cout << "\n";
    std::cout << "Edges count: " << graph.edges_num << "\n";
    std::cout << "Clique edges count: " << graph.k_edges_num << "\n";
    std::cout << "Goal: " << graph.get_goal() << "\n";

    std::cout << brute_force(graph);

//    graph_t subgraph = graph;
//
//    std::cout << "\n" << "* * * Remove vertex * * *" <<  "\n\n";
//
//    subgraph.set_indicator(2);
//
//    std::cout << "Subgraph: \n" << subgraph;
//    std::cout << "Indicators: ";
//    for (auto indicator : subgraph.indicators) {
//        std::cout << indicator << " ";
//    }
//    std::cout << "\n";
//    std::cout << "Edges count: " << subgraph.edges_num << "\n";
//    std::cout << "Clique edges count: " << subgraph.k_edges_num << "\n";
//    std::cout << "Goal: " <<  subgraph.get_goal() << "\n";
//
//    std::cout << "\n" << "* * * Add vertex * * *" <<  "\n\n";
//
//    subgraph.set_indicator(2);
//
//    std::cout << "Subgraph: \n" << subgraph;
//    std::cout << "Indicators: ";
//    for (auto && indicator : subgraph.indicators) {
//        std::cout << indicator << " ";
//    }
//    std::cout << "\n";
//    std::cout << "Edges count: " << subgraph.edges_num << "\n";
//    std::cout << "Clique edges count: " << subgraph.k_edges_num << "\n";
//    std::cout << "Goal: " <<  subgraph.get_goal() << "\n";
//
//    subgraph = random_solution(graph);
//
//    std::cout << "\n" << "* * * Random solution * * *" <<  "\n\n";
//
//    std::cout << "Subgraph: \n" << subgraph;
//    std::cout << "Indicators: ";
//    for (auto indicator : subgraph.indicators) {
//        std::cout << indicator << " ";
//    }
//    std::cout << "\n";
//    std::cout << "Edges count: " << subgraph.edges_num << "\n";
//    std::cout << "Clique edges count: " << subgraph.k_edges_num << "\n";
//    std::cout << "Goal: " << subgraph.get_goal() << "\n";

    return 0;
}