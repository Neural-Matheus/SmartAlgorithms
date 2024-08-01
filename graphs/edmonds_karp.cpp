#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// Função que executa uma busca em largura (BFS) para encontrar um caminho de aumento
bool bfs(vector<vector<int>>& residual_graph, int source, int sink, vector<int>& parent) {
    int V = residual_graph.size();
    vector<bool> visited(V, false);
    queue<int> q;

    q.push(source);
    visited[source] = true;
    parent[source] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < V; ++v) {
            if (!visited[v] && residual_graph[u][v] > 0) {
                if (v == sink) {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return false;
}

// Função que implementa o algoritmo de Edmonds-Karp para encontrar o fluxo máximo
int edmonds_karp(vector<vector<int>>& graph, int source, int sink) {
    int V = graph.size();
    vector<vector<int>> residual_graph = graph;
    vector<int> parent(V);
    int max_flow = 0;

    while (bfs(residual_graph, source, sink, parent)) {
        int path_flow = INT_MAX;
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            path_flow = min(path_flow, residual_graph[u][v]);
        }

        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            residual_graph[u][v] -= path_flow;
            residual_graph[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}

int main() {
    int V = 6; // Número de vértices no grafo
    vector<vector<int>> graph(V, vector<int>(V, 0));

    // Definindo as capacidades das arestas
    graph[0][1] = 16;
    graph[0][2] = 13;
    graph[1][2] = 10;
    graph[1][3] = 12;
    graph[2][1] = 4;
    graph[2][4] = 14;
    graph[3][2] = 9;
    graph[3][5] = 20;
    graph[4][3] = 7;
    graph[4][5] = 4;

    int source = 0;
    int sink = 5;

    cout << "The maximum possible flow is " << edmonds_karp(graph, source, sink) << endl;

    return 0;
}