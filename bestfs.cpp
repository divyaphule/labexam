#include <iostream>
#include <vector>
#include <climits> // For INT_MAX
using namespace std;

#define MAX 100

class Graph {
public:
    vector<vector<int>> adjMatrix;
    vector<int> heuristic;
    int num;

    Graph(int vertices) {
        num = vertices;
        adjMatrix.resize(vertices, vector<int>(vertices, 0));
        heuristic.resize(vertices, 0);
    }

    void addEdge(int v1, int v2) {
        adjMatrix[v1][v2] = 1;
        adjMatrix[v2][v1] = 1;
    }

    void setHeuristic(int vertex, int value) {
        heuristic[vertex] = value;
    }
};

int getMin(const vector<int>& heuristics, const vector<bool>& visited, int current, const Graph& g) {
    int min = INT_MAX;
    int minIndex = -1;
    for (int i = 0; i < g.num; i++) {
        if (!visited[i] && heuristics[i] < min && g.adjMatrix[current][i] == 1) {
            min = heuristics[i];
            minIndex = i;
        }
    }
    return minIndex;
}

void bestFirstSearch(const Graph& g, int start, int goal) {
    vector<bool> visited(g.num, false);
    int current = start;
    visited[start] = true;

    cout << "Best-First Search Traversal: ";

    while (current != -1) {
        cout << current << " ";

        if (current == goal) {
            cout << "\nGoal node " << goal << " reached.\n";
            return;
        }

        int next = getMin(g.heuristic, visited, current, g);

        if (next == -1) {
            cout << "\nGoal node " << goal << " not reachable.\n";
            return;
        }

        visited[next] = true;
        current = next;
    }
}

int main() {
    int vertices, edges, v1, v2, start, goal;

    cout << "Enter the number of vertices: ";
    cin >> vertices;

    Graph g(vertices);

    cout << "Enter the number of edges: ";
    cin >> edges;

    cout << "Enter the edges (v1 v2):\n";
    for (int i = 0; i < edges; i++) {
        cin >> v1 >> v2;
        g.addEdge(v1, v2);
    }

    cout << "Enter heuristic values:\n";
    for (int i = 0; i < vertices; i++) {
        int hValue;
        cout << "Heuristic value for vertex " << i << ": ";
        cin >> hValue;
        g.setHeuristic(i, hValue);
    }

    cout << "Graph Adjacency Matrix:\n";
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            cout << g.adjMatrix[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Enter the start vertex: ";
    cin >> start;

    cout << "Enter the goal vertex: ";
    cin >> goal;

    bestFirstSearch(g, start, goal);

    return 0;
}
