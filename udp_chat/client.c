#include <stdio.h>              // Standard I/O functions
#include <stdlib.h>             // For exit()
#include <unistd.h>             // For close()
#include <netinet/in.h>         // For sockaddr_in and htons()
#include <arpa/inet.h>          // For inet_addr()
#include <string.h>             // For memset(), strlen()
#include <sys/socket.h>         // For socket functions

#define PORT 44332              // Port number to connect to (must match the server)

int main() {
    int sockfd;
    struct sockaddr_in servaddr;         // Server address structure
    char buffer[100];                    // Buffer to store message to/from server
    socklen_t addr_len = sizeof(servaddr);

    // 1. Create a UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);  // AF_INET: IPv4, SOCK_DGRAM: UDP
    if (sockfd < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 2. Configure the server address
    servaddr.sin_family = AF_INET;              // IPv4
    servaddr.sin_port = htons(PORT);            // Convert port to network byte order
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Set server IP (localhost)

    // 3. Communicate with the server in a loop
    while (1) {
        printf("You: ");
        fgets(buffer, sizeof(buffer), stdin);   // Read message from user input

        // 4. Send the message to the server
        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&servaddr, addr_len);

        // 5. Clear the buffer to receive a fresh message
        memset(buffer, 0, sizeof(buffer));

        // 6. Receive the server's response
        recvfrom(sockfd, buffer, sizeof(buffer), 0, NULL, NULL);

        // 7. Print the server's response
        printf("Server: %s", buffer);
    }

    // 8. Close the socket (not reached here due to infinite loop)
    close(sockfd);
    return 0;
}
