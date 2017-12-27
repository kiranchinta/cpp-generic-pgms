# SRCS=bitpostodec.cpp bitpos.cpp powerof2.cpp printTwosComplement.cpp sort.cpp
# Replace .cpp in SRCS with .o
# OBJS=$(subst .cpp,.o,$(SRCS))

CXX=g++

binaries = bitpostodec bitpos powerof2 printTwosComplement sortAlgorithms/sort
all: $(binaries)

bitpostodec: bitpostodec.cpp 
	$(CXX) -o bitpostodec bitpostodec.cpp

bitpos: bitpos.cpp
	$(CXX) -o bitpos bitpos.cpp

powerof2: powerof2.cpp
	$(CXX) -o powerof2 powerof2.cpp

printTwosComplement: printTwosComplement.cpp
	$(CXX) -o printTwosComplement printTwosComplement.cpp

# Extra compile options to get the symbol info for stacktrace dumping
# $(CXX) -g -std=c++1y -rdynamic -o sort sort.cpp // For dynarray compilation
sort: sortAlgorithms/sort.cpp
	$(CXX) -g -rdynamic -o sortAlgorithms/sort sortAlgorithms/sort.cpp

clean:
	rm $(binaries)
