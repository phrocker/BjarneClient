CPPFLAGS=-g -std=c++11
LDFLAGS=-g
LDLIBS=
RM=rm -f
PWD=`pwd`

SRCS= ConstructHarness.cpp
OBJS=$(subst .cpp,.o,$(SRCS))
DEPENDENCIES=../../data/streaming/streaming.so 


all: test

clean: 
	$(RM) $(OBJS)


test:	$(OBJS)
	cd ../../data/streaming ; make clean; make ; cd $(PWD)
	g++ -o interconnect_tests $(OBJS) $(DEPENDENCIES) $(CPPFLAGS)
	$(RM) $(OBJS)
	./interconnect_tests
