#include <iostream>
#include "head.h"

int main() {
    // Создание графа
    Graph<char> graph;

    // Добавление вершин
    graph.add_vertex('A');
    graph.add_vertex('B');
    graph.add_vertex('C');
    graph.add_vertex('D');
    graph.add_vertex('E');

    std::cout << "Vertices added." << std::endl;

    // Проверка наличия вершины
    std::cout << "Graph has vertex 'A': " << graph.has_vertex('A') << std::endl;
    std::cout << "Graph has vertex 'Z': " << graph.has_vertex('Z') << std::endl;

    // Добавление ребер
    graph.add_edge('A', 'B', 1.0);
    graph.add_edge('A', 'C', 4.0);
    graph.add_edge('B', 'C', 2.0);
    graph.add_edge('B', 'D', 5.0);
    graph.add_edge('C', 'D', 1.0);
    graph.add_edge('D', 'E', 3.0);

    std::cout << "Edges added." << std::endl;

    // Проверка наличия ребра
    std::cout << "Graph has edge from 'A' to 'B': " << graph.has_edge('A', 'B') << std::endl;
    std::cout << "Graph has edge from 'A' to 'E': " << graph.has_edge('A', 'E') << std::endl;

    return 0;
}