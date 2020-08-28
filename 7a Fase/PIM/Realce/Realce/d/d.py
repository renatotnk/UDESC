#!/usr/bin/python
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
import numpy as np
import cv2

image = cv2.imread('gonzalez3_10.png',0)
hist_i = plt.hist(image)
plt.show()
plt.clf()

equ = cv2.equalizeHist(image)
hist_e = plt.hist(equ)
plt.show()
plt.clf()

#Colocando imagens lado a lado para comparacao
res = np.hstack((image,equ))

cv2.imwrite('eq.png',res)
cv2.imshow('eq',res)
cv2.waitKey(0)
cv2.destroyAllWindows()
