CPPFLAGS=-g
LDFLAGS=-g
LDLIBS=
RM=rm -f

SRCS=byte_stream.cpp data_out_stream.cpp dataoutstream.cpp stream_ifc.cpp translator.cpp
OBJS=$(subst .cpp,.o,$(SRCS))


all: streaming

clean: 
	$(RM) $(OBJS)


streaming:	$(OBJS)
	g++ -o streaming.so $(OBJS) -shared -fPIC
	$(RM) $(OBJS)

byte_stream.o: byte_stream.cpp
	g++ $(CPPFLAGS) -c byte_stream.cpp -fPIC


data_out_stream.o: data_out_stream.cpp 
	g++ $(CPPFLAGS) -c data_out_stream.cpp -fPIC

dataoutstream.o: dataoutstream.cpp
	g++ $(CPPFLAGS) -c dataoutstream.cpp -fPIC


stream_ifc.o: stream_ifc.cpp
	g++ $(CPPFLAGS) -c stream_ifc.cpp -fPIC
        
translator.o: translator.cpp
	g++ $(CPPFLAGS) -c translator.cpp -fPIC



