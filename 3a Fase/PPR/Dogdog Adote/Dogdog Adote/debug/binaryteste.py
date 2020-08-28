string = b'kek'
print string

with open("testebinario.dat", "wb") as f:
	f.write(string)
