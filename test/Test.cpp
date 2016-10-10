#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main()
{
    boost::asio::io_service ioService;
    tcp::resolver resolver(ioService);
    tcp::resolver::query query("127.0.0.1", "8080");
    tcp::resolver::iterator endpointIterator = resolver.resolve(query);
    tcp::socket socket(ioService);
    boost::asio::connect(socket, endpointIterator);
    boost::asio::write(socket, boost::asio::buffer("Test"));

    return 1;
}
