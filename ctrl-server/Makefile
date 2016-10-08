build: ControlServer HTTPServer HTTPHandler
	$(CXX) -o ctrl-server ControlServer.o HTTPServer.o HTTPHandler.o

ControlServer: ControlServer.cpp
	$(CXX) -c ControlServer.cpp -o ControlServer.o

HTTPServer: HTTPServer.cpp
	$(CXX) -c HTTPServer.cpp -o HTTPServer.o

HTTPHandler: HTTPHandler.cpp
	$(CXX) -c HTTPHandler.cpp -o HTTPHandler.o

clean:
	rm *.o ctrl-server
