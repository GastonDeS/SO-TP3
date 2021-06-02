#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#define PORT 8080

int main(int argc, char **argv) {
    struct sockaddr_in serv_addr;
    char *hello = "entendido\n";
    int sock = socket(PF_INET, SOCK_STREAM, IPPROTO_IP);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "0.0.0.0", &serv_addr.sin_addr);
    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    send(sock , hello , strlen(hello) , 0 );
    send(sock,"ITBA",14,0);
}