#!/usr/bin/python
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
import numpy as np
import cv2
from skimage.measure import compare_ssim as ssim
from skimage import exposure
from skimage import data
from skimage.viewer import ImageViewer

image1 = cv2.imread('fourier_1.jpg',0)
plt.hist(image1)
plt.savefig('antes.jpg')
plt.show()

####################### Equalizacao ##############################
image_eq = cv2.imread('fourier_1.jpg',0)
equ = cv2.equalizeHist(image_eq)
hist_e = plt.hist(equ)
plt.savefig('im1.jpg')
plt.show()

res = np.hstack((image_eq,equ))

cv2.imwrite('equalized.png',res)
cv2.imshow('eq',res)
cv2.waitKey(0)
cv2.destroyAllWindows()

####################### Log ##############################
image_2 = cv2.imread('fourier_1.jpg',0)
img_log = exposure.adjust_log(image_2, 1)

#img_log = (np.log(image_2+1)/(np.log(1+np.max(image_2))))*255
#img_log = np.array(img_log,dtype=np.uint8)

plt.hist(img_log)
plt.savefig('im2.jpg')
plt.show()

res_log = np.hstack((image_2,img_log))

cv2.imwrite('log.png',res_log)
cv2.imshow('ln',res_log)
cv2.waitKey(0)
cv2.destroyAllWindows()

#def adjust_gamma(image, gamma=1.0):
#	table = np.array([((i / 255.0) ** gamma) * 255 for i in np.arange(0, 256)])
#
#	return cv2.LUT(image.astype(np.uint8), table.astype(np.uint8))

####################### Gamma = 0.85 ##############################

original = cv2.imread('fourier_1.jpg',0)                            
adjusted = exposure.adjust_gamma(original, gamma=0.8, gain=1)

#adjusted = np.array(255*(original/255)**0.85,dtype='uint8')

plt.hist(adjusted)
plt.savefig('im3.jpg')
plt.show()

res_g_1 = np.hstack((original,adjusted))

cv2.imwrite('gamma_1.png',res_g_1)
cv2.imshow("gamma image 1", res_g_1)
cv2.waitKey(0)
cv2.destroyAllWindows()

####################### Gamma = 0.95 ##############################

original_2 = cv2.imread('fourier_1.jpg',0)
adjusted_2 = exposure.adjust_gamma(original, gamma=0.95, gain=1)

plt.hist(adjusted_2)
plt.savefig('im4.jpg')
plt.show()

res_g_2 = np.hstack((original,adjusted_2))

cv2.imwrite('gamma_2.png',res_g_2)
cv2.imshow("gamma image 2", res_g_2)
cv2.waitKey(0)
cv2.destroyAllWindows()


####################### Comparacoes ##############################

fig, axes = plt.subplots(nrows=1, ncols=5, figsize=(10, 4),
                         sharex=True, sharey=True)
ax = axes.ravel()

def mse(x, y):
    return np.linalg.norm(x - y)

best = cv2.imread('fourier_1_BestEnhanced.jpg',0)

mse_none = mse(best, best)
ssim_none = ssim(best, best, data_range=best.max() - best.min())

mse_eq = mse(best, equ)
ssim_eq = ssim(best, equ,
                  data_range=equ.max() - equ.min())

mse_log = mse(best, img_log)
ssim_log = ssim(best, img_log,
                  data_range=img_log.max() - img_log.min())

mse_g1 = mse(best, adjusted)
ssim_g1 = ssim(best, adjusted,
                  data_range=adjusted.max() - adjusted.min())

mse_g2 = mse(best, adjusted_2)
ssim_g2 = ssim(best, adjusted_2,
                  data_range=adjusted_2.max() - adjusted_2.min())

label = 'MSE: {:.2f}, SSIM: {:.2f}'

ax[0].imshow(best,cmap='gray', vmin=0, vmax=255)
ax[0].set_xlabel(label.format(mse_none, ssim_none))
ax[0].set_title('Best Enhanced image')

ax[1].imshow(equ,cmap='gray', vmin=0, vmax=255)
ax[1].set_xlabel(label.format(mse_eq, ssim_eq))
ax[1].set_title('Image with equalization')

ax[2].imshow(img_log,cmap='gray', vmin=0, vmax=255)
ax[2].set_xlabel(label.format(mse_log, ssim_log))
ax[2].set_title('Image with log')

ax[3].imshow(adjusted,cmap='gray', vmin=0, vmax=255)
ax[3].set_xlabel(label.format(mse_g1, ssim_g1))
ax[3].set_title('Image with gamma = 0.85')

ax[4].imshow(adjusted_2,cmap='gray', vmin=0, vmax=255)
ax[4].set_xlabel(label.format(mse_g2, ssim_g2))
ax[4].set_title('Image with gamma = 0.95')

plt.tight_layout()
plt.savefig('comparacao.jpg')
plt.show()

