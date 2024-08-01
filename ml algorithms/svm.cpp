#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct SVM {
    vector<double> weights;
    double bias;
    double learning_rate;
    double lambda;

    SVM(int dimensions, double learning_rate, double lambda) {
        this->weights.resize(dimensions, 0.0);
        this->bias = 0.0;
        this->learning_rate = learning_rate;
        this->lambda = lambda;
    }

    void train(const vector<vector<double>>& X, const vector<int>& y, int epochs) {
        for (int epoch = 0; epoch < epochs; ++epoch) {
            for (int i = 0; i < X.size(); ++i) {
                double decision = 0.0;
                for (int j = 0; j < X[i].size(); ++j) {
                    decision += weights[j] * X[i][j];
                }
                decision += bias;

                if (y[i] * decision <= 1) {
                    for (int j = 0; j < weights.size(); ++j) {
                        weights[j] = weights[j] - learning_rate * (2 * lambda * weights[j] - y[i] * X[i][j]);
                    }
                    bias = bias + learning_rate * y[i];
                } else {
                    for (int j = 0; j < weights.size(); ++j) {
                        weights[j] = weights[j] - learning_rate * 2 * lambda * weights[j];
                    }
                }
            }
        }
    }

    int predict(const vector<double>& x) {
        double decision = 0.0;
        for (int j = 0; j < x.size(); ++j) {
            decision += weights[j] * x[j];
        }
        decision += bias;
        return decision >= 0 ? 1 : -1;
    }
};

int main() {
    vector<vector<double>> X = {
        {2.0, 3.0},
        {1.0, 2.0},
        {2.5, 1.5},
        {3.0, 3.0},
        {3.5, 4.0}
    };
    vector<int> y = {1, 1, -1, -1, 1};

    SVM svm(X[0].size(), 0.01, 0.01);
    svm.train(X, y, 1000);

    vector<double> new_point = {2.0, 2.5};
    int label = svm.predict(new_point);

    cout << "Predicted label: " << label << endl;

    return 0;
}