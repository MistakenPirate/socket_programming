#include <stdio.h>              // Standard I/O functions
#include <stdlib.h>             // For exit()
#include <unistd.h>             // For close()
#include <netinet/in.h>         // For sockaddr_in and htons()
#include <arpa/inet.h>          // For inet_addr()
#include <string.h>             // For memset(), strlen()
#include <sys/socket.h>         // For socket functions

#define PORT 44332              // Port number on which the server will listen

int main() {
    int sockfd;
    struct sockaddr_in servaddr, clientaddr;
    char buffer[100];           // Buffer to store incoming/outgoing messages
    socklen_t addr_len = sizeof(clientaddr);  // Length of the client's address

    // 1. Create a UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);  // AF_INET: IPv4, SOCK_DGRAM: UDP
    if (sockfd < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 2. Initialize server address structure
    servaddr.sin_family = AF_INET;              // IPv4
    servaddr.sin_port = htons(PORT);            // Host to network byte order
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Bind to localhost

    // 3. Bind the socket to the server address
    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    printf("Server ready. Waiting for messages...\n");

    // 4. Server runs in a loop to handle messages
    while (1) {
        memset(buffer, 0, sizeof(buffer)); // Clear the buffer

        // 5. Receive message from client
        recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&clientaddr, &addr_len);
        printf("Client: %s", buffer); // Print the received message

        // 6. Get server's response from stdin
        printf("You: ");
        fgets(buffer, sizeof(buffer), stdin);

        // 7. Send the response back to the client
        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&clientaddr, addr_len);
    }

    // 8. Close the socket (though this line is never reached in this loop)
    close(sockfd);
    return 0;
}
