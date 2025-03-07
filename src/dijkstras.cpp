#include "../src/dijkstras.h"


vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous)
{
    // vector<int> distances(G.numVertices, INF);
    // distances[source] = 0;
    // previous.resize(G.numVertices, -1);
    // priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    // pq.push({0, source});
    // while (!pq.empty()) {
    //     auto [d, u] = pq.top();
    //     pq.pop();
    //     if (d > distances[u]) {
    //         continue;
    //     }
    //     for (const auto& e : G[u]) {
    //         int v = e.dst;
    //         int w = e.weight;
    //         if (distances[u] + w < distances[v]) {
    //             distances[v] = distances[u] + w;
    //             previous[v] = u;
    //             pq.push({distances[v], v});
    //         }
    //     }
    // }
    // return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination)
{
    
}

void print_path(const vector<int>& v, int total)
{
    std::cout << "Shortest Path: ";
    for (const auto& i : v) {
        std::cout << i << " ";
    }
    std::cout << "Total: " << total << std::endl;
}