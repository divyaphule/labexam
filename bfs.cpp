#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

// Function to perform BFS
void bfs(map<int, vector<int>> &graph, int start, int goal) {
    queue<vector<int>> frontier; // Queue to store paths
    frontier.push({start});      // Start with the initial node

    map<int, bool> visited;      // Track visited nodes

    while (!frontier.empty()) {
        // Get the first path from the frontier
        vector<int> path = frontier.front();
        frontier.pop();

        // Get the last node in the current path
        int node = path.back();

        // If this node is the goal, print the path and exit
        if (node == goal) {
            cout << "Path found: ";
            for (int n : path) {
                cout << n << " ";
            }
            cout << endl;
            return;
        }

        // Mark the node as visited
        if (!visited[node]) {
            visited[node] = true;

            // Add neighbors to the frontier
            for (int neighbor : graph[node]) {
                if (!visited[neighbor]) {
                    vector<int> newPath(path);
                    newPath.push_back(neighbor);
                    frontier.push(newPath);
                }
            }
        }
    }

    // If the loop ends, no path was found
    cout << "No path found from " << start << " to " << goal << endl;
}

int main() {
    // Graph input
    map<int, vector<int>> graph;
    int n, edges;
    cout << "Enter the number of nodes: ";
    cin >> n;

    cout << "Enter the number of edges: ";
    cin >> edges;

    cout << "Enter the edges (u v for an edge between u and v):" << endl;
    for (int i = 0; i < edges; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u); // Uncomment for undirected graph
    }

    // Input for BFS
    int start, goal;
    cout << "Enter the start node: ";
    cin >> start;

    cout << "Enter the goal node: ";
    cin >> goal;

    // Perform BFS
    bfs(graph, start, goal);

    return 0;
}
