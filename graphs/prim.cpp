#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

typedef pair<int, int> pii;

void prim(vector<vector<pii>>& graph, int V) {
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    vector<int> key(V, INT_MAX);
    vector<int> parent(V, -1);
    vector<bool> inMST(V, false);

    int start = 0;
    pq.push({0, start});
    key[start] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        inMST[u] = true;

        for (auto& neighbor : graph[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (!inMST[v] && key[v] > weight) {
                key[v] = weight;
                pq.push({key[v], v});
                parent[v] = u;
            }
        }
    }

    cout << "Edges in the Minimum Spanning Tree:\n";
    for (int i = 1; i < V; ++i) {
        cout << parent[i] << " - " << i << " \n";
    }
}

int main() {
    int V = 5;
    vector<vector<pii>> graph(V);

    graph[0].push_back({1, 2});
    graph[0].push_back({3, 6});
    graph[1].push_back({0, 2});
    graph[1].push_back({2, 3});
    graph[1].push_back({3, 8});
    graph[1].push_back({4, 5});
    graph[2].push_back({1, 3});
    graph[2].push_back({4, 7});
    graph[3].push_back({0, 6});
    graph[3].push_back({1, 8});
    graph[4].push_back({1, 5});
    graph[4].push_back({2, 7});

    prim(graph, V);

    return 0;
}