#include <iostream>
#include <vector>
using namespace std;

#define MAX_VERTICES 100

void dfs(vector<vector<int>>& graph, int numVertices, int vertex, vector<bool>& visited) {
    cout << vertex << " ";
    visited[vertex] = true;

    for (int i = 0; i < numVertices; i++) {
        if (graph[vertex][i] && !visited[i]) {
            dfs(graph, numVertices, i, visited);
        }
    }
}

int main() {
    int numVertices = 6;

    // Using a 2D vector to represent the graph instead of a fixed array
    vector<vector<int>> graph = {
        {0, 1, 1, 0, 0, 0},
        {1, 0, 0, 1, 1, 0},
        {1, 0, 0, 0, 0, 1},
        {0, 1, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 1},
        {0, 0, 1, 0, 1, 0}
    };

    // Create a visited array to mark visited vertices
    vector<bool> visited(numVertices, false);

    cout << "DFS starting from vertex 0:\n";
    dfs(graph, numVertices, 0, visited);
    cout << endl;

    return 0;
}
