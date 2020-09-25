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

# itertools.chain.from_iterable() unfortunately counts strings as iterables
# 
# we take all strings that aren't in a nested list and put them in one
filesDimensioned = getAllFiles()
rootFiles = []

# get all root strings and put them in a new list
for item in filesDimensioned:
    if type(item) != list:
        rootFiles.append(item)

# now remove them all from the original list
for item in rootFiles:
    filesDimensioned.remove(item)

# now add them back within the nested list
filesDimensioned.append(rootFiles)

# NOW we can do from_iterable
files = itertools.chain.from_iterable(filesDimensioned)

fnames = []

for f in files:
    if ".cpp" in f:
        fnames.append(f[:-4])

for f in fnames:
    printedCmd("g++ -c ./"+f+".cpp -I . -std=c++17")


objFiles = ".o ./".join([ item[:-2] for item in os.listdir(".") if ".o" in item ])

# the final fname won't have a .o appended
printedCmd("g++ ./"+objFiles+".o -o build")

