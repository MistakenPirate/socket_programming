#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/socket.h>

#define PORT 44332

int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    char buffer[100];
    socklen_t addr_len = sizeof(servaddr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }


    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    while (1) {
        printf("You: ");
        fgets(buffer, sizeof(buffer), stdin); 
        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&servaddr, addr_len);

        memset(buffer, 0, sizeof(buffer));
        recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&servaddr, &addr_len);
        printf("Server: %s", buffer);
    }

    close(sockfd);
    return 0;
}
