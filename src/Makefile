all: clean test

test: test.o converters.o
	g++ test.o converters.o -o test -std=c++11

converters.o:
	g++ -c converters.cpp -std=c++11
test.o:
	g++ -c test.cpp -std=c++11

clean:
	rm -rf *.o test
