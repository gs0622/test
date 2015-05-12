import subprocess

cmd = ['adb', 'shell', '/data/local/micro_bench_static',
	'--no_print_each_iter', '--print_average', 'memcpy', '', '10']

def memcpy_test(x):
	cmd[6] = str(pow(2, x))
	#print cmd
	subprocess.call(cmd)

def main():
	memcpy_test(5)
	memcpy_test(6)
	memcpy_test(7)
	memcpy_test(8)
	memcpy_test(9)
	memcpy_test(10)
	memcpy_test(11)
	memcpy_test(12)
	memcpy_test(13)
	memcpy_test(14)
	memcpy_test(15)
	memcpy_test(16)
	memcpy_test(17)
	memcpy_test(18)
	memcpy_test(19)
	memcpy_test(20)
	memcpy_test(21)
	memcpy_test(22)
	memcpy_test(23)

if __name__ == '__main__':
	main()
