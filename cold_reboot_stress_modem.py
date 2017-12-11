#!/usr/bin/python
import os
import sys
import time
import datetime
import subprocess
import argparse

def main():
	fnull = open(os.devnull,"w")
	ret = subprocess.call(["which", "sshpass"], stdout=fnull, stderr=subprocess.STDOUT)
	if ret == 1:
		print "'sshpass' is required."
		sys.exit(0)
	ret = subprocess.call(["which", "ssh"], stdout=fnull, stderr=subprocess.STDOUT)
	if ret == 1:
		print "'openssh-client' is required."
		sys.exit(0)
	fnull.close()

	parser = argparse.ArgumentParser(description='stress out late USB modem enumeration via remote ssh')
	parser.add_argument('--remote', dest='remote', type=str, metavar='IP', default='10.5.232.37', help='rermote IP address')
	parser.add_argument('--loops', dest='loops', type=int, default=10, help='iterator loops')
	parser.add_argument('--sleep', dest='sleep', type=int, default=30, help='sleep seconds per test')
	args = parser.parse_args()
	print args

	prefix = ['sshpass', '-p', 'test0000', 'ssh', '-q',
		'-oStrictHostKeyChecking=no', '-oUserKnownHostsFile=/dev/null',
		'-oConnectTimeout=10', '-oServerAliveInterval=5' ]
	cmd1 = ['lsusb -d 2cb7:0007']
	cmd2 = ['ectool reboot_ec cold']
	cmd3 = ['generate_logs']

	prefix.append("root@" + args.remote)

	for i in range(args.loops):
		try:
			now = str(datetime.datetime.fromtimestamp(time.time()))
			ret = subprocess.call(prefix + cmd1)
			print now, ": ", str(i).rjust(3), ": cmd: ", cmd1, ": ret:", ret

			now = str(datetime.datetime.fromtimestamp(time.time()))
			if ret == 0:
				subprocess.call(prefix + cmd2)
			elif ret == 1:
				# wait 200 seconds
				time.sleep(200)
				subprocess.call(prefix + cmd3)
				break
			else:
				continue

			now = str(datetime.datetime.fromtimestamp(time.time()))
			print now, ": ", str(i).rjust(3), ": slp: ", args.sleep
			time.sleep(args.sleep)

		except subprocess.CalledProcessError as err:
			now = str(datetime.datetime.fromtimestamp(time.time()))
			print now, ": ", str(i).rjust(3), ": error code: ", err.returncode
			break;

if __name__ == '__main__':
	main()
