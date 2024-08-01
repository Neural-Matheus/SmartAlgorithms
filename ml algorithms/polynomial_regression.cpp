#include <iostream>
#include <vector>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

// Função para calcular a regressão polinomial
VectorXd polynomial_regression(const VectorXd& x, const VectorXd& y, int degree) {
    int n = x.size();
    MatrixXd X(n, degree + 1);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= degree; ++j) {
            X(i, j) = pow(x[i], j);
        }
    }

    VectorXd coefficients = (X.transpose() * X).ldlt().solve(X.transpose() * y);
    return coefficients;
}

int main() {
    VectorXd x(5);
    x << 1, 2, 3, 4, 5;
    VectorXd y(5);
    y << 2, 3, 5, 6, 5;

    int degree = 2;
    VectorXd coefficients = polynomial_regression(x, y, degree);

    cout << "Polynomial Regression Coefficients: " << coefficients.transpose() << endl;

    // Predizer valores
    double x_new = 6;
    double y_pred = 0;
    for (int i = 0; i <= degree; ++i) {
        y_pred += coefficients[i] * pow(x_new, i);
    }
    cout << "Predicted value for x = " << x_new << " is y = " << y_pred << endl;

    return 0;
}