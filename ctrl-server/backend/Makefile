CFLAGS=-Wall -std=c++11 -I../vendor/json/include -I../vender/variant/include
LDFLAGS= -lboost_system -lpthread

OBJECTS=ControlServer.o HTTPServer.o ThreadPool.o String.o IO.o \
		HTTPHeaders.o HTTPRequest.o Router.o Session.o SessionManager.o \
		Application.o

all: ctrl-server

ctrl-server: $(OBJECTS)
	$(CXX) -o ctrl-server $(OBJECTS) $(LDFLAGS)

ControlServer.o: ControlServer.cpp
	$(CXX) -c ControlServer.cpp -o ControlServer.o $(CFLAGS)

Application.o: Application.cpp
	$(CXX) -c Application.cpp -o Application.o $(CFLAGS)

HTTPServer.o: HTTPServer.cpp
	$(CXX) -c HTTPServer.cpp -o HTTPServer.o $(CFLAGS)

ThreadPool.o: ThreadPool.cpp
	$(CXX) -c ThreadPool.cpp -o ThreadPool.o $(CFLAGS)

String.o: String.cpp
	$(CXX) -c String.cpp -o String.o $(CFLAGS)

IO.o: IO.cpp
	$(CXX) -c IO.cpp -o IO.o $(CFLAGS)

HTTPHeaders.o: HTTPHeaders.cpp
	$(CXX) -c HTTPHeaders.cpp -o HTTPHeaders.o $(CFLAGS)

HTTPRequest.o: HTTPRequest.cpp
	$(CXX) -c HTTPRequest.cpp -o HTTPRequest.o $(CFLAGS)

Router.o: Router.cpp
	$(CXX) -c Router.cpp -o Router.o $(CFLAGS)

Session.o: Session.cpp
	$(CXX) -c Session.cpp -o Session.o $(CFLAGS)

SessionManager.o: SessionManager.cpp
	$(CXX) -c SessionManager.cpp -o SessionManager.o $(CFLAGS)

clean:
	rm *.o ctrl-server
