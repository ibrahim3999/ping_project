# ping_project

This is a C program that utilizes raw sockets and the ping command to ping a specified IP address. It also have a timeout mechanism which runs as a watchdog process that regularly checks if the main process (ping process) is still running and if not, it sends an update message to the sender process.
It uses a combination of system calls such as `socket()`,`bind()`,`listen()`, `accept()` and `close()` to create a simple TCP socket server and signal() function to handle the timeout signal.  

## Requirements
- A C compiler (e.g. GCC)
- A UNIX-based operating system (the code was tested on Ubuntu)

## Compiling and running the code
1) Make sure that you have a C compiler installed on your system.

2) Clone the repository and navigate to the project directory.
3) Use the following command to compile the code:
    sudo su 
 4) make all 
 5) To run the code, you need to open two terminal windows and execute the following commands on both terminals:
    ./parta 
    ./partb
 6) The parta is the main process which pings the specified IP address and the partb is the watchdog process which checks the main process's status and sends       update message to the sender if the main process has stopped.
 7) You should see the ping results on the terminal window running the parta command.
 8) You can also change the IP address that is being pinged by modifying the `PingIp`
    variable in the source code and you can Like that:
    ./parta 8.8.8.8 or ./partb 8.8.8.8
 
![](https://github.com/ibrahim3999/ping_project/blob/main/Pic/ping_exp.jpeg)

