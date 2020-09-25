#!/usr/bin/env python3

# if you want to build this outside linux then yeah you have to do it yourself x

import os

def printedCmd(cmd):
    print(cmd)
    os.system(cmd)

files = os.listdir(".")

fnames = []

for f in files:
    if ".cpp" in f:
        fnames.append(f[:-4])

for f in fnames:
    printedCmd("g++ -c ./"+f+".cpp -std=c++17")


objFiles = ".o ./".join(fnames)

# the final fname won't have a .o appended
printedCmd("g++ ./"+objFiles+".o -o build")

