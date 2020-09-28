notas = [262, 294, 330, 349, 392, 440, 494, 523]
p = [1, 8, 64, 256, 1024]

f = []

for i in range(len(notas)):
	for j in range(len(p)):
		f.append((1000000 / ((2*notas[i]) * p[j]) - 1))

h = 0
for item in f:
	print hex(item)
	h += 1
	if h == 5:
		print ""
		h = 0

