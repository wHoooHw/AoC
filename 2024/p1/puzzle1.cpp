#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
using namespace std::chrono;

int similarity(const vector<int>& x, const vector<int>& y);
int check(const vector<int>& x, const vector<int>& y);

int main() {
    string filePath = "data.csv";
    vector<int> column1;
    vector<int> column2;

    auto start = high_resolution_clock::now();

    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        int col1, col2;
        if (!(iss >> col1 >> col2)) {
            cerr << "Error reading line" << endl;
            continue;
        }
        column1.push_back(col1);
        column2.push_back(col2);
    }
    file.close();

    sort(column1.begin(), column1.end());
    sort(column2.begin(), column2.end());

    cout << "Similarity: " << similarity(column1, column2) << endl;

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start).count();
    cout << "Runtime: " << duration << " ms" << endl;

    return 0;
}

int similarity(const vector<int>& x, const vector<int>& y) {
    int similarityScore = 0, count = 0;

    for (size_t i = 0; i < y.size(); i++) {
        for (size_t j = 0; j < x.size(); j++) {
            if (x[i] > y[j]) {
                continue;
            }

            if (x[i] < y[j]) {
                similarityScore += x[i] * count;
                count = 0;
                break;
            }

            if (x[i] == y[j]) {
                count++;
            }
        }
    }

    return similarityScore;
}

int check(const vector<int>& x, const vector<int>& y) {
    int difference = 0;

    for (size_t i = 0; i < x.size(); i++) {
        difference += abs(x[i] - y[i]);
    }

    return difference;
}