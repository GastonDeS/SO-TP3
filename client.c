#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define PORT 8080

int main(int argc, char **argv) {
    struct sockaddr_in serv_addr;
    char *hello = "entendido\n";
    char buff[1024];
    int sock = socket(PF_INET, SOCK_STREAM, IPPROTO_IP);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "0.0.0.0", &serv_addr.sin_addr);
    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    send(sock , hello , strlen(hello) , 0 );
    send(sock,"itba\n",5,0);
    send(sock,"M4GFKZ289aku\n",13,0);
    send(sock,"fk3wfLCm3QvS\n",13,0);
    send(sock,"too_easy\n",9,0);
    send(sock,".RUN_ME\n",8,0);
    send(sock,"K5n2UFfpFMUN\n",13,0);
    send(sock,"BUmyYq5XxXGt\n",13,0);
    send(sock,"u^v\n",4,0);
    send(sock,"chin_chu_lan_cha\n",17,0);
    send(sock,"gdb_rules\n",10,0);
    send(sock,"normal\n",8,0);
}