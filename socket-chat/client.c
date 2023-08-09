#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int sockfd = -1; // create socket 
    struct sockaddr_in server_addr;    // chua dia chi cua server
    char send_buffer[1024]; // send data client <---> server
    char recv_buffer[1024];
    time_t ticks;

    memset(send_buffer, 0, sizeof(send_buffer));
    memset(recv_buffer, 0, sizeof(recv_buffer));
    memset(&server_addr, 0, sizeof(server_addr));

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // inet_addr: convert chuoi string ip server theo kieu big endian
    server_addr.sin_port = htons(5000);

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("connect");
        close(sockfd);
        return 1;
    }

    // doc message tu server
    read(sockfd, recv_buffer, sizeof(recv_buffer) - 1);
    printf("%s", recv_buffer);

    while (1) {
        // nhan dau vao
        printf("Client: ");
        fgets(send_buffer, sizeof(send_buffer), stdin);

        // gui message den server
        write(sockfd, send_buffer, strlen(send_buffer));

        // kiem tra client co muon thoat khong "bye"
        if (strcmp(send_buffer, "bye\n") == 0) {
            // Server's goodbye message
            read(sockfd, recv_buffer, sizeof(recv_buffer) - 1);
            printf("%s", recv_buffer);
            break;
        }

        // nhan va hien thi, tra loi den server
        memset(recv_buffer, 0, sizeof(recv_buffer));
        read(sockfd, recv_buffer, sizeof(recv_buffer) - 1);
        printf("Server: %s", recv_buffer);
    }

    close(sockfd);
    return 0;
}
