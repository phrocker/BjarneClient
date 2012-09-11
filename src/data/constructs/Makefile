SRC=$(wildcard *.cpp)
EXTSRC=../streaming/stream_ifc.cpp
CPP = g++

CPPFLAGS=-O3
LDFLAGS = -lthrift -I/usr/local/include/thrift/

all: $(SRC)
	$(CPP) $(CPPFLAGS) -c $(SRC) $(EXTSRC) $(LDFLAGS)
	$(CPP) *.o -o test
clean:
	rm -f *.o
