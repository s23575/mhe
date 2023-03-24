#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <map>
#include <iomanip>
#include <random>

// <-- Elementy grafu -->
using vertex = int;
using vertices = std::vector<int>;
using edge = bool;
using edge_coordinates = std::array<vertex, 2>;
using edges = std::map<edge_coordinates, edge>;

using indicator_function_vector = std::vector<bool>;

// <-- Problem: graf -->
struct graph_t {
    ::vertices vertices;
    ::edges edges;

    explicit graph_t(int vertices_number) {
        vertices = determine_vertices(vertices_number);
        edges = determine_edges(vertices);
    }

    explicit graph_t (::vertices vs, ::graph_t& g) {
        vertices = vs;
        edges = determine_edges_subgraph(vertices, g);
    }

    static ::vertices determine_vertices(int vertices_number) {
        ::vertices vertices;
        for (int i = 0; i < vertices_number; i++) vertices.push_back(i);
        return vertices;
    }

    static ::edges determine_edges(::vertices &vs) {
        ::edges edges;
        ::vertices vs_erease_first = vs;
        for (auto first_vertex: vs) {
            vs_erease_first.erase(vs_erease_first.begin());
            for (auto second_vertex: vs_erease_first) {
                edges.insert({{first_vertex, second_vertex}, false});
            }
        }
        return edges;
    };

    static ::edges determine_edges_subgraph(::vertices &vs, graph_t g) {
        ::edges edges;
        ::vertices vs_erease_first = vs;
        for (auto first_vertex: vs) {
            vs_erease_first.erase(vs_erease_first.begin());
            for (auto second_vertex: vs_erease_first) {
                edges.insert({{first_vertex, second_vertex}, g.edges[{first_vertex, second_vertex}]});
            }
        }
        return edges;
    };
};

std::ostream &operator<<(std::ostream &o, graph_t g) {
    int char_size = static_cast<int>(std::to_string(g.vertices.size()).length() + 1);
    o << std::setw(char_size - 1) << " ";
    for (auto v: g.vertices) {
        o << std::setw(char_size) << v;
    }
    o << "\n";
    for (auto v_y: g.vertices) {
        o << std::setw(char_size - 1) << v_y;
        for (auto v_x: g.vertices) {
            if (g.edges.count({v_x, v_y}) == 1) {
                std::cout << std::setw(char_size) << g.edges[{v_x, v_y}];
            } else if (g.edges.count({v_y, v_x}) == 1) {
                std::cout << std::setw(char_size) << g.edges[{v_y, v_x}];
            } else {
                std::cout << std::setw(char_size) << "0";
            }
        }
        o << "\n";
    }
    return o;
}

// <-- Rozwiązanie -->
using clique_t = graph_t;
using solution = int;

// <-- Generator liczb pseudolosowych

std::random_device rd;
std::mt19937 rgen(rd());

int main() {
    graph_t graph = graph_t(4);

    graph.edges[{0, 2}] = 1;
    graph.edges[{0, 1}] = 1;
    graph.edges[{1, 2}] = 1;
    graph.edges[{2, 3}] = 1;

    std::cout << graph << std::endl;

    indicator_function_vector ind_func_vect;
    vertices subgraph_vertices;
    std::uniform_int_distribution<int> dist(0, 1);
    int vert_numb = 0;
    while (vert_numb < 2) {
        vert_numb = 0;
        ind_func_vect.clear();
        subgraph_vertices.clear();
        for (int i = 0; i < graph.vertices.size(); i++) {
            ind_func_vect.push_back(static_cast<bool>(dist(rgen)));
            if (ind_func_vect.back() == 1) {
                subgraph_vertices.push_back(i);
                vert_numb++;
            }
        }
    }

    for (int i = 0; i < ind_func_vect.size(); i++) {
        std::cout << ind_func_vect[i] << " | " << graph.vertices[i] << std::endl;
    }

    for (int i = 0; i < subgraph_vertices.size(); i++) {
        std::cout << subgraph_vertices[i] << " ";
    }
    std::cout << std::endl << std::endl;

    graph_t subgraph = graph_t(subgraph_vertices, graph);
    std::cout << subgraph;

    return 0;
}
