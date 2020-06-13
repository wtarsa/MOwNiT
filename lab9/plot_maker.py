import matplotlib.pyplot as plt 
import matplotlib.patches as mpatches
from os import system

sol = [0.374718, 0.374718, 0.374718, 0.374718, 0.374718]
eul = [0.373005, 0.375569, 0.375285, 0.374289, 0.374375]
rk = [0.368915, 0.370964, 0.37233, 0.373015, 0.374384]

axisX = [0.025, 0.0125, 0.00833333, 0.00625, 0.005]


figure = plt.figure()
subplot = figure.add_subplot()
subplot.scatter(axisX, sol, label = "poprawne rozwiązanie")
subplot.scatter(axisX, eul, label = "metoda Eulera")
subplot.scatter(axisX, rk, label = "metoda RK2")


plt.legend(bbox_to_anchor=(0.50, 0.30), loc='upper left')

subplot.set_title("Otrzymane rozwiązania równania w zależności od wielkości kroku iteracyjnego")
subplot.set_xlabel('wielkość kroku iteracyjnego')
subplot.set_ylabel("rozwiązanie")

plt.show()
