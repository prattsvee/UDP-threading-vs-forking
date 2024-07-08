#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "client_config.h"

int main(int argc, char **argv){

    if (argc != 1) {
        printf("Usage: %s <port>\n", argv[0]);
        exit(0);
    }

    // char *ip = SERVER_IP;
    // //int port = atoi(argv[1]);
    // int port = PORT;

    int sockfd;
    struct sockaddr_in addr;
    char buffer[1024];
    socklen_t addr_size;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    memset(&addr, '\0', sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Loop to continuously get command input from the user
    while (1) {
        printf("Enter command: ");
        fgets(buffer, 1024, stdin);
        // Remove trailing newline character
        buffer[strcspn(buffer, "\n")] = '\0';

        // if (strcmp(buffer, "BYE") == 0) // Allow the user to exit the loop
        //     break;

        sendto(sockfd, buffer, 1024, 0, (struct sockaddr*)&addr, sizeof(addr));
        printf("[+]Data send: %s\n", buffer);

        bzero(buffer, 1024);
        addr_size = sizeof(addr);
        recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)&addr, &addr_size);
        printf("%s\n", buffer);

        if (strstr(buffer, "BYE") != NULL && strstr(buffer, "HELP") == NULL) // Allow the user to exit the loop
            break;
    }

    return 0;
}
