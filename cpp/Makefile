all: server.cpp client.cpp
	g++ -Wall server.cpp -o revserver
	g++ -Wall client.cpp -o client
server: server.cpp
	g++ -Wall server.cpp -o revserver
client: client.cpp
	g++ -Wall client.cpp -o client
clean:
	rm revserver
	rm client
