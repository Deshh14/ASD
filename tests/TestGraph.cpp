#include <gtest/gtest.h>
#include "Graph.h"

TEST(GraphTest, ConstructorByVertices) {
    Graph g(5);

    EXPECT_FALSE(g.is_edge(0, 1));
    EXPECT_FALSE(g.is_edge(2, 3));
    EXPECT_EQ(g.edge(0, 1), 0);
}

TEST(GraphTest, ConstructorByEdges) {
    Tvector<std::pair<int, int>> edges;
    edges.push_back(std::make_pair(2, 1));
    edges.push_back(std::make_pair(3, 4));
    edges.push_back(std::make_pair(2, 3));

    Graph g(edges);

    EXPECT_TRUE(g.is_edge(2, 1));
    EXPECT_TRUE(g.is_edge(3, 4));
    EXPECT_TRUE(g.is_edge(2, 3));
    EXPECT_FALSE(g.is_edge(1, 4));
}

TEST(GraphTest, AddEdge) {
    Graph g(5);

    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 3);

    EXPECT_TRUE(g.is_edge(0, 1));
    EXPECT_TRUE(g.is_edge(1, 0));  
    EXPECT_TRUE(g.is_edge(1, 2));
    EXPECT_TRUE(g.is_edge(2, 3));
    EXPECT_FALSE(g.is_edge(0, 3));
    EXPECT_FALSE(g.is_edge(0, 2));

    EXPECT_EQ(g.edge(0, 1), 1);
    EXPECT_EQ(g.edge(0, 3), 0);
}

TEST(GraphTest, EdgeMethod) {
    Graph g(4);

    g.add_edge(0, 1);
    g.add_edge(1, 2);

    EXPECT_EQ(g.edge(0, 1), 1);
    EXPECT_EQ(g.edge(1, 0), 1);
    EXPECT_EQ(g.edge(0, 2), 0);
}

TEST(GraphTest, IsEdgeMethod) {
    Graph g(4);

    g.add_edge(0, 1);
    g.add_edge(2, 3);

    EXPECT_TRUE(g.is_edge(0, 1));
    EXPECT_TRUE(g.is_edge(1, 0));
    EXPECT_TRUE(g.is_edge(2, 3));
    EXPECT_FALSE(g.is_edge(0, 2));
}

TEST(GraphTest, DuplicateEdges) {
    Graph g(5);

    g.add_edge(0, 1);
    g.add_edge(0, 1);  
    g.add_edge(1, 0);  

    EXPECT_TRUE(g.is_edge(0, 1));
    EXPECT_EQ(g.edge(0, 1), 1);
}

TEST(GraphTest, InvalidVertices) {
    Graph g(5);

    EXPECT_FALSE(g.is_edge(-1, 2));
    EXPECT_FALSE(g.is_edge(0, 10));
    EXPECT_FALSE(g.is_edge(5, 3));
    EXPECT_EQ(g.edge(-1, 2), 0);
    EXPECT_EQ(g.edge(0, 10), 0);
}

TEST(GraphTest, AddEdgeExceptions) {
    Graph g(5);

    EXPECT_THROW(g.add_edge(-1, 2), std::out_of_range);
    EXPECT_THROW(g.add_edge(0, 10), std::out_of_range);
    EXPECT_THROW(g.add_edge(5, 3), std::out_of_range);
}

TEST(GraphTest, ExampleFromTask) {
    Tvector<std::pair<int, int>> edges;
    edges.push_back(std::make_pair(2, 1));
    edges.push_back(std::make_pair(3, 4));
    edges.push_back(std::make_pair(2, 3));
    edges.push_back(std::make_pair(2, 5));
    edges.push_back(std::make_pair(1, 5));

    Graph g(edges);

    std::cout << "\n=== Example from task ===\n";
    g.print();
    std::cout << "\n";
    g.print_adjacency_matrix();

    EXPECT_TRUE(g.is_edge(2, 1));
    EXPECT_TRUE(g.is_edge(3, 4));
    EXPECT_TRUE(g.is_edge(2, 3));
    EXPECT_TRUE(g.is_edge(2, 5));
    EXPECT_TRUE(g.is_edge(1, 5));

    EXPECT_FALSE(g.is_edge(1, 3));
    EXPECT_FALSE(g.is_edge(1, 4));
    EXPECT_FALSE(g.is_edge(3, 5));
    EXPECT_FALSE(g.is_edge(0, 1)); 

    EXPECT_EQ(g.edge(2, 1), 1);
    EXPECT_EQ(g.edge(1, 3), 0);
}

// Тест алгоритма Дейкстры на простом графе
TEST(GraphDijkstraTest, SimplePath) {
    Graph g(4);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 3);

    Tvector<int> distances = g.dijkstra(0);

    EXPECT_EQ(distances[0], 0);
    EXPECT_EQ(distances[1], 1);
    EXPECT_EQ(distances[2], 2);
    EXPECT_EQ(distances[3], 3);
}

// Тест на графе из задания
TEST(GraphDijkstraTest, ExampleGraph) {
    Tvector<std::pair<int, int>> edges;
    edges.push_back(std::make_pair(2, 1));
    edges.push_back(std::make_pair(3, 4));
    edges.push_back(std::make_pair(2, 3));
    edges.push_back(std::make_pair(2, 5));
    edges.push_back(std::make_pair(1, 5));

    Graph g(edges);

    Tvector<int> distances = g.dijkstra(4);

    EXPECT_EQ(distances[4], 0);  
    EXPECT_EQ(distances[3], 1);  
    EXPECT_EQ(distances[2], 2);  
    EXPECT_EQ(distances[1], 3);  
    EXPECT_EQ(distances[5], 3);  
    EXPECT_EQ(distances[0], INT_MAX);  
}

// Тест недостижимых вершин
TEST(GraphDijkstraTest, UnreachableVertices) {
    Graph g(6);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    Tvector<int> distances = g.dijkstra(0);

    EXPECT_EQ(distances[0], 0);
    EXPECT_EQ(distances[1], 1);
    EXPECT_EQ(distances[2], 2);
    EXPECT_EQ(distances[3], INT_MAX);
    EXPECT_EQ(distances[4], INT_MAX);
    EXPECT_EQ(distances[5], INT_MAX);
}