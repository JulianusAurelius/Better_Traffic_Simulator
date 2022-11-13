import numpy as np
import matplotlib.pyplot as plt

mu, sigma = 28800, 3600
mu2, sigma2 = 61200, 3600
X1 = np.random.normal(mu, sigma, 43200)
X2 = np.random.normal(mu2, sigma2, 43200)
X = np.concatenate([X2, X1])
arr = plt.hist(X, bins='auto')
plt.show()
print(arr)
# X1 = np.random.normal(size = 100, loc = 648000, scale = 81000)
# print(X1[40000])

