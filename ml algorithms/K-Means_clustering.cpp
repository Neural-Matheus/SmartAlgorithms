#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>
#include <cstdlib>
#include <ctime>

using namespace std;

double euclidean_distance(const vector<double>& a, const vector<double>& b) {
    double sum = 0.0;
    for (int i = 0; i < a.size(); ++i) {
        sum += pow(a[i] - b[i], 2);
    }
    return sqrt(sum);
}

vector<int> k_means(const vector<vector<double>>& data, int k, int max_iters) {
    int n = data.size();
    int m = data[0].size();
    
    vector<vector<double>> centroids(k, vector<double>(m));
    srand(time(0));
    
    for (int i = 0; i < k; ++i) {
        centroids[i] = data[rand() % n];
    }
    
    vector<int> labels(n);
    
    for (int iter = 0; iter < max_iters; ++iter) {
        for (int i = 0; i < n; ++i) {
            double min_dist = numeric_limits<double>::max();
            for (int j = 0; j < k; ++j) {
                double dist = euclidean_distance(data[i], centroids[j]);
                if (dist < min_dist) {
                    min_dist = dist;
                    labels[i] = j;
                }
            }
        }
        
        vector<vector<double>> new_centroids(k, vector<double>(m, 0.0));
        vector<int> count(k, 0);
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                new_centroids[labels[i]][j] += data[i][j];
            }
            count[labels[i]]++;
        }
        
        for (int j = 0; j < k; ++j) {
            if (count[j] == 0) continue;
            for (int d = 0; d < m; ++d) {
                new_centroids[j][d] /= count[j];
            }
        }
        
        centroids = new_centroids;
    }
    
    return labels;
}

int main() {
    vector<vector<double>> data = {
        {1.0, 2.0},
        {1.5, 1.8},
        {5.0, 8.0},
        {8.0, 8.0},
        {1.0, 0.6},
        {9.0, 11.0},
        {8.0, 2.0},
        {10.0, 2.0},
        {9.0, 3.0}
    };
    
    int k = 3;
    int max_iters = 100;
    
    vector<int> labels = k_means(data, k, max_iters);
    
    cout << "Cluster assignments:" << endl;
    for (int i = 0; i < labels.size(); ++i) {
        cout << "Point " << i << " is in cluster " << labels[i] << endl;
    }
    
    return 0;
}