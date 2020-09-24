#!/usr/bin/env bash
# if you want to build this outside linux then yeah you have to do it yourself x

g++ -c ./logging.cpp -std=c++17
g++ -c ./Model.cpp -std=c++17
g++ -c ./main.cpp -std=c++17

g++ ./main.o Model.o logging.o -o build