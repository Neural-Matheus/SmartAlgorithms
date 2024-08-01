#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

struct TreeNode {
    int feature;
    double threshold;
    int label;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int label) : feature(-1), threshold(0.0), label(label), left(nullptr), right(nullptr) {}
    TreeNode(int feature, double threshold) : feature(feature), threshold(threshold), label(-1), left(nullptr), right(nullptr) {}
};

double gini_impurity(const vector<int>& labels) {
    int n = labels.size();
    if (n == 0) return 0.0;
    
    int count0 = count(labels.begin(), labels.end(), 0);
    int count1 = n - count0;
    
    double p0 = (double)count0 / n;
    double p1 = (double)count1 / n;
    
    return 1.0 - p0 * p0 - p1 * p1;
}

pair<vector<vector<double>>, vector<int>> split(const vector<vector<double>>& X, const vector<int>& y, int feature, double threshold) {
    vector<vector<double>> left_X, right_X;
    vector<int> left_y, right_y;
    
    for (int i = 0; i < X.size(); ++i) {
        if (X[i][feature] < threshold) {
            left_X.push_back(X[i]);
            left_y.push_back(y[i]);
        } else {
            right_X.push_back(X[i]);
            right_y.push_back(y[i]);
        }
    }
    
    return {{left_X, right_X}, {left_y, right_y}};
}

TreeNode* build_tree(const vector<vector<double>>& X, const vector<int>& y, int max_depth, int depth = 0) {
    int n = y.size();
    int count0 = count(y.begin(), y.end(), 0);
    int count1 = n - count0;
    
    if (count0 == n) return new TreeNode(0);
    if (count1 == n) return new TreeNode(1);
    if (depth >= max_depth) return new TreeNode(count1 >= count0 ? 1 : 0);
    
    int best_feature = -1;
    double best_threshold = 0.0;
    double best_impurity = 1.0;
    
    for (int feature = 0; feature < X[0].size(); ++feature) {
        vector<double> values;
        for (const auto& row : X) {
            values.push_back(row[feature]);
        }
        sort(values.begin(), values.end());
        values.erase(unique(values.begin(), values.end()), values.end());
        
        for (double threshold : values) {
            auto [left_y, right_y] = split(X, y, feature, threshold).second;
            double impurity = (left_y.size() * gini_impurity(left_y) + right_y.size() * gini_impurity(right_y)) / n;
            if (impurity < best_impurity) {
                best_feature = feature;
                best_threshold = threshold;
                best_impurity = impurity;
            }
        }
    }
    
    if (best_feature == -1) return new TreeNode(count1 >= count0 ? 1 : 0);
    
    auto [left_X, right_X] = split(X, y, best_feature, best_threshold).first;
    auto [left_y, right_y] = split(X, y, best_feature, best_threshold).second;
    
    TreeNode* node = new TreeNode(best_feature, best_threshold);
    node->left = build_tree(left_X, left_y, max_depth, depth + 1);
    node->right = build_tree(right_X, right_y, max_depth, depth + 1);
    
    return node;
}

int predict(TreeNode* node, const vector<double>& x) {
    if (node->label != -1) return node->label;
    if (x[node->feature] < node->threshold) return predict(node->left, x);
    return predict(node->right, x);
}

class RandomForest {
private:
    vector<TreeNode*> trees;
    int n_trees;
    int max_depth;
    double sample_size;

    vector<int> bootstrap_sample(int n) {
        vector<int> sample_indices;
        for (int i = 0; i < sample_size * n; ++i) {
            sample_indices.push_back(rand() % n);
        }
        return sample_indices;
    }

public:
    RandomForest(int n_trees, int max_depth, double sample_size) : n_trees(n_trees), max_depth(max_depth), sample_size(sample_size) {}

    void fit(const vector<vector<double>>& X, const vector<int>& y) {
        int n = X.size();
        for (int i = 0; i < n_trees; ++i) {
            vector<int> sample_indices = bootstrap_sample(n);
            vector<vector<double>> X_sample;
            vector<int> y_sample;
            for (int idx : sample_indices) {
                X_sample.push_back(X[idx]);
                y_sample.push_back(y[idx]);
            }
            trees.push_back(build_tree(X_sample, y_sample, max_depth));
        }
    }

    int predict(const vector<double>& x) {
        vector<int> votes;
        for (TreeNode* tree : trees) {
            votes.push_back(predict(tree, x));
        }
        return count(votes.begin(), votes.end(), 1) > count(votes.begin(), votes.end(), 0) ? 1 : 0;
    }
};

int main() {
    vector<vector<double>> X = {
        {2.0, 3.0},
        {1.0, 2.0},
        {2.5, 1.5},
        {3.0, 3.0},
        {3.5, 4.0},
        {5.0, 3.0},
        {2.0, 2.0},
        {4.0, 2.0}
    };
    vector<int> y = {1, 1, 0, 0, 1, 0, 1, 0};

    RandomForest rf(5, 3, 0.8);
    rf.fit(X, y);

    vector<double> new_point = {2.5, 2.5};
    int label = rf.predict(new_point);

    cout << "Predicted label: " << label << endl;

    return 0;
}
