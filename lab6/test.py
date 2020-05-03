import numpy as np

# A = np.matrix([[0.0001, -5.0300, 5.8090, 7.8320],
#                [2.2660, 1.9950,  1.2120, 8.0080],
#                [8.8500, 5.6810,  4.5520, 1.3020],
#                [6.7750, -2.253,  2.9080, 3.9700]])

# b = np.matrix([9.5740, 7.2190, 5.7300, 6.2910]).transpose()

A = np.matrix([[10, -1, 2, 0],
			   [-1, 11, -1, 3],
			   [2, -1, 10, -1],
			   [0, 3, -1, 8]])
b = np.matrix([6, 25, -11, 15]).transpose()

x = np.linalg.solve(A, b)
 
print(np.allclose(np.dot(A, x), b))
print(x)