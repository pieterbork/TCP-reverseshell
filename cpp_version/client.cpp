#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include <string>

#define MAXLINE 4096 /*max text line length*/
#define MAXRECV 100000
#define SERV_PORT 8888 /*port*/
#define SERV_ADDR "127.0.0.1"

using namespace std;
using std::string;

int main(int argc, char **argv) {
	int sockfd;
	struct sockaddr_in servaddr;
	char sendline[MAXLINE], recvline[MAXRECV];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if( sockfd < 0) {
		perror("Problem in creating socket");
		exit(2);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(SERV_ADDR);
	servaddr.sin_port = htons(SERV_PORT);
	
	if((connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr))<0)) {
		perror("Problem in connect.");
		exit(3);
	}

	while(fgets(sendline, MAXLINE, stdin) != NULL) {
		send(sockfd, sendline, strlen(sendline), 0);
		
		if(recv(sockfd, recvline, MAXRECV, 0) == 0) {
			perror("The server terminated prematurely");
			exit(4);
		}
		printf("%s\n", recvline);
		memset(recvline, 0, sizeof(recvline));
	}
	exit(0);
}
