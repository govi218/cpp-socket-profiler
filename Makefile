all: asio-server asio-client
asio-server:
	g++ -o asio_server asio_server.cpp -L/usr/lib/ -lpthread
asio-client:
	g++ -o asio_client asio_client.cpp -L/usr/lib/ -lpthread
