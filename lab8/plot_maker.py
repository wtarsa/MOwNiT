import matplotlib.pyplot as plt 
import matplotlib.patches as mpatches
from os import system

dft = [160, 660, 1691, 6132, 23437, 93208, 361608, 1437868, 5756818, 22833367]
fft = [19, 75, 94, 201, 431, 917, 2031, 5551, 9035, 18986]

axisX = [32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384]
# axisX = []
# for i in range(1, 11):
# 	axisX.append(i);



figure = plt.figure()
subplot = figure.add_subplot()
subplot.scatter(axisX, dft, label = "DFT")
subplot.scatter(axisX, fft, label = "FFT")


plt.legend(bbox_to_anchor=(0.03, 0.97), loc='upper left')

subplot.set_title("Porównanie czasu wykonania metod DFT i FFT")
subplot.set_xlabel('Wielokość zbioru danych')
subplot.set_ylabel("czas wykonania[μs]")

plt.show()
