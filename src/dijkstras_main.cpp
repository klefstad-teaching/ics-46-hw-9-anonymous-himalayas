#include "../src/dijkstras.h"



void test_dijsktras()
{
    Graph G;
    file_to_graph("graph.txt", G);
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);
    print_path(distances, 0);
    print_path(previous, 0);
    vector<int> path = extract_shortest_path(distances, previous, 4);
    print_path(path, 0);

}

int main()
{
    test_dijsktras();
    return 0;
}