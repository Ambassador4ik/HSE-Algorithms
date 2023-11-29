import random
import math
import matplotlib.pyplot as plt
import pandas as pd


def generate_random_points(num_points):
    inside_circle = 0
    for _ in range(num_points):
        x = random.uniform(-1, 1)
        y = random.uniform(-1, 1)
        distance = x ** 2 + y ** 2
        if distance <= 1:
            inside_circle += 1
    return inside_circle


def approximate_pi(num_points):
    M = generate_random_points(num_points)
    pi_app = 4 * M / num_points
    return pi_app


# Params
start = 100
stop = 5000
step = 100

points_list = []
pi_values = []
errors = []


for N in range(start, stop + 1, step):
    pi_approx = approximate_pi(N)
    pi_values.append(pi_approx)
    points_list.append(N)
    error = abs((pi_approx - math.pi) / math.pi) * 100
    errors.append(error)

plt.figure(figsize=(8, 10))

# Graph 1
plt.subplot(2, 1, 1)
plt.plot(points_list, pi_values, marker='o')
plt.axhline(y=math.pi, color='r', linestyle='-')
plt.title('Approximation of π vs Number of Points')
plt.xlabel('Number of Points (N)')
plt.ylabel('Approximated π')
plt.grid(True)

# Graph 2
plt.subplot(2, 1, 2)
plt.plot(points_list, errors, marker='o', color='g')
plt.title('Relative Error in π Approximation vs Number of Points')
plt.xlabel('Number of Points (N)')
plt.ylabel('Relative Error (%)')
plt.grid(True)

plt.tight_layout()
plt.show()

# Create a DataFrame from the values
df = pd.DataFrame({
    'Number of Points (N)': points_list,
    'Approximated π': pi_values,
    'Relative Error (%)': errors
})

print(df)
