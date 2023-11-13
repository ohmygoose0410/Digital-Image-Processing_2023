import numpy as np
from PIL import Image

img = Image.open("../testdata/test.bmp")
img_arr = np.array(img)
img_shape = img_arr.shape

globalMean_c1 = np.sum(img_arr[:,:,0])
globalMean_c2 = np.sum(img_arr[:,:,1])
globalMean_c3 = np.sum(img_arr[:,:,2])

globalMean_c1 /= img_shape[0] * img_shape[1]
globalMean_c2 /= img_shape[0] * img_shape[1]
globalMean_c3 /= img_shape[0] * img_shape[1]

print(globalMean_c1)
print(globalMean_c2)
print(globalMean_c3)