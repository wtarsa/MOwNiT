import matplotlib.pyplot as plt 
import matplotlib.patches as mpatches
from os import system

# rec = [0.30703, 10.39500, 1.13304, 1.11132, 0.71514]
# tra = [0.32203, 9.04500, 1.11233, 1.09061, 0.64443]
# sim = [0.32175, 9.00000, 1.11145, 1.08943, 0.64379]

# rec = [0.30703, 1.13304, 1.11132, 0.71514]
# tra = [0.32203, 1.11233, 1.09061, 0.64443]
# sim = [0.32175, 1.11145, 1.08943, 0.64379]

rec = [95.426, 115.500, 101.943, 102.009, 111.083]
tra = [100.088, 100.500, 100.079, 100.108, 100.099]
sim = [100, 100, 100, 100, 100]
mcr = [114.429, 64.986, 96.152, 96.624, 70.250]
# with open('jac.txt', 'r') as f:
#     for item in f:
#         jac.append(float(item));

axisX = []
for i in range(1, 6):
	axisX.append(i);



figure = plt.figure()
subplot = figure.add_subplot()
subplot.scatter(axisX, rec, label = "metoda prostokątów")
subplot.scatter(axisX, tra, label = "metoda trapezów")
subplot.scatter(axisX, sim, label = "metoda Simpsona")
subplot.scatter(axisX, mcr, label = "metoda Monte Carlo")

plt.legend(bbox_to_anchor=(0.5, 0.3), loc='upper left', borderaxespad=0.)

subplot.set_title("Porównanie wyniku otrzymanego do wyniku dokładnego")
subplot.set_xlabel('numer funkcji testowej')
subplot.set_ylabel("% dokładniego wyniku")

plt.show()
