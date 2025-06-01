#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<string.h>

int main(){
    int server_sock, client_sock;
    socklen_t server_addr_len, client_addr_len;

    struct sockaddr_un server_addr, client_addr;

    unlink("my-unix-domain-socket");

    server_sock = socket(AF_UNIX, SOCK_STREAM, 0);

    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, "my-unix-domain-socket");
    server_addr_len = sizeof(server_addr);

    int retval = bind(server_sock, (struct sockaddr*)&server_addr, server_addr_len);

    if(retval == -1){
        perror("Bind Error");
        exit(EXIT_FAILURE);
    }

    listen(server_sock, 5);

    while(1){
        char ch;
        printf("Server waiting...\n");

        client_addr_len = sizeof(client_addr);
        client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_addr_len);
        

        read(client_sock, &ch, 1);
        ch++;
        write(client_sock, &ch, 1);
        
        close(client_sock);
    }

    close(server_sock);
    return 0;
}