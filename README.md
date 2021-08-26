# ass2-advanced_programing
by itamar gefen 326300738 and roei cohen

running instractions:
we provide you a cmake with 3 targets:
UdpServer: to run the udp server
TcpServer: to run the tcp server
Client: to run the client
make sure to run the servers before the client.

the code:
we wrraped the sockets with TCP/UDP ServerSocket and TCP/UDP Socket classes.
the TCP/UDP Socket is for the send,recive operations
the TCP/UDP ServerSocket are for the listen,accept operation
with these classes we made a Server class that can work wite eather tcp or udp.
the server recives forom the client a path of unclassified data file, and a path for the output file. the server creates the output file like in ass1.
