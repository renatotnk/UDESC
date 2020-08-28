import matplotlib.pyplot as plt
import numpy as np
import cv2

image = cv2.imread('aorta3.jpg', 0)
A = 165
B = 250

aorta = [[] for _ in range(len(image))]

for linha in range(len(image)):
	for pixel in image[linha]:
		if pixel < A or pixel > B:
			aorta[linha].append(0)
		else:
			aorta[linha].append(pixel)

aorta = np.array(aorta)
cv2.imwrite('aorta_isolada.jpg', aorta)
