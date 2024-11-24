#include <iostream>
#include <vector>
using namespace std;

#define MAX_VERTICES 100  // Define a maximum number of vertices

// Function to check if the current color assignment is safe for vertex v
bool isSafe(int graph[MAX_VERTICES][MAX_VERTICES], vector<int>& color, int v, int c, int V) {
    for (int i = 0; i < V; i++) {
        if (graph[v][i] && color[i] == c) {
            return false;  // An adjacent vertex has the same color
        }
    }
    return true;
}

// Function to solve the graph coloring problem using backtracking
bool graphColoringUtil(int graph[MAX_VERTICES][MAX_VERTICES], int m, vector<int>& color, int v, int V) {
    if (v == V) {
        return true;  // All vertices are assigned a color
    }

    for (int c = 1; c <= m; c++) {  // Try different colors
        if (isSafe(graph, color, v, c, V)) {
            color[v] = c;  // Assign color c to vertex v

            // Recur to assign colors to the rest of the vertices
            if (graphColoringUtil(graph, m, color, v + 1, V)) {
                return true;
            }

            // Backtrack
            color[v] = 0;  // Remove assigned color
        }
    }
    return false;  // No valid coloring found
}

// Function to solve the m-coloring problem
bool graphColoring(int graph[MAX_VERTICES][MAX_VERTICES], int m, int V) {
    vector<int> color(V, 0);  // Array to store color assignments, initialized to 0 (uncolored)

    if (!graphColoringUtil(graph, m, color, 0, V)) {
        cout << "Solution does not exist" << endl;
        return false;
    }

    // Print the solution
    cout << "Solution exists: Following are the assigned colors:" << endl;
    for (int i = 0; i < V; i++) {
        cout << "Vertex " << i << " ---> Color " << color[i] << endl;
    }
    return true;
}

// Driver code
int main() {
    int graph[MAX_VERTICES][MAX_VERTICES];
    int V, m;

    // Input the number of vertices
    cout << "Enter the number of vertices: ";
    cin >> V;

    // Input the adjacency matrix
    cout << "Enter the adjacency matrix (" << V << " x " << V << "):" << endl;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            cin >> graph[i][j];
        }
    }

    // Input the number of colors
    cout << "Enter the number of colors: ";
    cin >> m;

    // Call the graph coloring function
    graphColoring(graph, m, V);

    return 0;
}
