#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<string.h>

int main(){
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t server_len, client_len;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd < 0){
        perror("Error");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(44332);
    server_len = sizeof(server_addr);

    bind(server_fd, (struct sockaddr*)&server_addr, server_len);
    listen(server_fd, 5);

    while(1){
        char buf[100];
        client_len = sizeof(server_addr);
        client_fd = accept(server_fd, (struct sockaddr *)&server_addr, &client_len);

        read(client_fd, &buf, 100);
        printf("Client: %s\n", buf);
        printf("You:");
        scanf("%s", buf);
        write(client_fd, &buf, 100);
    }

    close(client_fd);
    close(server_fd);
    return 0;
}