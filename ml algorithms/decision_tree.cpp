#include <iostream>
#include <vector>
#include <algorithm>

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

int main() {
    vector<vector
