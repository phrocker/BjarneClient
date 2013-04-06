CPPFLAGS=-g -std=c++11 -I/usr/local/include/thrift -lthrift -lboost_system -lpthread -lboost_thread
LDFLAGS=-g
LDLIBS=
RM=rm -f
PWD=`pwd`

SRCS=../../data/constructs/KeyExtent.cpp  ../../data/constructs/security/AuthInfo.cpp ../../data/constructs/Key.cpp  ../../data/constructs/Range.cpp ../../data/constructs/column.cpp ConstructHarness.cpp
OBJS=$(subst .cpp,.o,$(SRCS))
DEPENDENCIES=../../data/streaming/streaming.so 


all: test

clean: 
	$(RM) $(OBJS)


test:	$(OBJS)
	cd ../../data/streaming ; make clean; make ; cd $(PWD)
	g++ -o interconnect_tests $(OBJS) $(DEPENDENCIES) $(CPPFLAGS) $(LDLIBS)
	$(RM) $(OBJS)
	./interconnect_tests
	rm interconnect_tests
