#include "../src/dijkstras.h"



void test_dijsktras()
{
    Graph G;
    file_to_graph("src/small.txt", G);
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);
    for (int i = 0; i< previous.size(); i++) {
        std::cout << previous[i] << " ";
    }
    vector<int> path = extract_shortest_path(distances, previous, 1);
    print_path(path, path.size());

}

int main()
{
    test_dijsktras();
    return 0;
}