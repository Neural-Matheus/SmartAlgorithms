#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int src, dest, weight;
};

struct Graph {
    int V, E;
    vector<Edge> edges;
};

struct Subset {
    int parent;
    int rank;
};

int find(Subset subsets[], int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

void union_subsets(Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank) {
        subsets[xroot].parent = yroot;
    } else if (subsets[xroot].rank > subsets[yroot].rank) {
        subsets[yroot].parent = xroot;
    } else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

bool compare_edges(Edge a, Edge b) {
    return a.weight < b.weight;
}

void kruskal(Graph& graph) {
    int V = graph.V;
    vector<Edge> result;
    int e = 0;

    sort(graph.edges.begin(), graph.edges.end(), compare_edges);

    Subset* subsets = new Subset[(V * sizeof(Subset))];
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    int i = 0;
    while (e < V - 1 && i < graph.E) {
        Edge next_edge = graph.edges[i++];
        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        if (x != y) {
            result.push_back(next_edge);
            union_subsets(subsets, x, y);
            e++;
        }
    }

    cout << "Edges in the Minimum Spanning Tree:\n";
    for (i = 0; i < result.size(); ++i) {
        cout << result[i].src << " -- " << result[i].dest << " == " << result[i].weight << endl;
    }

    delete[] subsets;
}

int main() {
    int V = 4;
    int E = 5;
    Graph graph = {V, E, {
        {0, 1, 10}, {0, 2, 6}, {0, 3, 5},
        {1, 3, 15}, {2, 3, 4}
    }};

    kruskal(graph);

    return 0;
}