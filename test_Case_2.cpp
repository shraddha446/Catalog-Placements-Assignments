#include <bits/stdc++.h>

using namespace std;

long long convertToDecimal(const string& value, int base) {
    try {
        return stoll(value, nullptr, base); 
    } catch (const invalid_argument& e) {
        cerr << "Invalid argument during conversion: " << value << " with base " << base << endl;
        return 0;
    } catch (const out_of_range& e) {
        cerr << "Out of range error during conversion: " << value << " with base " << base << endl;
        return 0;
    }
}

double lagrangeInterpolation(const vector<int>& x_vals, const vector<long long>& y_vals) {
    int n = x_vals.size();
    double constant_term = 0.0;

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

double computePolynomialSecret(const map<string, map<string, string>>& data) {
    try {
        if (data.find("keys") == data.end()) {
            cerr << "Missing keys section in the input data." << endl;
            return 0;
        }

        int n = stoll(data.at("keys").at("n"));
        int k = stoll(data.at("keys").at("k"));

        vector<int> x_vals;
        vector<long long> y_vals;

        for (const auto& pair : data) {
            if (pair.first != "keys") {
                try {
                    int x = stoi(pair.first);
                    long long y = convertToDecimal(pair.second.at("value"), stoi(pair.second.at("base")));
                    x_vals.push_back(x);
                    y_vals.push_back(y);
                } catch (const exception& e) {
                    cerr << "Error processing key: " << pair.first << " - " << e.what() << endl;
                    continue;  // Skip the current entry if an error occurs
                }
            }
        }

        if (x_vals.size() < k) {
            cerr << "Insufficient data points to perform interpolation. Required: " << k << ", Provided: " << x_vals.size() << endl;
            return 0;
        }

        double constant_term = lagrangeInterpolation(x_vals, y_vals);

        return constant_term;

    } catch (const out_of_range& e) {
        cerr << "Out of range error: " << e.what() << endl;
        return 0;
    } catch (const exception& e) {
        cerr << "An error occurred: " << e.what() << endl;
        return 0;
    }
}

int main() {
    map<string, map<string, string>> sample_data = {
        {"keys", {{"n", "9"}, {"k", "6"}}},
        {"1", {{"base", "10"}, {"value", "28735619723837"}}},
        {"2", {{"base", "16"}, {"value", "1A228867F0CA"}}},
        {"3", {{"base", "12"}, {"value", "32811A4AA0B7B"}}},
        {"4", {{"base", "11"}, {"value", "917978721331A"}}},
        {"5", {{"base", "16"}, {"value", "1A22886782E1"}}},
        {"6", {{"base", "10"}, {"value", "28735619654702"}}},
        {"7", {{"base", "14"}, {"value", "71AB5070CC4B"}}},
        {"8", {{"base", "9"}, {"value", "122662581541670"}}},
        {"9", {{"base", "8"}, {"value", "642121030037605"}}}
    };

    double result = computePolynomialSecret(sample_data);
    cout << "The constant term of the polynomial is: " << result << endl;

    return 0;
}
