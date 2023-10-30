import cv2
import numpy as np
import matplotlib.pyplot as plt

img = cv2.imread('output1_HistogramEqualization.bmp')
# img = cv2.imread('input1.bmp')

# 畫出 RGB 三種顏色的分佈圖
color = ('b','g','r')
for i, col in enumerate(color):
  histr = cv2.calcHist([img],[i],None,[256],[0, 256])
  print(histr[0])
  plt.plot(histr, color = col)
  plt.xlim([0, 256])
plt.show()