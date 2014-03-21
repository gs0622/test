#!/usr/bin/python
# find match of string s in document t
import sys

def NaiveSearch(s, t):
    with open(t) as f:
        d = f.read()
        print str(len(d))
        for i in range(len(d)):
            #print s+' vs. '+d[i:i+len(s)]
            if s == d[i:i+len(s)]:
                print 'found: '+d[i:i+len(s)]
                sys.exit(0)
        print 'not found: '+s

def main():
    s, t = sys.argv[1], sys.argv[2]
    print s, t
    NaiveSearch(s, t)
if __name__ == '__main__':
    main()

