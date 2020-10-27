# C++ Socket Profiler

Profiling the performance of various C++ socket libs. Currently supporting Poco and ASIO.

## Building
Run `./build.sh`. Only Arch and Ubuntu are currently supported. Boost and Poco are assumed to be in their standard install dirs.

## Stats
ASIO SERVER
- poco client: Average thru Gbps: 47.430393
- asio client: Average thru Gbps: 39.342850

POCO SERVER
- poco client: Average thru Gbps: 46.038822
- asio client: Average thru Gbps: 42.239065

## Soon to come
	- C++ Experimental socket
