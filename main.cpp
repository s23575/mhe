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
    int k_edges_count;
    int edges_count;

    explicit graph_t(int graph_size) {  // Doczytac: explicit, static
        vertices = determine_vertices(graph_size);
        edges = determine_edges(graph_size, edges_count = 0);
        k_edges_count = determine_k_edges_count(graph_size);
    }

    static std::vector<int> determine_vertices(int graph_size) {
        std::vector<int> vertices;
        for (int i = 0; i < graph_size; i++) vertices.push_back(i);
        return vertices;
    }

    static std::vector<std::vector<bool>> determine_edges(int graph_size, int& edges_count) {
        std::uniform_int_distribution<int> distr(0, 1);
        std::vector<std::vector<bool>> edges;
        bool b;
        for (int i = 0; i < graph_size; i++) {
            edges.emplace_back();
            for (int j = 0; j < graph_size; j++) {
                if (j == i) {
                    edges[i].push_back(false);
                } else if (i > j) {
                    edges[i].push_back(edges[j][i]);
                } else {
//                    edges[i].push_back(true);
//                    edges_count++;
                    b = static_cast<int>(distr(rgen));
                    edges[i].push_back(b);
                    if (b == 1) {
                        edges_count++;
                    }
                }
            }
        }
        return edges;
    }

    static int determine_k_edges_count(int graph_size) {
        return (graph_size * (graph_size - 1)) / 2;
    }

    double goal() {
        return (static_cast<int>(vertices.size()) - (k_edges_count - edges_count))
                * 1000
                * ((double)edges_count / (double)k_edges_count);
    }
};

std::ostream &operator<<(std::ostream &o, graph_t g) { // Dopracowac "rysowanie" (std::setw)
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
using clique_t = graph_t;
using solution = int;


int main() {
    graph_t graph = graph_t(5);

    std::cout << graph;
    std::cout << graph.edges_count << "\n";
    std::cout << graph.k_edges_count << "\n";
    std::cout << graph.goal();

    return 0;
}