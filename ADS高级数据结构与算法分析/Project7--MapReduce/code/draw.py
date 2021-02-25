import matplotlib.pyplot as plt
import math

y = [1, 200, 4000, 15910, 13237461, 47296200, 22702192]
for i in range(7):
    y[i] = math.log(y[i])

x1 = [0.006,
      0.008,
      0.009,
      0.031,
      8.284,
      29.44,
      14.038
      ]
x2 = [0.011,
      0.012,
      0.012,
      0.036,
      4.272,
      13.218,
      35.0928
      ]



for i in range(7):
    x1[i] = math.log(x1[i])**3
    x2[i] = math.log(x2[i])**3


plt.plot(y, x1, label='Serial', linewidth=3, color='black', marker='o', markerfacecolor='white', markersize=12)
plt.plot(y, x2, label='Parallel', linewidth=3, color='gray', marker='o', markerfacecolor='white', markersize=12)
plt.ylabel("running time")
plt.xlabel("word size")
plt.title("MapReduce Project")
plt.legend()
plt.show()
