import matplotlib.pyplot as plt 
import matplotlib.patches as mpatches
from mpl_toolkits.mplot3d import Axes3D

from os import system


x = []
with open('x.txt', 'r') as f:
    for item in f:
        x.append(float(item));

y = []
with open('y.txt', 'r') as f:
    for item in f:
        y.append(float(item));

z = []
with open('z.txt', 'r') as f:
    for item in f:
        z.append(float(item));


figure = plt.figure()
ax = figure.add_subplot(111, projection='3d')
ax.scatter(x, y, z)
plt.show()
