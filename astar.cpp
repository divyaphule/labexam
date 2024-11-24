#include <iostream>
#include <vector>
#include <queue>          
#include <unordered_map>    
#include <limits>           
#include <algorithm>        
#include <cmath>            


using namespace std;

struct Node {
    int vertex;
    double cost;
    double heuristic;
    Node* parent;

    Node(int v, double c, double h, Node* p = nullptr) : vertex(v), cost(c), heuristic(h), parent(p) {}

    double totalCost() const {
        return cost + heuristic;
    }

    bool operator>(const Node& other) const {
        return totalCost() > other.totalCost();
    }
};

double heuristic(int current, int goal) {
    // Example heuristic function (Manhattan distance)
    return abs(current - goal);
}

vector<int> reconstructPath(Node* node) {
    vector<int> path;
    while (node) {
        path.push_back(node->vertex);
        node = node->parent;
    }
    reverse(path.begin(), path.end());
    return path;
}

vector<int> aStar(const vector<vector<int>>& adjMatrix, int start, int goal) {
    priority_queue<Node, vector<Node>, greater<>> openSet;
    unordered_map<int, double> gScore;
    unordered_map<int, Node*> allNodes;

    // Initialize gScore for all nodes with infinity
    for (int i = 0; i < adjMatrix.size(); ++i) {
        gScore[i] = numeric_limits<double>::infinity();
    }
    
    gScore[start] = 0;
    openSet.emplace(start, 0, heuristic(start, goal));
    allNodes[start] = new Node(start, 0, heuristic(start, goal));

    while (!openSet.empty()) {
        Node current = openSet.top();
        openSet.pop();

        if (current.vertex == goal) {
            vector<int> path = reconstructPath(allNodes[goal]);
            // Clean up dynamically allocated nodes
            for (auto& pair : allNodes) {
                delete pair.second;
            }
            return path;
        }

        for (int i = 0; i < adjMatrix.size(); ++i) {
            if (adjMatrix[current.vertex][i] == 0) continue;

            double tentative_gScore = gScore[current.vertex] + adjMatrix[current.vertex][i];

            if (tentative_gScore < gScore[i]) {
                gScore[i] = tentative_gScore;
                Node* neighborNode = new Node(i, tentative_gScore, heuristic(i, goal), new Node(current));
                
                openSet.push(*neighborNode);
                if (allNodes.find(i) != allNodes.end()) {
                    delete allNodes[i];
                }
                allNodes[i] = neighborNode;
            }
        }
    }

    // Clean up dynamically allocated nodes
    for (auto& pair : allNodes) {
        delete pair.second;
    }

    return {}; // Return empty path if no path found
}

int main() {
    vector<vector<int>> adjMatrix = {
        {0, 1, 4, 0, 0, 0},
        {1, 0, 4, 2, 7, 0},
        {4, 4, 0, 3, 5, 0},
        {0, 2, 3, 0, 4, 6},
        {0, 7, 5, 4, 0, 7},
        {0, 0, 0, 6, 7, 0}
    };

    int start = 0;
    int goal = 4;

    vector<int> path = aStar(adjMatrix, start, goal);

    if (!path.empty()) {
        cout << "Path found: ";
        for (int vertex : path) {
            cout << vertex << " ";
        }
        cout << endl;
    } else {
        cout << "No path found." << endl;
    }

    return 0;
}

