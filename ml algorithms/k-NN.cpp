#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

// Estrutura para armazenar pontos de dados
struct DataPoint {
    vector<double> features;
    int label;
};

// Função para calcular a distância euclidiana
double euclidean_distance(const vector<double>& a, const vector<double>& b) {
    double sum = 0.0;
    for (int i = 0; i < a.size(); ++i) {
        sum += pow(a[i] - b[i], 2);
    }
    return sqrt(sum);
}

// Função para prever o rótulo usando k-NN
int knn_predict(const vector<DataPoint>& data, const vector<double>& point, int k) {
    vector<pair<double, int>> distances;
    for (const auto& dp : data) {
        double dist = euclidean_distance(dp.features, point);
        distances.push_back({dist, dp.label});
    }

    sort(distances.begin(), distances.end());

    vector<int> k_labels(k);
    for (int i = 0; i < k; ++i) {
        k_labels[i] = distances[i].second;
    }

    // Contar a frequência dos rótulos
    vector<int> count(2, 0); // Assumindo rótulos binários 0 e 1
    for (int label : k_labels) {
        count[label]++;
    }

    return (count[0] > count[1]) ? 0 : 1;
}

int main() {
    // Pontos de dados de treinamento
    vector<DataPoint> data = {
        {{1.0, 2.0}, 0},
        {{2.0, 3.0}, 0},
        {{3.0, 3.0}, 1},
        {{6.0, 6.0}, 1},
        {{7.0, 8.0}, 1}
    };

    vector<double> point = {4.0, 4.0};
    int k = 3;

    int label = knn_predict(data, point, k);
    cout << "Predicted label for point (" << point[0] << ", " << point[1] << ") is " << label << endl;

    return 0;
}