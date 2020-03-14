import matplotlib.pyplot as plt 
from os import system

errors =[]

with open('zad1_wyniki.txt', 'r') as f:
    for item in f:
        errors.append(float(item));


steps = [i*25000 for i in range(len(errors))]

figure = plt.figure()
subplot = figure.add_subplot()
subplot.plot(steps, errors, marker='o', markevery=int(1e7/25000))

subplot.set_xlabel('Liczba wykonanych operacji')
subplot.set_ylabel('Wartość błędu względnego')

plt.show()
