#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
using namespace std;

// Função para calcular a média
double mean(const vector<double>& v) {
    return accumulate(v.begin(), v.end(), 0.0) / v.size();
}

// Função para calcular a regressão linear
pair<double, double> linear_regression(const vector<double>& x, const vector<double>& y) {
    int n = x.size();
    double x_mean = mean(x);
    double y_mean = mean(y);

    double numerator = 0.0;
    double denominator = 0.0;
    for (int i = 0; i < n; ++i) {
        numerator += (x[i] - x_mean) * (y[i] - y_mean);
        denominator += (x[i] - x_mean) * (x[i] - x_mean);
    }

    double b1 = numerator / denominator;
    double b0 = y_mean - b1 * x_mean;

    return {b0, b1};
}

int main() {
    vector<double> x = {1, 2, 3, 4, 5};
    vector<double> y = {2, 3, 5, 6, 5};

    pair<double, double> coefficients = linear_regression(x, y);
    double b0 = coefficients.first;
    double b1 = coefficients.second;

    cout << "Linear Regression Equation: y = " << b0 << " + " << b1 << "x" << endl;

    // Predizer valores
    double x_new = 6;
    double y_pred = b0 + b1 * x_new;
    cout << "Predicted value for x = " << x_new << " is y = " << y_pred << endl;

    return 0;
}