import subprocess
import time

def main():
	for i in range(100):
		print i
		subprocess.call(["adb", "reboot"])
		time.sleep(60)

if __name__ == '__main__':
	main()
