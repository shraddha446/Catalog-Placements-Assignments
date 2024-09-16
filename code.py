import json
from sympy import symbols, Eq, solve

def convert_to_decimal(value, base):
    return int(value, base)

def interpolate_polynomial(x_vals, y_vals):
    x = symbols('x')
    num_points = len(x_vals)
    poly = 0

    for i in range(num_points):
        term = y_vals[i]
        for j in range(num_points):
            if i != j:
                term *= (x - x_vals[j]) / (x_vals[i] - x_vals[j])
        poly += term
    
    return poly

def extract_constant_term(poly):
    return poly.subs(symbols('x'), 0)

def compute_polynomial_secret(data):
    total_points = data["keys"]["n"]
    min_roots = data["keys"]["k"]
    
    x_vals = []
    y_vals = []
    
    for key, root in data.items():
        if key != "keys":
            x = int(key)
            y = convert_to_decimal(root["value"], int(root["base"]))
            x_vals.append(x)
            y_vals.append(y)
    
    poly = interpolate_polynomial(x_vals, y_vals)
    
    constant_value = extract_constant_term(poly)
    
    return constant_value
    
sample_data = {
    "keys": {
        "n": 4,
        "k": 3
    },
    "1": {"base": "10", "value": "4"},
    "2": {"base": "2", "value": "111"},
    "3": {"base": "10", "value": "12"},
    "6": {"base": "4", "value": "213"}
}

# Compute and print the constant term
result = compute_polynomial_secret(sample_data)
print(f"The value of C is: {result}")

