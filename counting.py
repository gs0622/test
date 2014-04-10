#!/usr/bin/python
import sys
import math
import random

class Foo:
    """ Foo test module """
    name = 'Foo test module'
    size = 10
    def __init__(self, sz=None):
        if (sz != None): self.size = sz
        Foo.reset(self)
    def reset(self):
        self.code = random.sample(xrange(self.size*10), self.size)
    def get(self):
        return self.code
    def counting(self, a=None):
        if a == None: a = self.code
        c = [0 for i in range(self.size*10)]
        #print c
        for i in range(len(a)):
            #print a[i]
            c[a[i]]+=1
        for i in range(self.size*10):
            c[i]+=c[i-1]
            #print str(c[i])+' '
        b=a[:]
        for i in range(len(a),0,-1):
            a[c[b[i-1]]-1]=b[i-1]
            #print a
            c[b[i-1]]-=1
def main():
    sys.setrecursionlimit(1000)
    if len(sys.argv) > 1:
        a = Foo(int(sys.argv[1]))
    else:
        a=Foo()
    print ('orig: '+str(a.get()))
    a.counting(a.get())
    print ('sort: '+str(a.get()))
if __name__ == '__main__':
    main()
