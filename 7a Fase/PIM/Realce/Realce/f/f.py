import numpy as np
import skimage
import cv2
import matplotlib.pyplot as plt
from skimage import io, exposure
from skimage.color import rgb2gray

rgb = io.imread("Niteroi.jpg")
rgb = cv2.resize(rgb, (800,600))
rgb_grayscale = cv2.cvtColor(rgb, cv2.COLOR_BGR2GRAY)
print("Salvando Histograma RGB - Antes")
plt.hist(rgb_grayscale)
plt.savefig('RGB-antes.jpg')
plt.show()

rgb_grayscale_eq = cv2.equalizeHist(rgb_grayscale)
print("Salvando  Histograma RGB - Depois")
plt.hist(rgb_grayscale_eq)
plt.savefig('RGB-Depois.jpg')
plt.show()


yiq = skimage.color.rgb2yiq(rgb)

print("Salvando  Histograma YIQ - Antes")
plt.hist(yiq[:, :, 0])
plt.savefig('YIQ-Antes.jpg')
plt.show()

yiq[:, :, 0] = exposure.equalize_hist(yiq[:, :, 0])

print("Salvando  Histograma Y'IQ - Depois")
plt.hist(yiq[:, :, 0])
plt.savefig('YIQ-Depois.jpg')
plt.show()
final = skimage.color.yiq2rgb(yiq)

print("Salvando  imagem Y'IQ - Equalizada")
plt.imshow(yiq)
plt.imsave('YIQ-Equalizada.png', yiq)

print("Salvando  imagem YIQ - Equalizada - RGB")
plt.imshow(final)
plt.imsave('YIQ-Equalizada-RGB.png', final)


#https://stackoverflow.com/questions/46990838/numpy-transforming-rgb-image-to-yiq-color-space
#https://stackoverflow.com/questions/31998428/opencv-python-equalizehist-colored-image
#https://stackoverflow.com/questions/44554125/python-want-to-display-red-channel-only-in-opencv
