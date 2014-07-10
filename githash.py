#!/usr/bin/python
import os
import sys
from hashlib import sha1
def githash(data):
    s = sha1()
    s.update("blob %u\0" % len(data))
    s.update(data)
    #s.update("blob " + str(len(data)) + "\0" + data)
    return s.hexdigest()

def main():
    fl = sys.argv[1]
    sz = os.path.getsize(fl)
    fp = open(fl)
    tx = fp.read()
    print githash(tx)
    #print ('blob ' + str(sz) + '\0' + tx)
    fp.close()
if __name__ == '__main__':
    main()
