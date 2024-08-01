#include <iostream>
#include <vector>
#include <memory>
using namespace std;

// Estrutura de uma caixa AABB
struct AABB {
    pair<double, double> min;
    pair<double, double> max;

    AABB(pair<double, double> min, pair<double, double> max) : min(min), max(max) {}

    // Verifica se duas caixas AABB se intersectam
    bool intersects(const AABB& other) const {
        return (min.first <= other.max.first && max.first >= other.min.first &&
                min.second <= other.max.second && max.second >= other.min.second);
    }
};

// Estrutura de um nó da árvore AABB
struct AABBNode {
    AABB box;
    unique_ptr<AABBNode> left;
    unique_ptr<AABBNode> right;
    bool isLeaf;
    int objectIndex; // Índice do objeto se este for um nó folha

    AABBNode(const AABB& box, int objectIndex = -1) : box(box), isLeaf(objectIndex != -1), objectIndex(objectIndex) {}
};

// Classe da árvore AABB
class AABBTree {
private:
    unique_ptr<AABBNode> root;

    unique_ptr<AABBNode> insert(unique_ptr<AABBNode> node, const AABB& box, int objectIndex) {
        if (!node) {
            return make_unique<AABBNode>(box, objectIndex);
        }

        if (node->isLeaf) {
            AABB newBox = AABB(box.min, box.max);
            newBox.min.first = min(newBox.min.first, node->box.min.first);
            newBox.min.second = min(newBox.min.second, node->box.min.second);
            newBox.max.first = max(newBox.max.first, node->box.max.first);
            newBox.max.second = max(newBox.max.second, node->box.max.second);

            auto internalNode = make_unique<AABBNode>(newBox);
            internalNode->left = move(node);
            internalNode->right = make_unique<AABBNode>(box, objectIndex);
            return internalNode;
        }

        if (node->left->box.intersects(box)) {
            node->left = insert(move(node->left), box, objectIndex);
        } else {
            node->right = insert(move(node->right), box, objectIndex);
        }

        node->box.min.first = min(node->left->box.min.first, node->right->box.min.first);
        node->box.min.second = min(node->left->box.min.second, node->right->box.min.second);
        node->box.max.first = max(node->left->box.max.first, node->right->box.max.first);
        node->box.max.second = max(node->left->box.max.second, node->right->box.max.second);

        return node;
    }

    void query(const unique_ptr<AABBNode>& node, const AABB& box, vector<int>& results) const {
        if (!node) return;

        if (!node->box.intersects(box)) return;

        if (node->isLeaf) {
            results.push_back(node->objectIndex);
            return;
        }

        query(node->left, box, results);
        query(node->right, box, results);
    }

public:
    AABBTree() : root(nullptr) {}

    void insert(const AABB& box, int objectIndex) {
        root = insert(move(root), box, objectIndex);
    }

    vector<int> query(const AABB& box) const {
        vector<int> results;
        query(root, box, results);
        return results;
    }
};

int main() {
    AABBTree tree;

    tree.insert(AABB({0, 0}, {1, 1}), 0);
    tree.insert(AABB({2, 2}, {3, 3}), 1);
    tree.insert(AABB({1, 1}, {2, 2}), 2);
    tree.insert(AABB({3, 3}, {4, 4}), 3);

    AABB queryBox({1.5, 1.5}, {2.5, 2.5});
    vector<int> results = tree.query(queryBox);

    cout << "Intersecting objects with query box: ";
    for (int index : results) {
        cout << index << " ";
    }
    cout << endl;

    return 0;
}