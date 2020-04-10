import matplotlib.pyplot as plt 
from os import system

axisY =[]
with open('resultsY.txt', 'r') as f:
    for item in f:
        axisY.append(float(item));

axisYfunc =[]
with open('results.txt', 'r') as f:
    for item in f:
        axisYfunc.append(float(item));


axisX = []
with open('resultsX.txt', 'r') as f:
    for item in f:
        axisX.append(float(item));




figure = plt.figure()
subplot = figure.add_subplot()
subplot.plot(axisX, axisY, marker=',')
subplot.plot(axisX, axisYfunc, marker=',')

subplot.set_title("Interpolacja metodą Hermite'a - liczba węzłów N = 20")
subplot.set_xlabel('oś X')
subplot.set_ylabel('oś Y')

plt.show()
