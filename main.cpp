#include <iostream>
#include "head.h"

int main() {
    setlocale(LC_ALL, "Russian");
    Graph<char> graph;

    graph.add_vertex('A');
    graph.add_vertex('B');
    graph.add_vertex('C');
    graph.add_vertex('D');
    graph.add_vertex('E');

    std::cout << "Vertices added." << std::endl;

    std::cout << "Graph has vertex 'A': " << graph.has_vertex('A') << std::endl;
    std::cout << "Graph has vertex 'Z': " << graph.has_vertex('Z') << std::endl;

    graph.add_edge('A', 'B', 1.0);
    graph.add_edge('A', 'C', 4.0);
    graph.add_edge('B', 'C', 2.0);
    graph.add_edge('B', 'D', 5.0);
    graph.add_edge('C', 'D', 1.0);
    graph.add_edge('D', 'E', 3.0);

    std::cout << "Edges added." << std::endl;

    std::cout << "Graph has edge from 'A' to 'B': " << graph.has_edge('A', 'B') << std::endl;
    std::cout << "Graph has edge from 'A' to 'E': " << graph.has_edge('A', 'E') << std::endl;

    std::cout << "Order of graph: " << graph.order() << std::endl;
    std::cout << "Degree of vertex 'A': " << graph.degree('A') << std::endl;

    graph.remove_edge('A', 'B');
    graph.remove_vertex('E');

    std::cout << "Edge from 'A' to 'B' and vertex 'E' removed." << std::endl;

    std::cout << "Order of graph after removals: " << graph.order() << std::endl;
    std::cout << "Degree of vertex 'A' after removals: " << graph.degree('A') << std::endl;


    char startVertex = 'A';
    char endVertex = 'D';

    std::vector<Graph<char>::Edge> path = graph.shortest_path(startVertex, endVertex);

    std::cout << "Shortest path from " << startVertex << " to " << endVertex << ":" << std::endl;
    for (const auto& edge : path) {
        std::cout << edge.from << " -> " << edge.to << " (Distance: " << edge.distance << ")" << std::endl;
    }
    char optimal_storage = find_optimal_storage(graph);
    std::cout << "Optimal storage location is at vertex: " << optimal_storage << std::endl;

    std::cout<<"/////////////////////////////////////////////////////////////////////"<< std::endl;
    Graph<int, double> graph2;


    graph2.add_vertex(1);
    graph2.add_vertex(2);
    graph2.add_vertex(3);
    graph2.add_vertex(4);

    graph2.add_edge(1, 2, 1.0);
    graph2.add_edge(2, 3, 1.0);
    graph2.add_edge(3, 1, 1.0);
    graph2.add_edge(4, 2, 1.0);
    graph2.add_edge(3, 4, 1.0);


    if (graph2.has_cycle()) {
        std::cout << "The graph contains cycles." << std::endl;
    } else {
        std::cout << "The graph does not contain cycles." << std::endl;
    }
    graph2.remove_edge(3, 1);
    graph2.print_edges();

    if (graph2.has_cycle()) {
        std::cout << "The graph contains cycles." << std::endl;
    } else {
        std::cout << "The graph does not contain cycles." << std::endl;
    }
    graph2.remove_edge(2, 3);
    graph2.print_edges();

    if (graph2.has_cycle()) {
        std::cout << "The graph contains cycles." << std::endl;
    } else {
        std::cout << "The graph does not contain cycles." << std::endl;
    }
    graph2.add_vertex(5);
    graph2.add_edge(5, 3, 1.0);
    graph2.add_edge(5, 4, 1.0);
    if (graph2.has_cycle()) {
        std::cout << "The graph contains cycles." << std::endl;
    } else {
        std::cout << "The graph does not contain cycles." << std::endl;
    }
    graph2.add_edge(3, 5, 1.0);
    if (graph2.has_cycle()) {
        std::cout << "The graph contains cycles." << std::endl;
    } else {
        std::cout << "The graph does not contain cycles." << std::endl;
    }
    Graph<int> graph3;
    graph3.add_edge(1, 2, 1);
    graph3.add_edge(1, 3, 1);
    graph3.add_edge(2, 4, 1);
    graph3.add_edge(2, 5, 1);

    std::vector<int> visitedOrder = graph3.walk(1);
    for(int v : visitedOrder) {
        std::cout << v << ' ';
    }

    return 0;
}