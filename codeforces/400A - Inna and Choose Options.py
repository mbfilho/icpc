t = int(raw_input())

for c in range(t):
	linha = raw_input()
	ans = []

	for row in range(1, 13):
		for col in range(1, 13):
			if row * col <> 12:
				continue
			conj = [''.join([linha[i+col*x] for x in range(row)]) for i in range(col)]

			if ''.join(row * ['X']) in conj:
				ans += [(row, col)]
	s = str(len(ans))
	

	for par in ans:
		s += ' %dx%d' % par
		
	print s


