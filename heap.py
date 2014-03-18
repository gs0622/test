#!/usr/bin/python
import sys
import math
import random

class Foo:
    """ Foo test module """
    name = 'Foo test module'
    size = 10
    step = 0
    bigo = 0
    def __init__(self, sz=None):
        if (sz != None): self.size = sz
        Foo.reset(self)
    def reset(self):
        self.code = random.sample(xrange(self.size*10), self.size)
        self.step = 0
        self.bigo = self.size * math.log(self.size,2)
    def get(self):
        return self.code
    def bubble(self):
        """ worst: O(n^2), best: O(n), avg: O(n^2) """
        for i in range(len(self.code)-1,0,-1):
            for j in range(0,i,1):
                if self.code[j]>self.code[j+1]:
                    self.code[j],self.code[j+1]=self.code[j+1],self.code[j]
    def __heap_sort(lst):
        for start in range((len(lst)-2)/2,-1,-1):
            sift_down(lst,start,len(lst)-1)
     
        for end in range(len(lst)-1,0,-1):
            lst[0],lst[end] = lst[end],lst[0]
            sift_down(lst,0,end-1)
        return lst
    def __sift_down(self,a,start,end):
        root = start
        while True:
            child = 2*root + 1
            if child>end: break
            if ((child+1)<=end) and (a[child]<a[child+1]):
                child += 1
            if a[root] < a[child]:
                a[root],a[child] = a[child],a[root]
                root = child
            else:
                break
            self.step += 1
    def heap(self, a=None):
        if a == None: a = self.code
        for start in range((len(a)-2)/2,-1,-1):
            self.__sift_down(a,start,len(a)-1)
            #print ('s'+str(start)+':   '+str(a))
        for end in range(len(a)-1,0,-1):
            a[0],a[end] = a[end],a[0]
            self.__sift_down(a,0,end-1)
            #print ('e'+str(end)+':   '+str(a))
def main():
    sys.setrecursionlimit(1000)
    if len(sys.argv) > 1:
        a = Foo(int(sys.argv[1]))
    else:
        a=Foo()
    #print ('orig: '+str(a.get()))
    #a.bubble()
    a.heap(a.get())
    #print ('sort: '+str(a.get()))
    print ('step: '+str(a.step)+' bigo: '+str(a.bigo))
if __name__ == '__main__':
    #print len(sys.argv)
    #print sys.argv
    main()
