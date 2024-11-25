#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <set>
using namespace std;

// Function to perform DFS
void dfs(map<int, vector<int>> &graph, int start, int goal) {
    stack<vector<int>> frontier; // Stack to store paths
    frontier.push({start});      // Start with the initial node

    set<int> visited;           // Set to track visited nodes

    while (!frontier.empty()) {
        // Get the first path from the frontier
        vector<int> path = frontier.top();
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
        if (visited.find(node) == visited.end()) {
            visited.insert(node);

            // Add neighbors to the frontier
            for (int neighbor : graph[node]) {
                if (visited.find(neighbor) == visited.end()) {
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

    // Input for DFS
    int start, goal;
    cout << "Enter the start node: ";
    cin >> start;

    cout << "Enter the goal node: ";
    cin >> goal;

    // Perform DFS
    dfs(graph, start, goal);

    return 0;
}
