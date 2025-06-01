#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>

int main(){
    int my_socket;
    struct sockaddr_in sock_addr;
    socklen_t sock_addr_len;
    char ch = 'A';

    my_socket = socket(AF_INET, SOCK_STREAM, 0);

    sock_addr.sin_family = AF_INET;
    sock_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    sock_addr.sin_port = htons(44332);
    sock_addr_len = sizeof(sock_addr);

    if(connect(my_socket, (struct sockaddr *)&sock_addr, sock_addr_len) == -1){
        perror("Client Error");
        exit(EXIT_FAILURE);
    }

    write(my_socket, &ch, 1);
    read(my_socket, &ch, 1);

    printf("Received from server: %c\n", ch);

    close(my_socket);
    return 0;
}