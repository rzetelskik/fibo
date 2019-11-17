.PHONY: run clean

install: build link

all: install run

build: build_fibo build_tests

link: link_tests

run:
	./tests

build_fibo:
	g++ -Wall -Wextra -O2 -std=c++17 -c fibo.cc -o fibo.o

build_tests:
	g++ -Wall -Wextra -O2 -std=c++17 -c tests.cc -o tests.o

link_tests:
	g++ tests.o fibo.o -o tests

clean:
	rm -f fibo.o tests.o
