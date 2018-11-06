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

	parser = argparse.ArgumentParser(description='cold reboto stress out USB enumeration via remote ssh')
	parser.add_argument('--clean', dest='clean', type=bool, default=False, help='clean up log after test')
	parser.add_argument('--devices', dest='devices', type=str, default='0bda:8153', help='USB VID:PID')
	parser.add_argument('--loops', dest='loops', type=int, default=10, help='iterator loops')
	parser.add_argument('--remote', dest='remote', type=str, metavar='IP', default='10.5.232.37', help='rermote IP address')
	parser.add_argument('--sleep', dest='sleep', type=int, default=30, help='sleep seconds per test')
	args = parser.parse_args()
	print args

	prefix = ['sshpass', '-p', 'test0000', 'ssh', '-q',
		'-oStrictHostKeyChecking=no', '-oUserKnownHostsFile=/dev/null',
		'-oConnectTimeout=10', '-oServerAliveInterval=5' ]
	cmd1 = []
	cmds = ''
	devices = args.devices.split(',')
	lens = len(devices)
	for i in range(lens):
		cmds += 'lsusb -d ' + devices[i]
		if (i<lens-1):
			cmds += ' && '
	cmd1.append(cmds)

	cmd2 = ['sync; reboot']
	cmd3 = ['generate_logs']
	cmd4 = ['rm -rf /var/log/*']

	prefix.append("root@" + args.remote)

	retry = 0;
	for i in range(args.loops):
		try:
			now = str(datetime.datetime.fromtimestamp(time.time()))
			ret = subprocess.call(prefix + cmd1)
			print now, ": ", str(i).rjust(3), ": cmd: ", cmd1, ": ret:", ret

			now = str(datetime.datetime.fromtimestamp(time.time()))
			if ret == 0:
				subprocess.call(prefix + cmd2)
				#continue
			elif ret == 1:
				# wait 5 seconds
				time.sleep(5)
				subprocess.call(prefix + cmd3)
				break
			else:
				# wait 10 seconds
				time.sleep(10)
				if (++retry > 3):
					break
				continue

			now = str(datetime.datetime.fromtimestamp(time.time()))
			print now, ": ", str(i).rjust(3), ": slp: ", args.sleep
			time.sleep(args.sleep)

		except subprocess.CalledProcessError as err:
			now = str(datetime.datetime.fromtimestamp(time.time()))
			print now, ": ", str(i).rjust(3), ": error code: ", err.returncode
			break;

        if (args.clean == True):
                now = str(datetime.datetime.fromtimestamp(time.time()))
                ret = subprocess.call(prefix + cmd4, stdout=fnull)
                print now, ": ", str(i).rjust(3), ": cmd: ", cmd4, ": ret:", ret

	fnull.close()

if __name__ == '__main__':
	main()
