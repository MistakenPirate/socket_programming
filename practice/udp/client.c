#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<string.h>

int main(){
    int server_fd;
    struct sockaddr_in server_addr;
    socklen_t server_len;

    server_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(server_fd < 0){
        perror("Error");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(44332);
    server_len = sizeof(server_addr);

    while(1){
        char buf[100];
        printf("You:");
        scanf("%s", buf);

        sendto(server_fd, buf, 100, 0, (struct sockaddr*)&server_addr, server_len);
        recvfrom(server_fd, buf, 100, 0, (struct sockaddr*)&server_addr, &server_len);
        printf("Server: %s\n", buf);
    }

    close(server_fd);
    return 0;
}