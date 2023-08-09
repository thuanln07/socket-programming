#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char const* argv[])
{
    int listenfd = -1;
    int connfd = -1;
    struct sockaddr_in server_addr; // chua dia chi cua server
    struct sockaddr_in client_addr; // chua dia chi cua client
    socklen_t client_len; // luu tru kich thuoc dia chi client
    char send_buffer[1024];
    char recv_buffer[1024];
    time_t ticks;

    memset(send_buffer, 0, sizeof(send_buffer));
    memset(recv_buffer, 0, sizeof(recv_buffer));
    memset(&server_addr, 0, sizeof(server_addr));

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1) {
        perror("socket");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(5000);

    if (bind(listenfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        close(listenfd);
        return 1;
    }

    listen(listenfd, 10);

    printf("Server listening\n");

    while (1)
    {
        client_len = sizeof(client_addr); // khoi tao kich thuoc dia chi client
        connfd = accept(listenfd, (struct sockaddr*)&client_addr, &client_len);
        if (connfd == -1) {
            perror("accept");
            continue; 
        }

        ticks = time(NULL);
        sprintf(send_buffer, "Server: Connected. Type 'bye' to quit.\n");
        write(connfd, send_buffer, strlen(send_buffer));

        while (1) {
            // nhan message tu client 
            memset(recv_buffer, 0, sizeof(recv_buffer));
            read(connfd, recv_buffer, sizeof(recv_buffer) - 1);

            if (strcmp(recv_buffer, "bye\n") == 0) {
                // Client wants to quit, close the connection
                sprintf(send_buffer, "Server: Goodbye!\n");
                write(connfd, send_buffer, strlen(send_buffer));
                close(connfd);
                break; 
            }

            printf("Client: %s", recv_buffer);

            // nhan input user send & rep for client
            printf("Server: ");
            fgets(send_buffer, sizeof(send_buffer), stdin);

            // gui<->tra loi cho client
            write(connfd, send_buffer, strlen(send_buffer));
        }
    }

    close(listenfd);
    return 0;
}
