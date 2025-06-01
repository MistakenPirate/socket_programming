#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(){
    int my_sock;
    socklen_t sock_addr_len;

    struct sockaddr_in sock_addr;

    char ch = 'A';

    // create a socket for the client
    my_sock = socket(AF_INET, SOCK_DGRAM, 0);

    // name the socket, as given in the server
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    sock_addr.sin_port = htons(44332);
    sock_addr_len = sizeof(sock_addr);

    // send and receive data to/from the server
    sendto(my_sock, &ch, 1, 0, (struct sockaddr *)&sock_addr, sock_addr_len);
    recvfrom(my_sock, &ch, 1, 0, (struct sockaddr*)&sock_addr, &sock_addr_len);

    printf("Received from server: %c\n", ch);

    close(my_sock);
    return 0;
}