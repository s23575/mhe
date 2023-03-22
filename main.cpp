#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <map>
#include <iomanip>

using vertex = int;
using vertices = std::vector<int>;
using edge = bool;
using edge_coordinates = std::array<vertex, 2>;
using edges = std::map<edge_coordinates, edge>;

struct graph_t {
    ::vertices vertices;
    ::edges edges;

    explicit graph_t(int vertices_number) {
        vertices = determine_vertices(vertices_number);
        edges = determine_edges(vertices);
    }

    static ::vertices determine_vertices(int vertices_number) {
        ::vertices vertices;
        for (int i = 0; i < vertices_number; i++) {
            vertices.push_back(i);
        }
        return vertices;
    }

    static ::edges determine_edges(::vertices &vs) {
        ::edges edges;
        ::vertices vs_erease_first = vs;
        for (auto first_vertex : vs) {
            vs_erease_first.erase(vs_erease_first.begin());
            for (auto second_vertex : vs_erease_first) {
                edges.insert({{first_vertex, second_vertex}, false});
            }
        }
        return edges;
    };
};

std::ostream &operator<<(std::ostream &o, graph_t g) {
    int char_size = static_cast<int>(std::to_string(g.vertices.size()).length()+1);
    o << std::setw(char_size-1) << " ";
    for (auto v : g.vertices) {
        o << std::setw(char_size) << v;
    }
    o << "\n";
    for (auto v_y : g.vertices) {
        o << std::setw(char_size-1) << v_y;
        for (auto v_x : g.vertices) {
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

using clique = std::vector<vertex>;
using solution = int;

int main()
{
    graph_t g = graph_t(28);
    std::cout << g;
    return 0;
}
