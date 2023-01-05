#include <stdio.h>
#include <signal.h>//not important
#include <sys/time.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <errno.h>
#include <strings.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

#define SERVER_PORT 3000
#define SERVER_IP_ADDRESS "127.0.0.1"

int setSock();
char buffer_timeout[1];
int timeout_flag = 0;
int receiver_socket;
char PingIp[32];

int update2(int sock){
    bzero(PingIp, sizeof(PingIp));
    int check_send = send(sock, PingIp, sizeof(PingIp), 0);
    if (check_send == -1) {
    // an error occurred
    fprintf(stderr, "Eeeeeeerror sending message:in update func WATCHDOG %s\n", strerror(errno));
    } else {
    printf("%d bytes sent successfully - in update func WATCHDOG\n", check_send);
    close(receiver_socket);
    }
}

void timeout_handler(int sig){
    printf("server %s cannot be reached\n",PingIp);
    update2(receiver_socket);
    //exit(1);
    timeout_flag = 1;
}



int main()
{

    
    struct sockaddr_in client_addr;
    struct sockaddr_in server_addr;
    socklen_t client_addr_length = sizeof(client_addr);
    signal(SIGPIPE, SIG_IGN);
    int receiver_socket = -1;
    int update=0;
    signal(SIGALRM,timeout_handler);

int setSock(){

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(SERVER_PORT); 

    // create a socket lisener for sender.
    int receiver_socket = -1;
    if((receiver_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("Couldn't create a socket listener : %d\n",errno);
        exit(1);
        
    }
    

    // connect the client
    
    if(bind(receiver_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        printf("Bind failed with error code : %d" , errno);
        exit(1);
    }

    printf("[+]Receiver connected to the Sender successfully!-WATCHDOG\n\n");


    if(listen(receiver_socket, 500) == -1) {
        printf("listen failed with error code : %d",errno);
        exit(1);
    }
    return receiver_socket;
}

receiver_socket = setSock(); //Creating the socket
    
    printf("[+]TCP protocol socket created -> Waiting for connection with sender-WATCHDOG\n");

    

        memset(&client_addr, 0, sizeof(client_addr));
        client_addr_length = sizeof(client_addr);

        //The receiver accept the connection
        
        int client_socket = accept(receiver_socket, (struct sockaddr *) &client_addr, &client_addr_length);
        if (client_socket == -1) {
            printf("listen failed with error code :%d \n",errno);
            exit(1);
        } else {
            printf("[+]Sender number connection accepted-WATCHDOG\n");
        }
    

    printf("\nhello partb-WATCHDOG\n");
    char buffreExit[1];
    char buffer_timeout[1];
    buffer_timeout[0]='0';
    

   // Set the timer to expire after 10 seconds
    struct itimerval timer;
    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;
    setitimer(ITIMER_REAL, &timer, NULL);

    // Run a loop to Update Watchdog Timer if NEW PING sent msg and reset the timer
    while (1) {
        printf("check1-WATCHDOG\n");
       // Check if BETTER_PING.C send new packet->Reset timer
        
        int update = recv(client_socket, &buffreExit, sizeof(buffreExit), 0);
        printf("%d+++\n",update);
        if (update>0) {
            // Reset the timer
            timer.it_value.tv_sec = 10;
            timer.it_value.tv_usec = 0;
            setitimer(ITIMER_REAL, &timer, NULL);
            printf("Check Timer reset\n");
            //update2(receiver_socket);
            
        }
        
    }

    
    

    
    return 0;
}