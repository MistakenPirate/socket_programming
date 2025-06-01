#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/socket.h>

#define PORT 44332

int main() {
    int server_fd;
    struct sockaddr_in servaddr, clientaddr;
    char buffer[100];
    socklen_t addr_len = sizeof(clientaddr);

    // Create socket
    server_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_fd < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Setup server address
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Bind to server address
    if (bind(server_fd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    printf("Server ready. Waiting for messages...\n");

    while (1) {
        memset(buffer, 0, sizeof(buffer));
        recvfrom(server_fd, buffer, sizeof(buffer), 0, (struct sockaddr *)&clientaddr, &addr_len);
        printf("Client: %s", buffer);

        printf("You: ");
        fgets(buffer, sizeof(buffer), stdin);
        sendto(server_fd, buffer, strlen(buffer), 0, (struct sockaddr *)&clientaddr, addr_len);
    }

    close(server_fd);
    return 0;
}
