#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>  // Include this header to use INT_MAX
#include <algorithm>

using namespace std;

// Task structure to represent each node
struct Task {
    string name;
    int cost; // Cost to solve this task
    bool isGoal;
    bool isAndNode; // Whether this node is an AND node (true) or OR node (false)
    vector<Task*> subTasks; // Subtasks for AND/OR nodes

    Task(string name, int cost = 0, bool isGoal = false, bool isAndNode = false)
        : name(name), cost(cost), isGoal(isGoal), isAndNode(isAndNode) {}
};

// AO* Algorithm to find the optimal task sequence
int aoStar(Task* task) {
    // If the task is already a goal, return its cost
    if (task->isGoal) {
        return task->cost;
    }

    if (task->isAndNode) {
        // For AND nodes, we need to solve all subtasks
        int totalCost = 0;
        for (auto subTask : task->subTasks) {
            totalCost += aoStar(subTask);
        }
        return totalCost;
    } else {
        // For OR nodes, we choose the minimum cost among all subtasks
        int minCost = INT_MAX;  // Now INT_MAX is defined because of the <climits> header
        for (auto subTask : task->subTasks) {
            minCost = min(minCost, aoStar(subTask));
        }
        return minCost;
    }
}

int main() {
    int numTasks;
    cout << "Enter number of tasks: ";
    cin >> numTasks;

    unordered_map<string, Task*> taskMap;

    // Input tasks
    for (int i = 0; i < numTasks; i++) {
        string taskName;
        int cost;
        bool isGoal, isAndNode;

        cout << "Enter task name: ";
        cin >> taskName;

        cout << "Enter cost for task " << taskName << ": ";
        cin >> cost;

        cout << "Is task " << taskName << " a goal (0 for No, 1 for Yes)? ";
        cin >> isGoal;

        cout << "Is task " << taskName << " an AND node (0 for No, 1 for Yes)? ";
        cin >> isAndNode;

        // Create task object
        taskMap[taskName] = new Task(taskName, cost, isGoal, isAndNode);
    }

    // Assign subtasks for AND/OR nodes
    int numRelations;
    cout << "Enter number of relationships between tasks: ";
    cin >> numRelations;

    for (int i = 0; i < numRelations; i++) {
        string parentTask, subTask;
        cout << "Enter parent task and subtask (e.g., A B where A is parent and B is subtask): ";
        cin >> parentTask >> subTask;

        taskMap[parentTask]->subTasks.push_back(taskMap[subTask]);
    }

    // Select the root task (starting point)
    string rootTaskName;
    cout << "Enter the root task to start the AO* search: ";
    cin >> rootTaskName;

    // Perform AO* search
    int totalCost = aoStar(taskMap[rootTaskName]);

    cout << "Total cost to reach goal from task " << rootTaskName << ": " << totalCost << endl;

    // Cleanup
    for (auto& taskEntry : taskMap) {
        delete taskEntry.second;
    }

    return 0;
}
