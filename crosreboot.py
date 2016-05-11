#!/usr/bin/python
import time
import datetime
import subprocess
import argparse

def main():
	parser = argparse.ArgumentParser(description='reboot via remote ssh')
	parser.add_argument('--remote', dest='remote', type=str, metavar='IP', default='10.5.232.37', help='rermote IP address')
	parser.add_argument('--sleep', dest='sleep', type=int, default=10, help='sleep seconds per test')
	parser.add_argument('--loops', dest='loops', type=int, default=10, help='iterator loops')
	args = parser.parse_args()
	print args

	prefix = ['sshpass', '-p', 'test0000', 'ssh',
		'-oStrictHostKeyChecking=no', '-oConnectTimeout=10',
		'-oServerAliveInterval=10' ]
	cmd0 = ['reboot; exit']
	prefix.append("root@" + args.remote)

	for i in range(args.loops):
		try:
			now = str(datetime.datetime.fromtimestamp(time.time()))
			print now, ": ", ": cmd0: ", cmd0
			subprocess.call(prefix + cmd0)

			now = str(datetime.datetime.fromtimestamp(time.time()))
			print now, ": ", str(i).rjust(4), ": sleep: ", args.sleep
			time.sleep(args.sleep)

		except subprocess.CalledProcessError as err:
			now = str(datetime.datetime.fromtimestamp(time.time()))
			print now, ": ", str(i).rjust(4), ": error code: ", err.returncode
			break;

if __name__ == '__main__':
	main()
