#!/usr/bin/env python3

# if you want to build this outside linux then yeah you have to do it yourself x

import os
import os.path as path
import itertools

def printedCmd(cmd):
    print(cmd)
    os.system(cmd)


def getAllFiles(dirName="."):
    allItems = os.listdir(dirName)
    allFiles = []

    for item in allItems:
        fullPath = os.path.join(dirName, item)
        if path.isdir(fullPath):
            allFiles.append(getAllFiles(fullPath))
        else:
            allFiles.append(fullPath)
    
    return allFiles

files = list(itertools.chain.from_iterable(getAllFiles()))

fnames = []

for f in files:
    if ".cpp" in f:
        fnames.append(f[:-4])

for f in fnames:
    printedCmd("g++ -c ./"+f+".cpp -I . -std=c++17")


objFiles = ".o ./".join([ item[:-2] for item in os.listdir(".") if ".o" in item ])

# the final fname won't have a .o appended
printedCmd("g++ ./"+objFiles+".o -o build")

