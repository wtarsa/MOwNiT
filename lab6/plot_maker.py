import matplotlib.pyplot as plt 
import matplotlib.patches as mpatches
from os import system

jac =[]
with open('jac.txt', 'r') as f:
    for item in f:
        jac.append(float(item));

gau =[]
with open('gau.txt', 'r') as f:
    for item in f:
        gau.append(float(item));

sor =[]
with open('sor.txt', 'r') as f:
    for item in f:
        sor.append(float(item));


axisX = []
for i in range(4, 31):
	axisX.append(i);



figure = plt.figure()
subplot = figure.add_subplot()
subplot.plot(axisX, jac, marker=',', label = "metoda Jacobiego")
subplot.plot(axisX, gau, marker=',', label = "metoda Gaussa-Seidela")
subplot.plot(axisX, sor, marker=',', label = "metoda SOR")

plt.legend(bbox_to_anchor=(0.55, 0.97), loc='upper left', borderaxespad=0.)

subplot.set_title("Porówanie tempa zbiegania do rozwiązania: równanie 3)")
subplot.set_xlabel('liczba iteracji')
subplot.set_ylabel('błąd')

plt.show()
