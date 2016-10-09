XXX: meeting05
	./meeting05

meeting05 : main.o string.o
	g++ -g -o meeting05 main.o string.o

main.o : main.cc string.hh
	g++ -Wall -std=c++14 -c main.cc

string.o : string.cc string.hh
	g++ -Wall -std=c++14 -c string.cc