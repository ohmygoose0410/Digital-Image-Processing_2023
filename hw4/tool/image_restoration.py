import numpy as np
import cv2
import matplotlib.pyplot as plt

def pad(image, pad_size):

    height, width, channels = image.shape

    padded_image = np.zeros((height + 2 * pad_size, width + 2 * pad_size, channels), dtype=np.uint8)

    padded_image[pad_size:height + pad_size, pad_size:width + pad_size, :] = image

    padded_image[:pad_size, pad_size:width + pad_size, :] = np.flipud(image[:pad_size, :, :])
    padded_image[height + pad_size:, pad_size:width + pad_size, :] = np.flipud(image[height - pad_size:, :, :])

    padded_image[:, :pad_size, :] = np.fliplr(padded_image[:, pad_size:2 * pad_size, :])
    padded_image[:, width + pad_size:, :] = np.fliplr(padded_image[:, width:width + pad_size, :])

    return padded_image

def dnorm(x, mu, sd):
    return 1 / (np.sqrt(2 * np.pi) * sd) * np.e ** (-np.power((x - mu) / sd, 2) / 2)

def gaussian_kernel(size, sigma=1, verbose=False):
 
    kernel_1D = np.linspace(-(size // 2), size // 2, size)
    for i in range(size):
        kernel_1D[i] = dnorm(kernel_1D[i], 0, sigma)
    kernel_1D /= np.sum(kernel_1D)
    kernel_2D = np.outer(kernel_1D.T, kernel_1D.T)
 
    if verbose:
        plt.imshow(kernel_2D, interpolation='none',cmap='gray')
        plt.title("Image")
        plt.show()
 
    return kernel_2D

# Code for computing constrained l s filter - own code
def constrained_ls_filter(image, psf, gamma):
    psf_M = psf.shape[0]
    psf_N = psf.shape[1]
    # zero pad the psf in space domain to match the image size
    psf_padded = np.zeros_like(image[:, :, 0], dtype=np.float64)
    psf_padded[0:psf_M, 0:psf_N] = psf
    psf_padded = psf_padded / np.sum(psf_padded)

    # define laplacian matrix and zero pad it
    laplacian = np.array([[0, -1, 0], [-1, 4, -1], [0, -1, 0]], dtype=int)
    laplacian_padded = np.zeros_like(image[:, :, 0], dtype=int)
    laplacian_padded[0:3, 0:3] = laplacian

    result = np.zeros_like(image)
    # compute dft of psf - H
    psf_dft = np.fft.fft2(psf_padded)
    # compute dft of laplacian - P
    laplacian_dft = np.fft.fft2(laplacian_padded)

    laplacian_dft_abs = np.square(np.abs(laplacian_dft))
    psf_dft_abs = np.square(np.abs(psf_dft))
    temp1 = np.divide(psf_dft_abs, psf_dft_abs + gamma * laplacian_dft_abs)

    # compute F = (G/H) * (|H|^2 / (|H|^2 + gamma * P)) for each channel i.e. R, G and B separately
    for i in range(0, 3):
        image_dft = np.fft.fft2(image[:, :, i])
        temp2 = np.divide(image_dft, psf_dft)
        temp = np.abs(np.fft.ifft2(np.multiply(temp1, temp2)))
        result[:, :, i] = temp.astype(np.uint8)

    return result

def weiner_filter(image, psf, K):
    psf_M = psf.shape[0]
    psf_N = psf.shape[1]
    # zero pad the psf in space domain to match the image size
    psf_padded = np.zeros_like(image[:, :, 0], dtype=np.float64)
    psf_padded[0:psf_M, 0:psf_N] = psf
    psf_padded = psf_padded / np.sum(psf_padded)

    result = np.zeros_like(image)
    # compute dft of psf - H
    psf_dft = np.fft.fft2(psf_padded)

    # plt.imshow(np.log1p(np.abs(np.fft.fftshift(psf_dft))), cmap='gray')
    # plt.axis('off')
    # plt.show()

    # compute F = (G/H) * (|H|^2 / (|H|^2 + K)) for each channel i.e. R, G and B separately
    for i in range(0, 3):
        image_dft = np.fft.fft2(image[:, :, i])
        psf_dft_abs = np.abs(psf_dft)
        psf_dft_abs = np.square(psf_dft_abs)
        
        temp1 = np.divide(psf_dft_abs, psf_dft_abs + K * np.ones_like(image_dft))
        temp2 = np.divide(image_dft, psf_dft)
        
        temp = np.multiply(temp1, temp2)
        temp = np.abs(np.fft.ifft2(temp))
        result[:, :, i] = temp.astype(np.uint8)

    return result

# Code for computing psnr - own code
def psnr(image_original, image_restored):
    M = image_original.shape[0]
    N = image_original.shape[1]

    # compute psnr as 10log10(MAX^2/MSE)
    mse = np.sum(np.square(image_original - image_restored)) / (M * N) + 0.0000001
    max = 255**2
    psnr = 10 * np.log10(max/mse)

    return psnr

path1 = r'.\images\input1_ori.bmp'
path2 = r'.\images\input1.bmp'
path3 = r'.\images\input2.bmp'

m_kernel_size = 23
angle = -45
m_k = 0.1

g_kernel_size = 11
g_kernel = gaussian_kernel(g_kernel_size, 15)
g_k = 0.01

image_org = cv2.imread(path1)
image_blur = cv2.imread(path2)
image2_blur = cv2.imread(path3)

tar_image = image_blur
tar_shape = tar_image.shape

m_kernel = np.zeros((m_kernel_size, m_kernel_size))
theta = np.radians(angle)
center = m_kernel_size // 2

for i in range(m_kernel_size):
    x = i - center
    for j in range(m_kernel_size):
        y = j - center
        if np.abs(np.sin(theta) * x - np.cos(theta) * y) < 1:
            m_kernel[i, j] = 1

padding_size = m_kernel_size
tar_image_pad = pad(tar_image, padding_size)
f = weiner_filter(tar_image_pad, m_kernel, m_k)
f = f[padding_size:-padding_size, padding_size:-padding_size,:]

padding_size = g_kernel_size
f_pad = pad(f, padding_size)
t = weiner_filter(f_pad, g_kernel, g_k)
t = t[padding_size:-padding_size, padding_size:-padding_size,:]

print("before_PSNR: ", psnr(image_org, image_blur))
print("f_PSNR: ", psnr(image_org, f))
print("t_PSNR: ", psnr(image_org, t))

im_h = cv2.hconcat([tar_image, f, t])
im_h = cv2.resize(im_h, (0,0), fx=1, fy=1)
cv2.imshow('IMG', im_h)
cv2.waitKey(0)
cv2.destroyAllWindows()