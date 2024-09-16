#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cmath>

using namespace std;

// Function to convert a number in a given base to decimal (base 10)
int convertToDecimal(const string& value, int base) {
    return stoi(value, nullptr, base);
}

// Function to perform Lagrange Interpolation and return the constant term
double lagrangeInterpolation(const vector<int>& x_vals, const vector<int>& y_vals) {
    int n = x_vals.size();
    double constant_term = 0.0;

    // Lagrange interpolation formula to find the constant term
    for (int i = 0; i < n; i++) {
        double term = y_vals[i];
        for (int j = 0; j < n; j++) {
            if (i != j) {
                term *= double(0 - x_vals[j]) / double(x_vals[i] - x_vals[j]);
            }
        }
        constant_term += term;
    }

    return constant_term;
}

// Main function to compute the secret (constant term) of the polynomial
double computePolynomialSecret(const map<string, map<string, string>>& data) {
    int n = stoi(data.at("keys").at("n"));
    int k = stoi(data.at("keys").at("k"));

    vector<int> x_vals;
    vector<int> y_vals;

    // Iterate through the input data to decode the x and y values
    for (const auto& pair : data) {
        if (pair.first != "keys") {
            int x = stoi(pair.first);
            int y = convertToDecimal(pair.second.at("value"), stoi(pair.second.at("base")));
            x_vals.push_back(x);
            y_vals.push_back(y);
        }
    }

    // Perform Lagrange interpolation to find the constant term
    double constant_term = lagrangeInterpolation(x_vals, y_vals);

    return constant_term;
}

int main() {
    // Sample test case in a map (JSON equivalent in C++)
    map<string, map<string, string>> sample_data = {
        {"keys", {{"n", "4"}, {"k", "3"}}},
        {"1", {{"base", "10"}, {"value", "4"}}},
        {"2", {{"base", "2"}, {"value", "111"}}},
        {"3", {{"base", "10"}, {"value", "12"}}},
        {"6", {{"base", "4"}, {"value", "213"}}}
    };

    // Compute and print the constant term of the polynomial
    double result = computePolynomialSecret(sample_data);
    cout << "The constant term of the polynomial is: " << result << endl;

    return 0;
}
