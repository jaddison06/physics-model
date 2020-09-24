# if you want to build this outside linux then yeah you have to do it yourself x

build: main.o Model.o logging.o
	g++ ./main.o Model.o logging.o -o build

main.o: main.cpp
	g++ -c ./main.cpp

Model.o: Model.cpp
	g++ -c ./Model.cpp

logging.o: logging.cpp
	g++ -c ./logging.cpp

clean:
	rm *.o
	rm build