#!/usr/bin/python
import time
import datetime
import subprocess
import argparse

def main():
	parser = argparse.ArgumentParser(description='perform "HUNG_TASK" test via remote ssh')
	parser.add_argument('--remote', dest='remote', type=str, metavar='IP', default='10.5.232.37', help='rermote IP address')
	parser.add_argument('--loops', dest='loops', type=int, default=10, help='iterator loops')
	parser.add_argument('--sleep', dest='sleep', type=int, default=30, help='sleep seconds per test')
	args = parser.parse_args()
	print args

	prefix = ['sshpass', '-p', 'test0000', 'ssh', '-q',
		'-oStrictHostKeyChecking=no', '-oUserKnownHostsFile=/dev/null',
		'-oConnectTimeout=10', '-oServerAliveInterval=5' ]
	cmd1 = ['echo 3 > /proc/sys/kernel/hung_task_timeout_secs']
	cmd2 = ['cat /proc/sys/kernel/hung_task_timeout_secs']
	cmd3 = ['echo HUNG_TASK > /sys/kernel/debug/provoke-crash/DIRECT &']
	cmd4 = ['dmesg | tail -3']
	cmd5 = ['i=1; while true; do echo $i; let i++; sleep 1; done']

	prefix.append("root@" + args.remote)

	for i in range(args.loops):
		try:
			now = str(datetime.datetime.fromtimestamp(time.time()))
			print now, ": ", str(i).rjust(4), ": cmd1: ", cmd1
			ret = subprocess.check_output(prefix + cmd1)

			now = str(datetime.datetime.fromtimestamp(time.time()))
			print now, ": ", str(i).rjust(4), ": cmd2: ", cmd2
			ret = subprocess.check_output(prefix + cmd2)
			now = str(datetime.datetime.fromtimestamp(time.time()))
			print now, ": ", str(i).rjust(4), ": hung_task_timeout_secs:", ret

			now = str(datetime.datetime.fromtimestamp(time.time()))
			print now, ": ", str(i).rjust(4), ": cmd3: ", cmd3
			subprocess.call(prefix + cmd3)

			now = str(datetime.datetime.fromtimestamp(time.time()))
			print now, ": ", str(i).rjust(4), ": cmd4: ", cmd4
			ret = subprocess.check_output(prefix + cmd4)
			now = str(datetime.datetime.fromtimestamp(time.time()))
			print now, ": ", str(i).rjust(4), ": dmesg:\n", ret

			now = str(datetime.datetime.fromtimestamp(time.time()))
			print now, ": ", str(i).rjust(4), ": cmd5: ", cmd5
			subprocess.call(prefix + cmd5)

			now = str(datetime.datetime.fromtimestamp(time.time()))
			print now, ": ", str(i).rjust(4), ": sleep: ", args.sleep
			time.sleep(args.sleep)

		except subprocess.CalledProcessError as err:
			now = str(datetime.datetime.fromtimestamp(time.time()))
			print now, ": ", str(i).rjust(4), ": error code: ", err.returncode
			break;

if __name__ == '__main__':
	main()
