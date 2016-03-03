CXXFLAGS=-g -std=c++14 -Wall -I/opt/optiver/boost/1.59.0/include/

report_printer: main.o person.o report.o
	g++ $(LDFLAGS) -o report_printer main.o person.o report.o

main.o: main.cc report.hh person.hh
	g++ $(CXXFLAGS) -c main.cc
person.o: person.cc person.hh record.hh
	g++ $(CXXFLAGS) -c person.cc
report.o: report.cc report.hh
	g++ $(CXXFLAGS) -c report.cc
