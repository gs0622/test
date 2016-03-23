#!/usr/bin/python
import time
import datetime
import subprocess
import argparse

def main():
	parser = argparse.ArgumentParser(description='grep "hello" string via remote ssh')
	parser.add_argument('--remote', dest='remote', type=str, metavar='IP', default='10.5.232.37', help='rermote IP address')
	parser.add_argument('--loops', dest='loops', type=int, default=10, help='iterator loops')
	args = parser.parse_args()
	print args

	prefix = ['sshpass', '-p', 'test0000', 'ssh',
		'-oStrictHostKeyChecking=no', '-oConnectTimeout=10',
		'-oServerAliveInterval=5' ]
	cmd1 = ['grep -rsI "hello" / --exclude={kmsg,pagemap} --exclude-dir=sys &> /dev/null']
	cmd2 = ['grep -rsI "hello" /sys --exclude-dir={usb,tracing,ehdaudio0D2} &> /dev/null']
	cmd3 = ['uptime']

	prefix.append("root@" + args.remote)

	for i in range(args.loops):
		now = str(datetime.datetime.fromtimestamp(time.time()))
		print now, ": ", str(i).rjust(4), ": cmd1: ", cmd1
		subprocess.call(prefix + cmd1)

		now = str(datetime.datetime.fromtimestamp(time.time()))
		print now, ": ", str(i).rjust(4), ": cmd2: ", cmd2
		subprocess.call(prefix + cmd2)

		now = str(datetime.datetime.fromtimestamp(time.time()))
		print now, ": ", str(i).rjust(4), ": cmd3: ", cmd3
		subprocess.call(prefix + cmd3)

if __name__ == '__main__':
	main()
