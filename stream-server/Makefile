CFLAGS=-Wall -std=c++11
LDFLAGS= -lpthread

OBJECTS=StreamServer.o

all: stream-server

stream-server: $(OBJECTS)
	$(CXX) -o stream-server $(OBJECTS) $(LDFLAGS)

StreamServer.o: StreamServer.cpp
	$(CXX) -c StreamServer.cpp -o StreamServer.o $(CFLAGS)

clean:
	rm *.o stream-server
