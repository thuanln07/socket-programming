#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	int sockfd = -1;
	struct sockaddr_in server_addr;
	char recv_buffer[1024];
	time_t ticks;

	memset(recv_buffer, 0, sizeof(recv_buffer));
	memset(&server_addr, 0, sizeof(server_addr));

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_addr.sin_port = htons(5000);

	if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == 0)
	{
		read(sockfd, recv_buffer, sizeof(recv_buffer) - 1);
		printf("\n%s\n", recv_buffer);
	}
	close(sockfd);

	return 0;
}

