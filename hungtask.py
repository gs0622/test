#!/usr/bin/python
import sys
import time
import datetime
import subprocess

def main():
	loops = 10
	remote = "10.174.88.78"
	prefix = ['sshpass', '-p', 'test0000', 'ssh',
		'-oStrictHostKeyChecking=no', '-oConnectTimeout=5' ]
	cmd1 = ['echo 5 > /proc/sys/kernel/hung_task_timeout_secs']
	cmd2 = ['cat /proc/sys/kernel/hung_task_timeout_secs']
	cmd3 = ['echo HUNG_TASK > /sys/kernel/debug/provoke-crash/DIRECT &']
	cmd4 = ['dmesg | tail -3']

	if len(sys.argv) > 1:
		remote = sys.argv[1]

	if len(sys.argv) > 2:
		loops = int(sys.argv[2])

	prefix.append("root@" + remote)

	for i in range(loops):
		try:
			now = str(datetime.datetime.fromtimestamp(time.time()))
			print now, " cmd1: ", cmd1
			ret = subprocess.check_output(prefix + cmd1)

			now = str(datetime.datetime.fromtimestamp(time.time()))
			print now, " cmd2: ", cmd2
			ret = subprocess.check_output(prefix + cmd2)
			now = str(datetime.datetime.fromtimestamp(time.time()))
			print now + " hung_task_timeout_secs=" + ret

			now = str(datetime.datetime.fromtimestamp(time.time()))
			print now, " cmd3: ", cmd3
			subprocess.call(prefix + cmd3)


			now = str(datetime.datetime.fromtimestamp(time.time()))
			print now, " cmd4: ", cmd4
			ret = subprocess.check_output(prefix + cmd4)
			now = str(datetime.datetime.fromtimestamp(time.time()))
			print now, " dmesg=\n", ret

			time.sleep(10)

		except subprocess.CalledProcessError as err:
			print "error code: ", err.returncode
			break;

if __name__ == '__main__':
	main()
