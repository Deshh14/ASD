#pragma once
#include <iostream>
#include <stdexcept>
#include <climits>
#include "list.h"
#include "Tvector.h"

class Graph {
private:
    Tvector<List<int>> adjacency_list;
    int vertex_count;

public:
    Graph(int vertices);
    Graph(const Tvector<std::pair<int, int>>& edges);
    ~Graph() = default;

    bool is_edge(int from, int to) const;
    int edge(int from, int to) const;
    void add_edge(int from, int to);
    void print() const;
    void print_adjacency_matrix() const;

    Tvector<int> dijkstra(int start) const;
    void print_shortest_paths(int start) const;
};

Graph::Graph(int vertices) : vertex_count(vertices) {
    adjacency_list = Tvector<List<int>>(vertex_count);
}

Graph::Graph(const Tvector<std::pair<int, int>>& edges) {
    int max_vertex = -1;
    for (size_t i = 0; i < edges.size(); ++i) {
        if (edges[i].first > max_vertex) max_vertex = edges[i].first;
        if (edges[i].second > max_vertex) max_vertex = edges[i].second;
    }
    vertex_count = max_vertex + 1;
    adjacency_list = Tvector<List<int>>(vertex_count);
    for (size_t i = 0; i < edges.size(); ++i) {
        add_edge(edges[i].first, edges[i].second);
    }
}

bool Graph::is_edge(int from, int to) const {
    if (from < 0 || from >= vertex_count || to < 0 || to >= vertex_count) {
        return false;
    }
    for (auto it = adjacency_list[from].begin(); it != adjacency_list[from].end(); ++it) {
        if (*it == to) {
            return true;
        }
    }
    return false;
}

int Graph::edge(int from, int to) const {
    if (is_edge(from, to)) {
        return 1;
    }
    return 0;
}

void Graph::add_edge(int from, int to) {
    if (from < 0 || from >= vertex_count || to < 0 || to >= vertex_count) {
        throw std::out_of_range("Vertex index out of range");
    }
    if (from == to) {
        return;
    }
    if (is_edge(from, to)) {
        return;
    }
    adjacency_list[from].push_back(to);
    adjacency_list[to].push_back(from);
}

void Graph::print() const {
    std::cout << "Adjacency list:\n";
    for (int i = 0; i < vertex_count; ++i) {
        std::cout << i << ": ";
        for (auto it = adjacency_list[i].begin(); it != adjacency_list[i].end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }
}

void Graph::print_adjacency_matrix() const {
    std::cout << "Adjacency Matrix:\n";
    std::cout << "   ";
    for (int i = 0; i < vertex_count; ++i) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < vertex_count; ++i) {
        std::cout << i << ": ";
        for (int j = 0; j < vertex_count; ++j) {
            std::cout << edge(i, j) << " ";
        }
        std::cout << std::endl;
    }
}

Tvector<int> Graph::dijkstra(int start) const {
    if (start < 0 || start >= vertex_count) {
        throw std::out_of_range("Start vertex out of range");
    }

    const int INF = INT_MAX;

    Tvector<int> distances(vertex_count);
    for (int i = 0; i < vertex_count; ++i) {
        distances[i] = INF;
    }
    distances[start] = 0;

    Tvector<bool> visited(vertex_count);
    for (int i = 0; i < vertex_count; ++i) {
        visited[i] = false;
    }

    for (int count = 0; count < vertex_count; ++count) {
        int min_distance = INF;
        int min_vertex = -1;

        for (int i = 0; i < vertex_count; ++i) {
            if (!visited[i] && distances[i] < min_distance) {
                min_distance = distances[i];
                min_vertex = i;
            }
        }

        if (min_vertex == -1) break;

        visited[min_vertex] = true;

        for (auto it = adjacency_list[min_vertex].begin();
            it != adjacency_list[min_vertex].end(); ++it) {
            int neighbor = *it;

            if (!visited[neighbor] && distances[min_vertex] != INF) {
                int new_distance = distances[min_vertex] + 1;  
                if (new_distance < distances[neighbor]) {
                    distances[neighbor] = new_distance;
                }
            }
        }
    }

    return distances;
}

void Graph::print_shortest_paths(int start) const {
    Tvector<int> distances = dijkstra(start);

    std::cout << "Shortest paths from vertex " << start << ":\n";
    for (int i = 0; i < vertex_count; ++i) {
        std::cout << "  to " << i << ": ";
        if (distances[i] == INT_MAX) {
            std::cout << "unreachable";
        }
        else {
            std::cout << distances[i];
        }
        std::cout << std::endl;
    }
}