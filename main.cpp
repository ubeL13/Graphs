#include <iostream>
#include "head.h"

int main() {
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

    return 0;
}