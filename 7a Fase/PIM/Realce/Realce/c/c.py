#!/usr/bin/python
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
import numpy as np
import cv2
from skimage import exposure

img = cv2.imread('figuraEscura.jpg')

img_log = (np.log(img+1)/(np.log(1+np.max(img))))*255
img2 = np.array(img_log,dtype=np.uint8)

res = np.hstack((img,img2))

cv2.imwrite('escura_log.png',res)
cv2.imshow('log',res)
cv2.waitKey(0)
cv2.destroyAllWindows()

###########################################################################

imagem = cv2.imread('figuraClara.jpg')

imagem = 255 - imagem
img_log = (np.exp(imagem+1)/(np.exp(1+np.max(imagem))))*255
img3 = np.array(img_log,dtype=np.uint8)

res_2 = np.hstack((imagem,img3))

#cv2.imwrite('clara_e.png',res_2)
cv2.imshow('exp',res_2)
cv2.waitKey(0)
cv2.destroyAllWindows()
