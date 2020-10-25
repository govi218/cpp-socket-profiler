# C++ Socket Profiler

Profiling the performance of various C++ socket libs. Currently supporting Poco and ASIO.

## Building
Run `./build.sh`. Only Arch and Ubuntu are currently supported. Boost and Poco are assumed to be in their standard install dirs.

## Stats
1. ASIO Server
	- ASIO client
	```
	~/dev/cpp-socket-profiler on  master ● ●
	❯ ./asio_client
	Mbytes/sec: 5470.733947, Gbytes/sec: 5.470734, Mbits/sec: 43765.871575, Gbits/sec: 43.765872
	Mbytes/sec: 5936.793376, Gbytes/sec: 5.936793, Mbits/sec: 47494.347005, Gbits/sec: 47.494347
	Mbytes/sec: 5315.283395, Gbytes/sec: 5.315283, Mbits/sec: 42522.267160, Gbits/sec: 42.522267
	Mbytes/sec: 5661.320086, Gbytes/sec: 5.661320, Mbits/sec: 45290.560686, Gbits/sec: 45.290561
	Mbytes/sec: 5108.676519, Gbytes/sec: 5.108677, Mbits/sec: 40869.412150, Gbits/sec: 40.869412
	Mbytes/sec: 5349.520803, Gbytes/sec: 5.349521, Mbits/sec: 42796.166426, Gbits/sec: 42.796166
	Mbytes/sec: 6363.495096, Gbytes/sec: 6.363495, Mbits/sec: 50907.960768, Gbits/sec: 50.907961
	^Cclient: goodbyte
	```

	- Poco Client
	```
	❯ ./poco_client
	Mbytes/sec: 6663.611541, Gbytes/sec: 6.663612, Mbits/sec: 53308.892326, Gbits/sec: 53.308892
	Mbytes/sec: 6573.645766, Gbytes/sec: 6.573646, Mbits/sec: 52589.166129, Gbits/sec: 52.589166
	Mbytes/sec: 6485.982314, Gbytes/sec: 6.485982, Mbits/sec: 51887.858511, Gbits/sec: 51.887859
	Mbytes/sec: 6230.755090, Gbytes/sec: 6.230755, Mbits/sec: 49846.040722, Gbits/sec: 49.846041
	Mbytes/sec: 6650.963671, Gbytes/sec: 6.650964, Mbits/sec: 53207.709371, Gbits/sec: 53.207709
	Mbytes/sec: 5925.913457, Gbytes/sec: 5.925913, Mbits/sec: 47407.307655, Gbits/sec: 47.407308
	Mbytes/sec: 6481.999782, Gbytes/sec: 6.482000, Mbits/sec: 51855.998259, Gbits/sec: 51.855998
	^Cclient: goodbyte
	```

2. Poco Server
	- ASIO Client
	```
	~/dev/cpp-socket-profiler on  master ● ●
	❯ ./asio_client
	Mbytes/sec: 4153.775142, Gbytes/sec: 4.153775, Mbits/sec: 33230.201135, Gbits/sec: 33.230201
	Mbytes/sec: 5703.338004, Gbytes/sec: 5.703338, Mbits/sec: 45626.704034, Gbits/sec: 45.626704
	terminate called after throwing an instance of 'boost::wrapexcept<boost::system::system_error>'
	  what():  write: Connection reset by peer
	[1]    82101 abort (core dumped)  ./asio_client
	```

	- Poco Client
	```
	~/dev/cpp-socket-profiler on  master ● ●
	❯ ./poco_client
	Mbytes/sec: 4838.075773, Gbytes/sec: 4.838076, Mbits/sec: 38704.606181, Gbits/sec: 38.704606
	Mbytes/sec: 6444.733722, Gbytes/sec: 6.444734, Mbits/sec: 51557.869773, Gbits/sec: 51.557870
	terminate called after throwing an instance of 'Poco::Net::ConnectionResetException'
	  what():  Connection reset by peer
	[1]    82244 abort (core dumped)  ./poco_client
	```

	So there's clearly something funky going on. What's funkier, here are stats with Poco Server running on Valgrind:

	- ASIO Client
	```
	❯ ./asio_client
	Mbytes/sec: 815.667253, Gbytes/sec: 0.815667, Mbits/sec: 6525.338020, Gbits/sec: 6.525338
	Mbytes/sec: 823.797307, Gbytes/sec: 0.823797, Mbits/sec: 6590.378460, Gbits/sec: 6.590378
	Mbytes/sec: 836.448597, Gbytes/sec: 0.836449, Mbits/sec: 6691.588780, Gbits/sec: 6.691589
	Mbytes/sec: 834.398052, Gbytes/sec: 0.834398, Mbits/sec: 6675.184420, Gbits/sec: 6.675184
	Mbytes/sec: 832.001507, Gbytes/sec: 0.832002, Mbits/sec: 6656.012056, Gbits/sec: 6.656012
	^Cclient: goodbyte
	```

	- Poco Client
	```
	~/dev/cpp-socket-profiler on  master ● ●
	❯ ./poco_client
	Mbytes/sec: 831.125404, Gbytes/sec: 0.831125, Mbits/sec: 6649.003236, Gbits/sec: 6.649003
	Mbytes/sec: 828.358152, Gbytes/sec: 0.828358, Mbits/sec: 6626.865220, Gbits/sec: 6.626865
	Mbytes/sec: 821.415920, Gbytes/sec: 0.821416, Mbits/sec: 6571.327357, Gbits/sec: 6.571327
	Mbytes/sec: 807.946447, Gbytes/sec: 0.807946, Mbits/sec: 6463.571573, Gbits/sec: 6.463572
	Mbytes/sec: 824.609338, Gbytes/sec: 0.824609, Mbits/sec: 6596.874706, Gbits/sec: 6.596875
	^Cclient: goodbyte
	```

	While the speed loss makes perfect sense, why does it work on Valgrind? Moreover,
	```
	==82455== HEAP SUMMARY:
	==82455==     in use at exit: 0 bytes in 0 blocks
	==82455==   total heap usage: 1,451 allocs, 1,451 frees, 633,666 bytes allocated
	==82455==
	==82455== All heap blocks were freed -- no leaks are possible
	==82455==
	==82455== For lists of detected and suppressed errors, rerun with: -s
	==82455== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
	```

	Strange....

## Soon to come
	- C++ Experimental socket
