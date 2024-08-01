#include <iostream>
#include <vector>
#include <map>

using namespace std;

class NaiveBayes {
private:
    map<int, int> class_counts;
    map<int, map<int, map<int, int>>> feature_counts;
    map<int, double> class_probabilities;
    map<int, map<int, map<int, double>>> feature_probabilities;

public:
    void train(const vector<vector<int>>& X, const vector<int>& y) {
        int n = X.size();
        int m = X[0].size();

        for (int i = 0; i < n; ++i) {
            int label = y[i];
            class_counts[label]++;

            for (int j = 0; j < m; ++j) {
                feature_counts[label][j][X[i][j]]++;
            }
        }

        for (auto& kv : class_counts) {
            int label = kv.first;
            class_probabilities[label] = (double)class_counts[label] / n;

            for (int j = 0; j < m; ++j) {
                for (auto& fv : feature_counts[label][j]) {
                    feature_probabilities[label][j][fv.first] = (double)fv.second / class_counts[label];
                }
            }
        }
    }

    int predict(const vector<int>& x) {
        double max_prob = -1.0;
        int best_label = -1;

        for (auto& kv : class_probabilities) {
            int label = kv.first;
            double prob = class_probabilities[label];

            for (int j = 0; j < x.size(); ++j) {
                prob *= feature_probabilities[label][j][x[j]];
            }

            if (prob > max_prob) {
                max_prob = prob;
                best_label = label;
            }
        }

        return best_label;
    }
};

int main() {
    vector<vector<int>> X = {
        {1, 0, 0},
        {1, 0, 1},
        {0, 1, 0},
        {0, 1, 1}
    };
    vector<int> y = {0, 0, 1, 1};

    NaiveBayes nb;
    nb.train(X, y);

    vector<int> new_point = {1, 1, 0};
    int label = nb.predict(new_point);

    cout << "Predicted label: " << label << endl;

    return 0;
}