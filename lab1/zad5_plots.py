import matplotlib.pyplot as plt 
from os import system

stable_results =[]

with open('zad5_stable.txt', 'r') as f:
    for item in f:
        stable_results.append(float(item));

unstable_results =[]

with open('zad5_unstable.txt', 'r') as f:
    for item in f:
        unstable_results.append(float(item));


x_axis = [(-0.00001 + i*0.0000002) for i in range(101)]

figure = plt.figure()
stable_fig = figure.add_subplot()
stable_fig.plot(x_axis, stable_results, marker='o', markevery=int(1e7/25000))

stable_fig.set_xlabel('argument x')
stable_fig.set_ylabel('Wartość funkcji')

figure2 = plt.figure()
unstable_fig = figure2.add_subplot()
unstable_fig.plot(x_axis, unstable_results, marker='o', markevery=int(1e7/25000))

unstable_fig.set_xlabel('argument x')
unstable_fig.set_ylabel('Wartość funkcji')

plt.show()
