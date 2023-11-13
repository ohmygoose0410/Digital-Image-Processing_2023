import numpy as np
import matplotlib.pyplot as plt
import cv2

def dnorm(x, mu, sd):
    return 1 / (np.sqrt(2 * np.pi) * sd) * np.e ** (-np.power((x - mu) / sd, 2) / 2)

def gaussian_kernel(size, sigma=1, verbose=False):
 
    kernel_1D = np.linspace(-(size // 2), size // 2, size)
    for i in range(size):
        kernel_1D[i] = dnorm(kernel_1D[i], 0, sigma)
    kernel_1D /= np.sum(kernel_1D)
    print("kernel 1D: ", kernel_1D)
    print("sum: ", np.sum(kernel_1D))
    kernel_2D = np.outer(kernel_1D.T, kernel_1D.T)
 
    # kernel_2D /= np.sum(kernel_2D)
 
    if verbose:
        plt.imshow(kernel_2D, interpolation='none',cmap='gray')
        plt.title("Image")
        plt.show()
 
    return kernel_2D

kernel = gaussian_kernel(5, 10)
print(kernel)
print(np.sum(kernel))

img=np.zeros((7,7))
img[3,3]=1

img1 = cv2.GaussianBlur(img, (5, 5), 10)
print(img1)
print(np.sum(img1))