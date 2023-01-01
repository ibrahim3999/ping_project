#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <errno.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/socket.h>


#define SERVER_PORT 3000
#define SERVER_IP_ADDRESS "127.0.0.1"

// run 2 programs using fork + exec
// command: make clean && make all && ./partb
int setSock();

int main()
{
int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(client_socket == -1) {
        fprintf(stderr, "Socket ERROR - could not create the socket : %s\n", strerror(errno));
        exit(1); 
    }
    else printf("[+]TCP protocol socket created.\n");


    //Sets the first count bytes of destination
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERVER_PORT);
    int rval = inet_pton(AF_INET, (const char*)SERVER_IP_ADDRESS, &server_address.sin_addr);
    if(rval <= 0) {
        printf("Failed to convert an IP to Binary format!");
        exit(1); 
       
    }

    // Connect to the receiver
    int connection = connect(client_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    if(connection == -1) {
        fprintf(stderr, "The connecting to watchdog failed - error msg code:%s\n", strerror(errno));
        exit(1); 
    }
    else {
        printf("[+]ping connected to the watchdog successfully!!\n");
    }

    //sending the status of the ping to watchdog
    printf("[+]send the status of the ping\n");

    
    size = send(client_socket, buffer, sizeof(buffer), 0);
        if(size<0){
            printf("ERROR - Send the half 1 of f2.txt-> failed with error!\n");
            exit(1);
          }


    //get a msg of time out from watchdog if 10 seconds left!
    recv(client_socket, &xorcheck, sizeof(xorcheck), 0);


    //################################################
    char *args[2];
    // compiled watchdog.c by makefile
    args[0] = "./watchdog";
    args[1] = NULL;
    int status;
    int pid = fork();
    if (pid == 0)
    {
        printf("in child \n");
        execvp(args[0], args);
    }
    else {

    }
    wait(&status); // waiting for child to finish before exiting
    printf("child exit status is: %d", status);

    //close the TCP socket with watchdog
    close(client_socket);
    return 0;
}

