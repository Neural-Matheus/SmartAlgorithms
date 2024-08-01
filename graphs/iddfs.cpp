#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Graph {
    int V; // Número de vértices
    list<int> *adj; // Ponteiro para um array contendo listas de adjacência

    bool DLS(int v, int target, int limit);

public:
    Graph(int V); // Construtor
    void addEdge(int v, int w); // Adiciona uma aresta ao grafo
    bool IDDFS(int v, int target, int max_depth);
};

Graph::Graph(int V) {
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w); // Adiciona w à lista de v
}

bool Graph::DLS(int v, int target, int limit) {
    if (v == target)
        return true;

    if (limit <= 0)
        return false;

    for (auto i = adj[v].begin(); i != adj[v].end(); ++i)
        if (DLS(*i, target, limit - 1))
            return true;

    return false;
}

bool Graph::IDDFS(int v, int target, int max_depth) {
    for (int i = 0; i <= max_depth; i++)
        if (DLS(v, target, i))
            return true;

    return false;
}

int main() {
    Graph g(7);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(2, 6);

    int target = 6, max_depth = 3;
    if (g.IDDFS(0, target, max_depth))
        cout << "Target " << target << " is reachable from source within max depth " << max_depth << endl;
    else
        cout << "Target " << target << " is NOT reachable from source within max depth " << max_depth << endl;

    return 0;
}
