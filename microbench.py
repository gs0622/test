import subprocess

cmd = ['adb', 'shell', '/data/local/micro_bench_static',
	'--no_print_each_iter', '--print_average', 'memcpy', '', '10']

def test_size(exponent, offset=0):
	return str(pow(2, exponent) + offset)

def test_memcpy(x, y=0):
	cmd[6] = test_size(x, y)
	mbench = subprocess.check_output(cmd)
	result = mbench.splitlines()[1].split()
	#print result[4]
	print result[1:]

def main():
	test_memcpy(5,0)
	test_memcpy(6)
	test_memcpy(7)
	test_memcpy(8)
	test_memcpy(9)
	test_memcpy(10)
	test_memcpy(11)
	test_memcpy(12)
	test_memcpy(13)
	test_memcpy(14)
	test_memcpy(15)
	test_memcpy(16)
	test_memcpy(17)
	test_memcpy(18)
	test_memcpy(19)
	test_memcpy(20)
	test_memcpy(21)
	test_memcpy(22)
	test_memcpy(23)

if __name__ == '__main__':
	main()
