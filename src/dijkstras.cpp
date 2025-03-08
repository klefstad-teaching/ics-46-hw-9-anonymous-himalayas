#include "dijkstras.h"


vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous)
{
    /*
    n = graph.adjacencyList.size()


    graph.distance.resize(n, INT_MAX)

    graph.previous.resize(n, -1)

    graph.visited.resize(n, false)


    priorityQueue pq

    pq.push(Node(source, 0))

    graph.distance[source] = 0


    while !pq.empty():

        current = pq.pop_top()


        u = current.vertex


        if graph.visited[u]:

            continue


        graph.visited[u] = true


        for each neighbor in graph.adjacencyList[u]:

            v = neighbor.vertex

            weight = neighbor.weight


            if !graph.visited[v] and graph.distance[u] + weight < graph.distance[v]:

                graph.distance[v] = graph.distance[u] + weight

                graph.previous[v] = u

                pq.push(Node(v, graph.distance[v]))

end function
    */
    vector<int> distances(G.numVertices, INF);
    distances[source] = 0;
    previous.assign(G.numVertices, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source});
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        for (const auto& e : G[u]) {
            int v = e.dst;
            int w = e.weight;
            if (distances[v] > distances[u] + w) {
                distances[v] = distances[u] + w;
                previous[v] = u;
                pq.push({distances[v], v});
            }
        }
    }
    return distances;

}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination)
{
    vector<int> path;
    for (int v = destination; v != -1; v = previous[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& v, int total)
{
    for (const auto& i : v) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::cout << "Total cost is " << total << std::endl;
}