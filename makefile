# SRCS=bitpostodec.cpp bitpos.cpp powerof2.cpp printTwosComplement.cpp
# Replace .cpp in SRCS with .o
# OBJS=$(subst .cpp,.o,$(SRCS))

CXX=g++

binaries = bitpostodec bitpos powerof2 printTwosComplement
all: $(binaries)

bitpostodec: bitpostodec.cpp 
	$(CXX) -o bitpostodec bitpostodec.cpp

bitpos: bitpos.cpp
	$(CXX) -o bitpos bitpos.cpp

powerof2: powerof2.cpp
	$(CXX) -o powerof2 powerof2.cpp

printTwosComplement: printTwosComplement.cpp
	$(CXX) -o printTwosComplement printTwosComplement.cpp

clean:
	rm $(binaries)
