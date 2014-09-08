#!/usr/bin/python
import re

def main():
    f = open('/proc/cpuinfo','r')
    s = f.read()
    print s
    #re_obj = re.compile("(: \S+)")
    #for match in re_obj.findall(s):
    #    print match
    #match = re.search("processor\\t: ", s)
    #if match:
    #    print match
    f.close()

if __name__ == '__main__':
    main()

