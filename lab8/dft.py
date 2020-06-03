import numpy as np
def DFT_slow(x):
    """Compute the discrete Fourier Transform of the 1D array x"""
    x = np.asarray(x, dtype=float)
    N = x.shape[0]
    n = np.arange(N)
    k = n.reshape((N, 1))
    M = np.exp(-2j * np.pi * k * n / N)
    return np.dot(M, x)

# x = np.random.random(1024)
# print(np.allclose(DFT_slow(x), np.fft.fft(x)))

x = []
with open('temp.txt', 'r') as f:
    for item in f:
        x.append(float(item));

myfft = []
with open('fft.txt', 'r') as ft:
    for item in ft:
        myfft.append(float(item));

result = np.fft.fft(x)

result_abs = []
for item in result:
	result_abs.append(abs(item))

print(np.allclose(myfft, result_abs))