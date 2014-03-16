#!/usr/bin/python
with open('cat.py') as fp:
    for line in iter(fp.readline, ''):
        print(line)