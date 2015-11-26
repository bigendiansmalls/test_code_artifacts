#define _ALL_SOURCE
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>


int main(int argc, char ** argv)
{
	socklen_t socklen;
	int retval=-1;
	int flags=-1;
        int bread=0;
	int pid=-1;
	int sockfd;
	int clientfd;
	struct sockaddr_in srv_addr;
	struct sockaddr_in cli_addr;
	char buff[3000];
        char *bufp = buff;
        int (*ret)();
	ret=(int(*)())(buff);

	memset(buff,'\0',sizeof(buff));

	srv_addr.sin_family = AF_INET;
	srv_addr.sin_port = htons(12346);

	printf("port: %04X\n",srv_addr.sin_port);
	inet_pton(AF_INET, "10.0.0.1", &srv_addr.sin_addr);

	printf("addr: %08X\n",srv_addr.sin_addr);
	sockfd = socket( AF_INET, SOCK_STREAM, IPPROTO_IP );

	retval=bind( sockfd, (struct sockaddr *)&srv_addr, sizeof(srv_addr) );
	retval=listen(sockfd, 1);
	socklen = sizeof(cli_addr);
	clientfd = accept(sockfd, (struct sockaddr * restrict)&cli_addr, &socklen );
	bread=read(clientfd, &*bufp, 3000);
	while (bread > 0) {
		printf("Read %d bytes.\n",bread);
		bufp = bufp + bread;
		bread=read(clientfd, &*bufp, 3000);
	}
	close(clientfd);
	(int)(*ret)();
	return 0;
}
