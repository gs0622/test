#!/usr/bin/python
import sys
import random

class Foo:
    """ Foo test module """
    name = 'Foo test module'
    def __init__(self):
        Foo.reset(self)
    def reset(self):
        self.code = random.sample(xrange(100), 10)
    def get(self):
        return self.code
    def bubble(self):
        """ worst: O(n^2), best: O(n), avg: O(n^2) """
        for i in range(len(self.code)-1,0,-1):
            for j in range(0,i,1):
                if self.code[j]>self.code[j+1]:
                    self.code[j],self.code[j+1]=self.code[j+1],self.code[j]
    def insertion(self):
        """ worst: O(n^2), best: O(n), avg: O(n^2) """
        for i in range(len(self.code)):
            j = i
            while j>0 and self.code[j-1] > self.code[j]:
                self.code[j-1],self.code[j]=self.code[j],self.code[j-1]
                j = j-1
    def select(self):
        """ worst: O(n^2), best: O(n^2), avg: O(n^2) """
        a = self.code
        k = len(a)
        #for i in range(k):
        for i in range(k-1):    #skip last one
            min = i
            for j in range(i,k):
                if a[j] < a[min]:
                    min = j
            if min != i:
                a[i],a[min] = a[min],a[i]
            #print i,a
    def __merge(self, left, right):
        if left == None: l=0
        else: l=len(left)
        if right == None: r=0
        else: r=len(right)
        res=list()
        #print('m',str(l),left,str(r),right)
        while l>0 or r>0:
            if l>0 and r>0:
                #print('c',left[0],right[0])
                if left[0]<=right[0]:
                    res.append(left.pop(0))
                    l=l-1
                else:
                    res.append(right.pop(0))
                    r=r-1
            elif l>0:
                #print('l',l, res, left)
                for w in left:
                    res.append(w)
                l=0
            elif r>0:
                #print('r',r, res, right)
                for w in right:
                    res.append(w)
                r=0
            #print('m',res)
        return res
    def __merge_sort(self, a):
        n = len(a)
        if n<=1: return a
        m = n/2
        #print('s','l',a[0:m],'r',a[m:n])
        left = a[0:m]
        right = a[m:n]
        left = self.__merge_sort(left)
        right = self.__merge_sort(right)
        return self.__merge(left,right)
    def merge(self):
        """ worst: O(nlogn), best: O(nlogn), avg: O(nlogn) """
        self.code = self.__merge_sort(self.code)
    def __quicksort(self, a, left, right):
        key = a[right]
        lid = left
        rid = right
        if lid == rid: return
        while True:
            while (a[lid] <= key) and (lid < rid): lid = lid + 1
            while (a[rid] >= key) and (lid < rid): rid = rid - 1
            a[lid], a[rid] = a[rid], a[lid]
            if lid >= rid: break;
        a[rid], a[right] = a[right], a[rid]
        if left < lid: self.__quicksort(a, left, lid-1)
        self.__quicksort(a, rid, right)
        print(self.code,lid,rid)
    def quick(self):
        """ worst: O(n^2), best: O(nlogn), avg: O(nlogn) """
        l = len(self.code)
        self.__quicksort(self.code, 0, l-1)
def main():
    sys.setrecursionlimit(1000)
    a=Foo()
    #print ('orig: '+str(a.get()))
    #a.bubble()
    #print ('sort: '+str(a.get()))
    #a.reset()
    #print ('orig: '+str(a.get()))
    #a.insertion()
    #print ('sort: '+str(a.get()))
    #a.reset()
    #print ('orig: '+str(a.get()))
    #a.merge()
    #print ('sort: '+str(a.get()))
    #a.reset()
    #print ('orig: '+str(a.get()))
    #a.quick()
    #print ('sort: '+str(a.get()))
    a.reset()
    print ('orig: '+str(a.get()))
    a.select()
    print ('sort: '+str(a.get()))
if __name__ == '__main__':
    main()
