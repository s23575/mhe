#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <random>

// <-- Generator liczb pseudolosowych
std::random_device rd;
std::mt19937 rgen(rd());

// <-- Problem: graf -->
struct graph_t {
    std::vector<int> vertices;
    std::vector<std::vector<bool>> edges;
    std::vector<bool> indicators;
    int k_edges_count;
    int edges_count;

    explicit graph_t(int graph_size) {  // TODO Doczytac: explicit, static, [[nodiscard]], const method
        vertices = determine_vertices(graph_size);
        edges = determine_edges();
        indicators = determine_indicators();
        k_edges_count = determine_k_edges_count();
        edges_count = determine_edges_count();
    }

    static std::vector<int> determine_vertices(int graph_size) {
        std::vector<int> vertices_temp;
        for (int i = 0; i < graph_size; i++) vertices_temp.push_back(i);
        return vertices_temp;
    }

    [[nodiscard]] std::vector<std::vector<bool>> determine_edges() const {
        std::vector<std::vector<bool>> edges_temp;
        std::uniform_int_distribution<int> distr(0, 1);
        bool b;
        for (int i = 0; i < vertices.size(); i++) {
            edges_temp.emplace_back();
            for (int j = 0; j < vertices.size(); j++) {
                if (j == i) {
                    edges_temp[i].push_back(false);
                } else if (i > j) {
                    edges_temp[i].push_back(edges_temp[j][i]);
                } else {
                    b = static_cast<int>(distr(rgen));
                    edges_temp[i].push_back(b);
                }
            }
        }
        return edges_temp;
    }

    [[nodiscard]] std::vector<bool> determine_indicators() const {
        std::vector<bool> indicators_temp;
        for (int i = 0; i < vertices.size(); i++) {
            indicators_temp.push_back(true);
        }
        return indicators_temp;
    }

    [[nodiscard]] int determine_edges_count() const {
        int edges_count_temp = 0;
        for (auto & edge : edges) {
            for (auto && e : edge) {
                if (e) edges_count_temp++;
            }
        }
        return edges_count_temp / 2;
    }

    [[nodiscard]] int determine_k_edges_count() const {
        return (static_cast<int>(vertices.size()) * (static_cast<int>(vertices.size()) - 1)) / 2;
    }

    [[nodiscard]] double goal() const {
        return (static_cast<int>(vertices.size()) - (k_edges_count - edges_count)) * 1000
                * ((double)edges_count / (double)k_edges_count);
    }

    void remove_vertex(int vertex_to_remove) { // TODO Dorobic sprawdzanie, czy vertex istnieje (1)
        int vertex_pos;
        for (int i = 0; i < vertices.size(); i++) {
            if (vertices[i] == vertex_to_remove) {
                vertex_pos = i;
            }
        }

        vertices.erase(vertices.begin() + vertex_pos);
        edges.erase(edges.begin() + vertex_pos);
        for (auto & edge : edges) {
            edge.erase(edge.begin() + vertex_pos);
        }
        indicators[vertex_to_remove] = false;
        k_edges_count = determine_k_edges_count();
        edges_count = determine_edges_count();
    }

    void add_vertex(int vertex_to_add, graph_t& graph) { // TODO Dorobic sprawdzanie, czy vertex istnieje (2)
        for (int i = 0; i < vertices.size(); i++) {
            if (vertices[i] > vertex_to_add) {
                vertices.insert(vertices.begin() + i, vertex_to_add);
                break;
            } else if (i + 1 == vertices.size()) {
                vertices.push_back(vertex_to_add);
                break;
            }
        }
        edges.clear();
        for (int i = 0; i < vertices.size(); i++) {
            edges.emplace_back();
            for (int j = 0; j < vertices.size(); j++) {
                if (j == i) {
                    edges[i].push_back(false);
                } else if (i > j) {
                    edges[i].push_back(edges[j][i]);
                } else {
                    edges[i].push_back(graph.edges[vertices[i]][vertices[j]]);
                }
            }
        }
        indicators[vertex_to_add] = true;
        k_edges_count = determine_k_edges_count();
        edges_count = determine_edges_count();
    }
};

