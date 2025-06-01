#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>


int main(){
    int serv_sock, client_sock;
    socklen_t serv_addr_len, client_addr_len;
    struct sockaddr_in serv_addr, client_addr;

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = PF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(44332);
    serv_addr_len = sizeof(serv_addr);

    if(bind(serv_sock, (struct sockaddr*)&serv_addr, serv_addr_len) == -1)
    {
        perror("Bind Error");
        exit(EXIT_FAILURE);
    }

    listen(serv_sock, 1);

    char ch[100];
    printf("Server waiting...\n");

    client_addr_len = sizeof(client_addr);
    client_sock = accept(serv_sock, (struct sockaddr*)&client_addr, &client_addr_len);

    read(client_sock, ch, 100);
    
    while(1){
        printf("client: %s\nreply:", ch);
        scanf(" %99[^\n]", ch);
        write(client_sock, ch, 100);
        read(client_sock, ch, 100);
    }

    close(client_sock);
    close(serv_sock);

    return 0;


}