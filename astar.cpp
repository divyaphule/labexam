#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <functional>
#include <climits>
#include <algorithm>
using namespace std;

// Define a structure for storing the node data in the open set
struct Node {
    string name;
    int g_cost;   // Cost from the start node to the current node
    int h_cost;   // Heuristic estimated cost to the goal node
    int f_cost;   // f_cost = g_cost + h_cost
    string parent; // Parent node for reconstructing the path

    // Comparator to order nodes based on f_cost
    bool operator>(const Node &other) const {
        return f_cost > other.f_cost;
    }
};

// Function to calculate the heuristic (straight-line distance or estimated cost)
int heuristic(string node, string goal) {
    // For simplicity, using Manhattan distance or any heuristic
    // Here, you can define any heuristic based on your problem
    map<string, int> heuristic_map = {
        {"a", 4}, {"b", 2}, {"c", 3}, {"d", 5}, {"e", 1}, {"f", 0}, {"g", 0}
    };
    return heuristic_map[node];
}

// Function to perform A* search
void a_star(map<string, vector<pair<string, int>>> &graph, string start, string goal) {
    priority_queue<Node, vector<Node>, greater<Node>> open_set;
    map<string, bool> closed_set;
    map<string, int> g_scores;
    map<string, string> came_from;

    // Initialize the starting node
    open_set.push({start, 0, heuristic(start, goal), heuristic(start, goal), ""});
    g_scores[start] = 0;

    while (!open_set.empty()) {
        Node current = open_set.top();
        open_set.pop();

        if (current.name == goal) {
            // Reconstruct the path
            vector<string> path;
            string current_node = goal;
            while (current_node != "") {
                path.push_back(current_node);
                current_node = came_from[current_node];
            }
            reverse(path.begin(), path.end());

            cout << "Path found: ";
            for (const string &node : path) {
                cout << node << " ";
            }
            cout << endl;
            cout << "Total cost: " << current.g_cost << endl;
            return;
        }

        closed_set[current.name] = true;

        // Explore the neighbors
        for (auto &neighbor : graph[current.name]) {
            string neighbor_node = neighbor.first;
            int edge_cost = neighbor.second;

            if (closed_set.find(neighbor_node) != closed_set.end())
                continue;

            int tentative_g_score = current.g_cost + edge_cost;

            if (g_scores.find(neighbor_node) == g_scores.end() || tentative_g_score < g_scores[neighbor_node]) {
                g_scores[neighbor_node] = tentative_g_score;
                came_from[neighbor_node] = current.name;
                open_set.push({neighbor_node, tentative_g_score, heuristic(neighbor_node, goal), tentative_g_score + heuristic(neighbor_node, goal), current.name});
            }
        }
    }

    cout << "No path found from " << start << " to " << goal << endl;
}

int main() {
    // Graph input: node name and adjacent nodes with edge costs
    map<string, vector<pair<string, int>>> graph;

    // Number of edges
    int edges;
    cout << "Enter the number of edges: ";
    cin >> edges;

    cout << "Enter the edges (u v cost):" << endl;
    for (int i = 0; i < edges; i++) {
        string u, v;
        int cost;
        cin >> u >> v >> cost;
        graph[u].push_back({v, cost});
        graph[v].push_back({u, cost}); // For undirected graph
    }

    // Input for A* search
    string start, goal;
    cout << "Enter the start node: ";
    cin >> start;
    cout << "Enter the goal node: ";
    cin >> goal;

    // Perform A* search
    a_star(graph, start, goal);

    return 0;
}
