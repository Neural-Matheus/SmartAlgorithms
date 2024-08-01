#include <iostream>
#include <vector>

using namespace std;

void dfs_util(int u, const vector<vector<int>>& graph, vector<bool>& visited) {
    visited[u] = true;
    cout << u << " ";

    for (int v : graph[u]) {
        if (!visited[v]) {
            dfs_util(v, graph, visited);
        }
    }
}

void dfs(const vector<vector<int>>& graph, int start) {
    int n = graph.size();
    vector<bool> visited(n, false);
    dfs_util(start, graph, visited);
}

int main() {
    int V = 5;
    vector<vector<int>> graph = {
        {1, 2},
        {0, 3, 4},
        {0, 4},
        {1},
        {1, 2}
    };

    int start = 0;
    cout << "DFS starting from vertex " << start << ": ";
    dfs(graph, start);
    cout << endl;

    return 0;
}