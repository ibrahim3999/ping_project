#include <stdio.h>
#include <stdio.h>
#include <signal.h>
#include <sys/time.h>

#define TimeOut "timeout"
int main()
{
    char buffreExit[1];
    char buffer_timeout[8];
    printf("hello partb");
    /*
    while (timer < 10seconds)
    {
        recv();
        timer = 0seconds;
    }
    */

   // Set the timer to expire after 10 seconds
    struct itimerval timer;
    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;
    setitimer(ITIMER_REAL, &timer, NULL);

    // Run a loop to Update Watchdog Timer if NEW PING sent msg and reset the timer
    while (1) {
        
        // Check if BETTER_PING.C send new packet->Reset timer
        bzero(buffreExit, sizeof(buffreExit));
        if ((recv(client_socket, &buffreExit, sizeof(buffreExit), 0))>0) {
            // Reset the timer
            timer.it_value.tv_sec = 10;
            timer.it_value.tv_usec = 0;
            setitimer(ITIMER_REAL, &timer, NULL);
            
        }
        else break;
    }
    send(client_socket,TimeOut, sizeof(buffer_timeout),0);

        return 0;
}