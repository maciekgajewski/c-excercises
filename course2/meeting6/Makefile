all: const move

const: const.cc string.hh
	g++ -std=c++14 -Wall -g -o const const.cc

move: move.cc string.hh
	g++ -std=c++14 -Wall -g -O0 -o move move.cc
clean:
	rm -f const move
