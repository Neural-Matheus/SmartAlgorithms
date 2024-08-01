#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>

using namespace std;

double sigmoid(double z) {
    return 1.0 / (1.0 + exp(-z));
}

void logistic_regression(const vector<vector<double>>& X, const vector<int>& y, vector<double>& weights, double alpha, int epochs) {
    int m = X.size();
    int n = X[0].size();
    
    weights.resize(n, 0.0);
    
    for (int epoch = 0; epoch < epochs; ++epoch) {
        vector<double> gradient(n, 0.0);
        
        for (int i = 0; i < m; ++i) {
            double z = inner_product(X[i].begin(), X[i].end(), weights.begin(), 0.0);
            double h = sigmoid(z);
            for (int j = 0; j < n; ++j) {
                gradient[j] += (h - y[i]) * X[i][j];
            }
        }
        
        for (int j = 0; j < n; ++j) {
            weights[j] -= alpha * gradient[j] / m;
        }
    }
}

int predict(const vector<double>& weights, const vector<double>& x) {
    double z = inner_product(x.begin(), x.end(), weights.begin(), 0.0);
    return sigmoid(z) >= 0.5 ? 1 : 0;
}

int main() {
    vector<vector<double>> X = {
        {1, 2.0, 3.0},
        {1, 1.0, 2.0},
        {1, 2.5, 1.5},
        {1, 3.0, 3.0}
    };
    vector<int> y = {0, 0, 1, 1};
    
    vector<double> weights;
    double alpha = 0.1;
    int epochs = 1000;
    
    logistic_regression(X, y, weights, alpha, epochs);
    
    vector<double> new_point = {1, 2.0, 2.5};
    int label = predict(weights, new_point);
    
    cout << "Predicted label: " << label << endl;
    
    return 0;
}
