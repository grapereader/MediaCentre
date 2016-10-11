CFLAGS=-Wall -std=c++11
LDFLAGS= -lboost_system -lpthread

OBJECTS=ControlServer.o HTTPServer.o ThreadPool.o String.o IO.o

all: ctrl-server

ctrl-server: $(OBJECTS)
	$(CXX) -o ctrl-server $(OBJECTS) $(LDFLAGS)

ControlServer.o: ControlServer.cpp
	$(CXX) -c ControlServer.cpp -o ControlServer.o $(CFLAGS)

HTTPServer.o: HTTPServer.cpp
	$(CXX) -c HTTPServer.cpp -o HTTPServer.o $(CFLAGS)

ThreadPool.o: ThreadPool.cpp
	$(CXX) -c ThreadPool.cpp -o ThreadPool.o $(CFLAGS)

String.o: String.cpp
	$(CXX) -c String.cpp -o String.o $(CFLAGS)

IO.o: IO.cpp
	$(CXX) -c IO.cpp -o IO.o $(CFLAGS)

clean:
	rm *.o ctrl-server
