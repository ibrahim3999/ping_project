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
int timeout_flag = 0;

void timeout_handler(int sig){
    printf("Timeout happened!\n");
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
    
    char buffreExit[256];
    char buffer_timeout[1];
    buffer_timeout[0]='0';
    
    
   

    // Run a loop to Update Watchdog Timer if NEW PING sent msg and reset the timer
    while (1) {
        printf("check in While loop-WATCHDOG\n");

        // Set the timer to expire after 10 seconds
    struct itimerval timer;
    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 0;
    setitimer(ITIMER_REAL, &timer, NULL);

       // Check if BETTER_PING.C send new packet->Reset timer
        
        int update = recv(client_socket, &buffreExit, sizeof(buffreExit), 0);
        printf("%d the update to timer\n",update);
        if (update>0) {
            // Reset the timer
            timer.it_value.tv_sec = 10;
            timer.it_value.tv_usec = 0;
            setitimer(ITIMER_REAL, &timer, NULL);
            printf("Check Timer reset\n");
            
        }
        if (timeout_flag)
        {
            //send a timeout message
            printf("the time out - WATCHDOG");
            timeout_flag =0;
            close(receiver_socket);
        }
        
        
    }

    bzero(buffer_timeout, sizeof(buffer_timeout));
    send(client_socket,buffer_timeout, sizeof(buffer_timeout),0);

    
    return 0;
}