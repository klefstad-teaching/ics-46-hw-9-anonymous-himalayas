#include "../src/dijkstras.h"


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
    int n = G.size();
    vector<int> distances(n, INF);
    previous.resize(n, -1);
    vector<bool> visited(n, false);
    priority_queue<Edge> pq;
    pq.push(Edge(source));
    distances[source] = 0;
    while (!pq.empty()) {
        Edge current = pq.top();
        pq.pop();
        int u = current.src;
        if (visited[u]) {
            continue;
        }
        visited[u] = true;
        for (const auto& neighbor : G[u]) {
            int v = neighbor.dst;
            int weight = neighbor.weight;
            if (!visited[v] && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                pq.push(Edge(v, distances[v]));
            }
        }
    }

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
    std::cout << "Total cost is " << total << std::endl;
}