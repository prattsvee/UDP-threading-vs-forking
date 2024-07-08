#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdbool.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include "calculator.h"
#include "server_config.h"


#define MAX_COMMAND_LENGTH 1024


typedef enum {
    MODE_NONE,
    MODE_AREA,
    MODE_VOL,
    MODE_TEMP,
    MODE_WGT
} Mode;

Mode current_mode = MODE_NONE;

bool processRequest(char* input, char* output, struct sockaddr_in client_addr);

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[MAX_COMMAND_LENGTH];
    char response[MAX_COMMAND_LENGTH];

    // Create UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Initialize server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(SERVER_PORT);

    // Bind socket to server address
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    printf("UDP Server up and listening on port %d\n", SERVER_PORT);

    while (1) {
        socklen_t addr_len = sizeof(client_addr);

        // Receive data from client
        int recv_len = recvfrom(sockfd, buffer, MAX_COMMAND_LENGTH, 0, (struct sockaddr*)&client_addr, &addr_len);
        if (recv_len == -1) {
            perror("recvfrom");
            continue;
        }

        // Null-terminate the received buffer
        buffer[recv_len] = '\0';

        // Fork a child process to handle the client request
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            continue;
        } else if (pid == 0) {
            // Child process
            if (processRequest(buffer, response, client_addr)) {
                // Client requested to close the connection
                printf("Connection closed by client\n");
                exit(EXIT_SUCCESS);
            }
            // Send response to client
            if (sendto(sockfd, response, strlen(response), 0, (struct sockaddr*)&client_addr, sizeof(client_addr)) == -1) {
                perror("sendto");
                exit(EXIT_FAILURE);
            }
            printf("Response sent: %s\n", response);
            exit(EXIT_SUCCESS);
        } else {
            // Parent process
            // Wait for any finished child process
            while (waitpid(-1, NULL, WNOHANG) > 0);
        }
    }

    close(sockfd);
    return 0;
}

bool processRequest(char* input, char* output, struct sockaddr_in client_addr) {
    char command[MAX_COMMAND_LENGTH];
    char mode[10], fromUnit[10], toUnit[10];
    double value;

    // Parse the input command
    if (sscanf(input, "%s", command) != 1) {
        // Failed to parse command
        strcpy(output, "500 Syntax Error, command unrecognized.");
        return false;
    }

    if (strcmp(command, "HELO") == 0) {
        // HELO command
        sprintf(output, "200 HELO %s(UDP) - Welcome.", inet_ntoa(client_addr.sin_addr));
        return false;
    } else if (strcmp(command, "HELP") == 0) {
        // HELP command
        strcpy(output, "200 HELP - Available commands: HELO, HELP, AREA, VOL, TEMP, WGT, BYE");
        return false;
    } else if (strcmp(command, "BYE") == 0) {
        // BYE command
        sprintf(output, "200 BYE %s(UDP) - Goodbye.", inet_ntoa(client_addr.sin_addr));
        return false; 
    }else if (strcmp(command, "AREA") == 0 || strcmp(command, "VOL") == 0 ||
               strcmp(command, "TEMP") == 0 || strcmp(command, "WGT") == 0) {
        // Mode selection command
        if (strcmp(command, "AREA") == 0) {
            current_mode = MODE_AREA;
        } else if (strcmp(command, "VOL") == 0) {
            current_mode = MODE_VOL;
        } else if (strcmp(command, "TEMP") == 0) {
            current_mode = MODE_TEMP;
        } else if (strcmp(command, "WGT") == 0) {
            current_mode = MODE_WGT;
        }

        // Provide information about the selected mode and available units
        switch (current_mode) {
            case MODE_AREA:
                strcpy(output, "210 AREA Mode ready! Available units: SQRMT, SQRML, SQRIN, SQRFT");
                break;
            case MODE_VOL:
                strcpy(output, "220 VOL Mode ready! Available units: LTR, GALNU, GALNI, CUBM");
                break;
            case MODE_TEMP:
                strcpy(output, "230 TEMP Mode ready! Available units: CELS, FAHR, KELV");
                break;
            case MODE_WGT:
                strcpy(output, "240 WGT Mode ready! Available units: KILO, PND, CART");
                break;
            default:
                strcpy(output, "500 Internal Server Error");
                break;
        }

        return false;
    } else if (current_mode != MODE_NONE) {

        // Process conversion request in the selected mode
        if (sscanf(input, "%s %s %lf", fromUnit, toUnit, &value) != 3) {
            // Syntax error in conversion request
            strcpy(output, "501 Syntax error in parameters or arguments.");
            return false;
        }

        // Perform unit conversion based on the selected mode
        double result = -1;
        switch (current_mode) {
            case MODE_AREA:
                result = convertArea(fromUnit, toUnit, value);
                break;
            case MODE_VOL:
                result = convertVolume(fromUnit, toUnit, value);
                break;
            case MODE_TEMP:
                result = convertTemperature(fromUnit, toUnit, value);
                break;
            case MODE_WGT:
                result = convertWeight(fromUnit, toUnit, value);
                break;
            default:
                strcpy(output, "503 Bad sequence of commands.");
                return false;
        }

        if (result != -1) {
            // Conversion successful
            sprintf(output, "250 %.2lf", result);
        } else {
            // Invalid conversion request
            strcpy(output, "504 Bad conversion request.");
        }

        return false;
    } else {
        // Invalid sequence of commands
        strcpy(output, "503 Bad sequence of commands.");
        return false;
    }
}




