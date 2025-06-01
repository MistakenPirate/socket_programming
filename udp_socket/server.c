#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    int my_sock;
    socklen_t serv_addr_len, client_addr_len;

    struct sockaddr_in serv_addr, client_addr;

    my_sock = socket(AF_INET, SOCK_DGRAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(44332);
    serv_addr_len = sizeof(serv_addr);

    int retval = bind(my_sock, (const struct sockaddr*)&serv_addr, serv_addr_len);

    if( retval == -1){
        perror("Bind Error");
        exit(EXIT_FAILURE);
    }

    char ch;
    printf("Server waiting...\n");

    client_addr_len = sizeof(client_addr);

    recvfrom(my_sock, &ch, 1, 0, (struct sockaddr*)&client_addr, &client_addr_len);
    ch++;
    sendto(my_sock, &ch, 1, 0, (const struct sockaddr*)&client_addr, client_addr_len);

    close(my_sock);

    return 0;
}