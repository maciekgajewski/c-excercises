test2: test2.o library.o complex.o rpn_calculator.o
	g++ -o test2 test2.o library.o complex.o rpn_calculator.o

library.o: library.cc library.hh
	g++ -c library.cc -std=c++14

test2.o: test2.cc library.hh complex.hh
	g++ -c test2.cc -std=c++14

complex.o: complex.cc complex.hh
	g++ -c complex.cc -std=c++14

rpn_calculator.o: rpn_calculator.cc rpn_calculator.hh complex.hh
	g++ -c rpn_calculator.cc -std=c++14

clean:
	rm *.o