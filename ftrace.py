#!/usr/bin/python
import time
import datetime
import subprocess
import argparse

def main():
	parser = argparse.ArgumentParser(description='grep "hello" string via remote ssh')
	parser.add_argument('--remote', dest='remote', type=str, metavar='IP', default='10.5.232.37', help='rermote IP address')
	args = parser.parse_args()
	print args

	prefix = ['sshpass', '-p', 'test0000', 'ssh',
		'-oStrictHostKeyChecking=no', '-oConnectTimeout=10',
		'-oServerAliveInterval=5' ]
	cmd1 = ['echo function > /sys/kernel/debug/tracing/current_tracer']
	cmd2 = ['echo 1 > /sys/kernel/debug/tracing/tracing_on']
	cmd3 = ['cat /sys/kernel/debug/tracing/trace']

	prefix.append("root@" + args.remote)

	now = str(datetime.datetime.fromtimestamp(time.time()))
	print now, ": ", ": cmd1: ", cmd1
	subprocess.call(prefix + cmd1)

	now = str(datetime.datetime.fromtimestamp(time.time()))
	print now, ": ", ": cmd2: ", cmd2
	subprocess.call(prefix + cmd2)

	now = str(datetime.datetime.fromtimestamp(time.time()))
	print now, ": ", ": cmd3: ", cmd3
	subprocess.call(prefix + cmd3)

if __name__ == '__main__':
	main()
