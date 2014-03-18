#!/usr/bin/python

import re, sys

def isPrime(n):
    # see http://www.noulakaz.net/weblog/2007/03/18/a-regular-expression-to-check-for-prime-numbers/
    return re.match(r'^1?$|^(11+?)\1+$', '1' * n) == None

def isPrime2(n):
    #6k+-1 version, see http://en.wikipedia.org/wiki/Primality_test
    if n < 2: return None
    if n in (2, 3): return n
    if (n%2==0) or (n%3==0): return None
    maxdiv = int(n**0.5)    # squart root of n
    div = 5
    while div < maxdiv:
        if (n%div==0) or (n%(div+2)==0): return None
        div += 6
    return n    # n is prime

def main():
    N = int(sys.argv[1]) # number of primes wanted (from command-line)
    M = 100              # upper-bound of search space
    l = list()           # result list
    while len(l) < N:
        l += filter(isPrime, range(M - 100, M)) # append prime element of [M - 100, M] to l
        #l += filter(isPrime2, range(M - 100, M))
        M += 100                                # increment upper-bound
    print l[:N] # print result list limited to N elements

    while len(l) < N:
        l += filter(isPrime2, range(M - 100, M))
        M += 100                                # increment upper-bound
    print l[:N] # print result list limited to N elements

if __name__ == '__main__':
    main()
