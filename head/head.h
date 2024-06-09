#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>
#include <set>
#include <memory>
#include <map>
#include <stack>

template<typename Vertex, typename Distance = double>
class Graph {
public:
    struct Edge {
        Vertex from;
        Vertex to;
        Distance distance;

        Edge(const Vertex &from, const Vertex &to, Distance distance)
                : from(from), to(to), distance(distance) {}
    };

private:


    std::unordered_map<Vertex, std::vector<Edge>> adj_list;

public:
    void print_edges() const {
        for (const auto &pair : adj_list) {
            const Vertex &from = pair.first;
            const std::vector<Edge> &edges = pair.second;
            for (const Edge &edge : edges) {
                std::cout << "rebro is " << edge.from << " v " << edge.to << " with distance " << edge.distance << std::endl;
            }
        }
    }
    bool has_vertex(const Vertex &v) const {
        return adj_list.find(v) != adj_list.end();
    }

    void add_vertex(const Vertex &v) {
        adj_list[v];
    }

    bool remove_vertex(const Vertex &v) {
        if (!has_vertex(v)) return false;
        adj_list.erase(v);
        for (auto &pair: adj_list) {
            pair.second.erase(std::remove_if(pair.second.begin(), pair.second.end(),
                                             [&v](const Edge &e) { return e.to == v; }),
                              pair.second.end());
        }
        return true;
    }

    std::vector<Vertex> vertices() const {
        std::vector<Vertex> keys;
        for (const auto &pair: adj_list) {
            keys.push_back(pair.first);
        }
        return keys;
    }

    void add_edge(const Vertex &from, const Vertex &to, const Distance &d) {
        if (d < 0) {
            std::cerr << "Нельзя добавить ребро с отрицательным весом (" << d << ")." << std::endl;
            return;
        }
        adj_list[from].emplace_back(from, to, d);
    }

    bool remove_edge(const Vertex &from, const Vertex &to) {
        if (!has_vertex(from)) return false;
        auto &edges = adj_list[from];
        auto it = std::find_if(edges.begin(), edges.end(), [&to](const Edge &e) { return e.to == to; });
        if (it != edges.end()) {
            edges.erase(it);
            return true;
        }
        return false;
    }

    bool has_edge(const Vertex &from, const Vertex &to) const {
        if (!has_vertex(from)) return false;
        const auto &edges = adj_list.at(from);
        return std::any_of(edges.begin(), edges.end(), [&to](const Edge &e) { return e.to == to; });
    }

    const std::vector<Edge>& edges(const Vertex &vertex) const {

        auto it = adj_list.find(vertex);
        if (it != adj_list.end()) {
            return it->second;
        } else {
            static const std::vector<Edge> empty_vector;
            return empty_vector;
        }
    }


    size_t order() const {
        return adj_list.size();
    }

    size_t degree(const Vertex &v) const {
        if (!has_vertex(v)) return 0;
        return adj_list.at(v).size();
    }
    std::vector<Edge> shortest_path(const Vertex &source, const Vertex &target) const {
        std::map<Vertex, Distance> distances;
        std::map<Vertex, Vertex> predecessors;
        std::priority_queue<std::pair<Distance, Vertex>, std::vector<std::pair<Distance, Vertex>>, std::greater<>> queue;

        for (const auto &node : adj_list) {
            distances[node.first] = std::numeric_limits<Distance>::infinity();
        }
        distances[source] = 0;

        queue.push(std::make_pair(0, source));

        while (!queue.empty()) {
            Vertex current = queue.top().second;
            queue.pop();

            if (current == target) {
                break;
            }

            for (const Edge &edge : edges(current)) {
                Vertex neighbor = edge.to;
                Distance new_dist = distances[current] + edge.distance;
                if (new_dist < distances[neighbor]) {
                    distances[neighbor] = new_dist;
                    predecessors[neighbor] = current;
                    queue.push(std::make_pair(new_dist, neighbor));
                }
            }
        }

        std::vector<Edge> path;
        if (distances[target] == std::numeric_limits<Distance>::infinity()) {
            return path;
        }

        for (Vertex v = target; v != source; v = predecessors[v]) {
            Vertex u = predecessors[v];
            auto it = std::find_if(adj_list.at(u).begin(), adj_list.at(u).end(), [&v](const Edge &e) {
                return e.to == v;
            });
            if (it != adj_list.at(u).end()) {
                path.push_back(*it);
            }
        }

        std::reverse(path.begin(), path.end());
        return path;
    }
    std::vector<Vertex> walk(const Vertex& source)  {
        std::unordered_map<Vertex, bool> visited;
        for (auto const& item: adj_list) {
            visited[item.first] = false;
        }
        std::queue<Vertex> q;
        visited[source] = true;
        q.push(source);

        std::vector<Vertex> result;
        while(!q.empty()) {
            Vertex vertex = q.front();
            q.pop();
            result.push_back(vertex);
            const std::vector<Edge>& edges_list = edges(vertex);
            for (const Edge &i : edges_list) {
                if (!visited[i.to]) {
                    q.push(i.to);
                    visited[i.to] = true;
                }
            }
        }
        return result;
    }


    bool dfs(Vertex v, std::unordered_map<Vertex, bool> &visited, std::unordered_map<Vertex, bool> &recStack) const {
        if(!visited[v]) {
            visited[v] = true;
            recStack[v] = true;
            for(const Edge &edge : adj_list.at(v)) {
                Vertex neighbor = edge.to;
                if (!visited[neighbor] && dfs(neighbor, visited, recStack))
                    return true;
                else if (recStack[neighbor])
                    return true;
            }
        }
        recStack[v] = false;
        return false;
    }
    bool has_cycle() const {
        std::unordered_map<Vertex, bool> visited;
        std::unordered_map<Vertex, bool> recStack;
        for (const auto &node : adj_list) {
            if (dfs(node.first, visited, recStack))
                return true;
        }
        return false;
    }
};

template<typename Vertex, typename Distance>
Vertex find_optimal_storage(Graph<Vertex, Distance>& graph) {
    Distance min_average_distance = std::numeric_limits<Distance>::infinity();
    Vertex optimal_storage_vertex;

    for (const Vertex& vertex : graph.vertices()) {
        Distance total_distance = 0;
        int reachable_vertices = 0;

        for (const Vertex& target : graph.vertices()) {
            if (vertex == target) continue;
            std::vector<typename Graph<Vertex, Distance>::Edge> path = graph.shortest_path(vertex, target);

            for (const auto& edge : path) {
                total_distance += edge.distance;
            }

            reachable_vertices++;
        }

        Distance average_distance = total_distance / reachable_vertices;

        if (average_distance < min_average_distance) {
            min_average_distance = average_distance;
            optimal_storage_vertex = vertex;
        }
    }

    return optimal_storage_vertex;
}

