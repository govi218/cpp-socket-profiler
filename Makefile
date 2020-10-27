CC := g++
CXXFLAGS = -g -Wall
CFLAGS := -lPocoNet -lPocoUtil -lPocoXML -lPocoFoundation

all: asio-server asio-client poco-server poco-client
asio-server:
	${CC} -o asio_server asio_server.cpp -L/usr/lib/ -lpthread
asio-client:
	${CC} -o asio_client asio_client.cpp -L/usr/lib/ -lpthread
poco-server:
	${CC} -o poco_server ${CFLAGS} ${CXXFLAGS} poco_server.cpp ConnectionHandler.cpp poco_server_main.cpp
poco-client:
	${CC} -o poco_client poco_client.cpp -L/usr/local/lib/cmake/Poco -lPocoNet
