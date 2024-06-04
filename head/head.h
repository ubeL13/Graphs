#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>
#include <set>
#include <memory>
#include <map>

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
    struct VertexComparator {
        bool operator()(const std::pair<Distance, Vertex> &a, const std::pair<Distance, Vertex> &b) const {
            return a.first > b.first;
        }
    };

    std::unordered_map<Vertex, std::vector<Edge>> adj_list;

public:
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

    std::vector<Edge> edges(const Vertex &vertex) {
        return adj_list[vertex];
    }
};
