#!/bin/bash


distro="$(awk -F'=' '/^ID=/ {print tolower($2)}' /etc/*-release)"
if [[ $distro == "ubuntu" ]]; then
	# make all servers/clients	
	g++ -o asio_server asio_server.cpp -L/usr/lib/x86_64-linux-gnu/ -lpthread
	g++ -o asio_client asio_client.cpp -L/usr/lib/x86_64-linux-gnu/ -lpthread
	mkdir build && cd build
	cmake ..
	make
	mv poco_* ..
	cd ..
	rm -rf build
else
	make all
fi
