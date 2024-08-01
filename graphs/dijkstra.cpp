#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

typedef pair<int, int> pii;

class Graph {
public:
    Graph(int vertices, bool is_directed = true) : n(vertices), directed(is_directed) {
        graph.resize(vertices);
    }

    void add_edge(int u, int v, int weight) {
        if (u < 0 || u >= n || v < 0 || v >= n) {
            throw invalid_argument("Invalid vertex number");
        }
        graph[u].push_back({v, weight});
        if (!directed) {
            graph[v].push_back({u, weight});
        }
    }

    vector<int> dijkstra(int start) {
        if (start < 0 || start >= n) {
            throw invalid_argument("Invalid start vertex");
        }

        vector<int> dist(n, INT_MAX);
        vector<int> prev(n, -1);
        priority_queue<pii, vector<pii>, greater<pii>> pq;

        dist[start] = 0;
        pq.push({0, start});

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (auto& neighbor : graph[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    prev[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }

        this->prev = prev;
        return dist;
    }

    vector<int> get_shortest_path(int start, int end) {
        vector<int> path;
        for (int at = end; at != -1; at = prev[at]) {
            path.push_back(at);
        }
        reverse(path.begin(), path.end());

        if (path.size() == 1 && path[0] != start) {
            return {}; // No path found
        }
        return path;
    }

    static Graph generate_random_graph(int vertices, int edges, int max_weight, bool is_directed = true) {
        Graph graph(vertices, is_directed);
        srand(static_cast<unsigned>(time(0)));

        for (int i = 0; i < edges; ++i) {
            int u = rand() % vertices;
            int v = rand() % vertices;
            int weight = rand() % max_weight + 1;
            graph.add_edge(u, v, weight);
        }

        return graph;
    }

private:
    int n;
    bool directed;
    vector<vector<pii>> graph;
    vector<int> prev;
};

int main() {
    try {
        int vertices = 10; // Number of vertices
        int edges = 20;    // Number of edges
        int max_weight = 10; // Maximum weight of edges

        // Generate a random graph
        Graph graph = Graph::generate_random_graph(vertices, edges, max_weight);

        int start = 0; // Starting vertex
        vector<int> distances = graph.dijkstra(start);

        cout << "Distances from vertex " << start << ":\n";
        for (int i = 0; i < distances.size(); i++) {
            cout << "To vertex " << i << ": " << distances[i] << endl;
        }

        int end = vertices - 1; // Ending vertex for path reconstruction
        vector<int> path = graph.get_shortest_path(start, end);

        if (!path.empty()) {
            cout << "Shortest path from " << start << " to " << end << ": ";
            for (int v : path) {
                cout << v << " ";
            }
            cout << endl;
        } else {
            cout << "No path found from " << start << " to " << end << endl;
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
