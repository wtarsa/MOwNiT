import matplotlib.pyplot as plt 
import matplotlib.patches as mpatches
from os import system

fft = []
with open('fft.txt', 'r') as f:
    for item in f:
        fft.append(float(item));

axisX = []
with open('freq.txt', 'r') as f:
    for item in f:
        axisX.append(float(item));



figure = plt.figure()
subplot = figure.add_subplot()
subplot.scatter(axisX, fft, label = "FFT")


subplot.set_title("Średnia temperatura w Polsce od 26.05.20 do 31.05.20 7:00")
subplot.set_xlabel('Częstotliwość [1/h]')
subplot.set_ylabel("Wartość funkcji")

plt.show()
