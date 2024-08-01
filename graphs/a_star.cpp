#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <set>

using namespace std;

struct Node {
    pair<int, int> position;
    Node* parent;
    int g, h, f;

    Node(pair<int, int> pos, Node* parent = nullptr) : position(pos), parent(parent), g(0), h(0), f(0) {}

    bool operator==(const Node& other) const {
        return position == other.position;
    }

    bool operator<(const Node& other) const {
        return f > other.f;
    }
};

int heuristic(const pair<int, int>& a, const pair<int, int>& b) {
    return abs(a.first - b.first) + abs(a.second - b.second); // Distância de Manhattan
}

vector<pair<int, int>> a_star(vector<vector<int>>& grid, pair<int, int> start, pair<int, int> end) {
    priority_queue<Node> open_list;
    set<pair<int, int>> closed_list;

    Node* start_node = new Node(start);
    Node* end_node = new Node(end);

    open_list.push(*start_node);

    while (!open_list.empty()) {
        Node current_node = open_list.top();
        open_list.pop();
        closed_list.insert(current_node.position);

        if (current_node == *end_node) {
            vector<pair<int, int>> path;
            Node* current = &current_node;
            while (current != nullptr) {
                path.push_back(current->position);
                current = current->parent;
            }
            reverse(path.begin(), path.end());
            return path;
        }

        vector<pair<int, int>> neighbors = {
            {0, -1}, {0, 1}, {-1, 0}, {1, 0} // Cima, Baixo, Esquerda, Direita
        };

        for (const auto& neighbor : neighbors) {
            pair<int, int> neighbor_position = {current_node.position.first + neighbor.first, current_node.position.second + neighbor.second};

            if (neighbor_position.first < 0 || neighbor_position.first >= grid.size() || neighbor_position.second < 0 || neighbor_position.second >= grid[0].size()) {
                continue;
            }

            if (grid[neighbor_position.first][neighbor_position.second] != 0) {
                continue;
            }

            if (closed_list.find(neighbor_position) != closed_list.end()) {
                continue;
            }

            Node* neighbor_node = new Node(neighbor_position, new Node(current_node));
            neighbor_node->g = current_node.g + 1;
            neighbor_node->h = heuristic(neighbor_position, end_node->position);
            neighbor_node->f = neighbor_node->g + neighbor_node->h;

            bool add_to_open = true;
            priority_queue<Node> temp_queue = open_list;
            while (!temp_queue.empty()) {
                Node temp_node = temp_queue.top();
                temp_queue.pop();
                if (*neighbor_node == temp_node && neighbor_node->g >= temp_node.g) {
                    add_to_open = false;
                    break;
                }
            }

            if (add_to_open) {
                open_list.push(*neighbor_node);
            }
        }
    }

    return vector<pair<int, int>>();
}

int main() {
    vector<vector<int>> grid = {
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0}
    };

    pair<int, int> start = {0, 0};
    pair<int, int> end = {4, 4};

    vector<pair<int, int>> path = a_star(grid, start, end);
    if (!path.empty()) {
        cout << "Caminho encontrado: ";
        for (const auto& position : path) {
            cout << "(" << position.first << ", " << position.second << ") ";
        }
        cout << endl;
    } else {
        cout << "Caminho não encontrado" << endl;
    }

    return 0;
}
