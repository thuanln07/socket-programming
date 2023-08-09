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

int main(int argc, char const* argv[])
{
	int listenfd = -1;	// khoi tao listen cho socket
	int connfd = -1;	// khoi tao connect cho socket da ket noi
	struct sockaddr_in server_addr; // chua dia chi cua server
	char send_buffer[1024];  // send data client <---> server
	time_t ticks;

	memset (send_buffer, 0, sizeof(send_buffer));
	memset (&server_addr, 0, sizeof(server_addr));

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	// AF_INET: truyen du lieu ra ben ngoai
	// SOCK_STREAM: truyen lien tuc khong ngat quang
	// protocol: mac dinh

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  // // inet_addr: convert chuoi string ip server theo kieu big-endian
	server_addr.sin_port = htons(5000);
	
	bind(listenfd, (struct sockaddr*)&server_addr, sizeof(server_addr)); // dinh kem dai chi vao socket
	listen(listenfd, 10); // max 10 client connect den

	while (1)
	{
		connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); // chap nhan ket noi tu client
		ticks = time(NULL);  // lay thoi gian hien tai 
		sprintf(send_buffer, "server reply %s",ctime(&ticks));  // dinh dang phan hoi la gian hien tai cua server
		write(connfd, send_buffer, strlen(send_buffer));  // send-buffer den client bang socket da ket noi
		close(connfd); // dong socket da ket noi sau khi gui phan hoi
	}
	
	return 0;
}
