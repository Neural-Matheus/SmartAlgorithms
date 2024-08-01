#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void bfs(const vector<vector<int>>& graph, int start) {
    int n = graph.size();
    vector<bool> visited(n, false);
    queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cout << u << " ";

        for (int v : graph[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
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
    cout << "BFS starting from vertex " << start << ": ";
    bfs(graph, start);
    cout << endl;

    return 0;
}