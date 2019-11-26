all: test

test: test.o converters.o
	g++ test.o converters.o -o test

converters.o:
	g++ -c converters.cpp
test.o:
	g++ -c test.cpp

clean:
	rm -rf *.o test