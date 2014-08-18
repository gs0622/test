#!/usr/bin/python
# tags: hex formatting, bit revert
import sys

def main():
    stride = 16
    for i in range(0, 256, stride):
        s = ''
        for j in range(i, i + stride, 1):
            k = j
            k = (k & 0xaa) >> 1 | (k & 0x55) << 1
            k = (k & 0xcc) >> 2 | (k & 0x33) << 2
            k = (k & 0xf0) >> 4 | (k & 0x0f) << 4
            s += '0x' + format(k, '02X')+ ', '
        print s

if __name__ == '__main__':
    main()