std::ostream &operator<<(std::ostream &o, graph_t g) { // TODO Dopracowac "rysowanie" (std::setw)
    int char_size = static_cast<int>(std::to_string(g.vertices.size()).length() - 1);
    o << std::setw(char_size) << " " << " ";
    for (auto v: g.vertices) {
        o << std::setw(char_size) << v << " ";
    }
    o << "\n";
    for (int i = 0; i < g.vertices.size(); i++) {
        o << std::setw(char_size - 1) << g.vertices[i] << " ";
        for (int j = 0; j < g.vertices.size(); j++) {
            std::cout << std::setw(char_size) << g.edges[i][j] << " ";
        }
        o << "\n";
    }
    return o;
}

// <-- Rozwiązanie -->

graph_t random_solution(graph_t &problem) { // TODO Przypadki z 1 wierzchołkiem (Goal: nan)
    graph_t solution = problem;
    std::uniform_int_distribution<int> distr(0, 1);
    for (int i = 0; i < solution.indicators.size(); i++) {
        if (!static_cast<bool>(distr(rgen))) {
            solution.remove_vertex(i);
        }
    }
    return solution;
}

using clique_t = graph_t;
using solution = int;


int main() {
    graph_t graph = graph_t(6);

    std::cout << "Graph: \n" << graph; // TODO Drukowanie grafu i informacji o nim
    std::cout << "Indicators: ";
    for (auto && indicator : graph.indicators) {
        std::cout << indicator << " ";
    }
    std::cout << "\n";
    std::cout << "Edges count: " << graph.edges_count << "\n";
    std::cout << "Clique edges count: " << graph.k_edges_count << "\n";
    std::cout << "Goal: " <<  graph.goal() << "\n";

//    graph_t subgraph = graph;
//
//    std::cout << "\n" << "* * * Remove vertex * * *" <<  "\n\n";
//
//    subgraph.remove_vertex(0);
//    subgraph.remove_vertex(2);
//    subgraph.remove_vertex(4);
//
//    std::cout << "Subgraph: \n" << subgraph;
//    std::cout << "Indicators: ";
//    for (auto && indicator : subgraph.indicators) {
//        std::cout << indicator << " ";
//    }
//    std::cout << "\n";
//    std::cout << "Edges count: " << subgraph.edges_count << "\n";
//    std::cout << "Clique edges count: " << subgraph.k_edges_count << "\n";
//    std::cout << "Goal: " <<  subgraph.goal() << "\n";
//
//    std::cout << "\n" << "* * * Add vertex * * *" <<  "\n\n";
//
//    subgraph.add_vertex(2, graph);
//
//    std::cout << "Subgraph: \n" << subgraph;
//    std::cout << "Indicators: ";
//    for (auto && indicator : subgraph.indicators) {
//        std::cout << indicator << " ";
//    }
//    std::cout << "\n";
//    std::cout << "Edges count: " << subgraph.edges_count << "\n";
//    std::cout << "Clique edges count: " << subgraph.k_edges_count << "\n";
//    std::cout << "Goal: " <<  subgraph.goal() << "\n";

    graph_t subgraph = random_solution(graph);

    std::cout << "\n" << "* * * Random solution * * *" <<  "\n\n";

    std::cout << "Subgraph: \n" << subgraph;
    std::cout << "Indicators: ";
    for (auto && indicator : subgraph.indicators) {
        std::cout << indicator << " ";
    }
    std::cout << "\n";
    std::cout << "Edges count: " << subgraph.edges_count << "\n";
    std::cout << "Clique edges count: " << subgraph.k_edges_count << "\n";
    std::cout << "Goal: " <<  subgraph.goal() << "\n";

    return 0;
}