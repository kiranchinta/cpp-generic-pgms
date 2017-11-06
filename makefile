# SRCS=bitpostodec.cpp alphacount.cpp bitpos.cpp powerof2.cpp
# Replace .cpp in SRCS with .o
# OBJS=$(subst .cpp,.o,$(SRCS))

CXX=g++

binaries = bitpostodec alphacount bitpos powerof2
all: $(binaries)

bitpostodec: bitpostodec.cpp 
	$(CXX) -o bitpostodec bitpostodec.cpp

alphacount: alphacount.cpp
	 $(CXX) -o alphacount alphacount.cpp

bitpos: bitpos.cpp
	$(CXX) -o bitpos bitpos.cpp

powerof2: powerof2.cpp
	$(CXX) -o powerof2 powerof2.cpp

clean:
	rm $(binaries)
