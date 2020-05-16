import matplotlib.pyplot as plt 
import matplotlib.patches as mpatches
from os import system

# axisX = [128, 1024, 4096, 8192, 20000, 100000]
# points = [3.281250, 3.167969, 3.145508, 3.179199, 3.159400, 3.145680]

axisX = []
for i in range(1, 1000):
	axisX.append(i*100);

points = []
with open('points.txt', 'r') as f:
    for item in f:
        points.append(float(item));


figure = plt.figure()
subplot = figure.add_subplot()
subplot.plot(axisX, points, label = "metoda prostokątów")

# plt.legend(bbox_to_anchor=(0.6, 0.2), loc='upper left', borderaxespad=0.)

subplot.set_title("Wartość liczby PI w zależności od liczby punktów losowych")
subplot.set_xlabel('liczba punktów losowych')
subplot.set_ylabel("wartość liczby PI")

plt.show()
