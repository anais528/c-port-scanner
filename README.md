C-Port-Scanner: Simple TCP Port Connectivity Tool
🌟 Overview
This is a lightweight, command-line TCP port scanner implemented in C. It is designed to check the connectivity (open status) of a defined range of TCP ports on a target IP address.

The project demonstrates fundamental network programming concepts in C using the standard Unix socket API (socket, connect, setsockopt).

🛠️ Features
Range Scanning: Scans a contiguous range of ports specified by the user.

Target IP: Accepts a target IP address (IPv4) as a command-line argument.

Non-Blocking Check: Uses setsockopt to set a short receive and send timeout (0.5 seconds) to ensure the scan does not hang indefinitely on filtered or unresponsive ports.

Simple Output: Reports which ports within the range successfully establish a TCP connection.

⚙️ Build Instructions
Prerequisites
You will need a C compiler (like GCC) and standard development libraries available on most Unix-like systems (Linux, macOS).

Compilation
Compile the source file using GCC:

Bash

gcc -o portscan portscan.c
This will produce an executable file named portscan.

🚀 Usage
Syntax
The program requires exactly three arguments: the target IP address, the starting port number, and the ending port number.

Bash

./portscan <IP_ADDRESS> <START_PORT> <END_PORT>
Example
To scan the local machine (127.0.0.1) from port 20 (FTP) to port 100:

Bash

./portscan 127.0.0.1 20 100
Example Output
Scanning 127.0.0.1 from port 20 to 100...
[+] Port 22 is open
[+] Port 80 is open
Scan complete.
💻 Code Details
The core functionality resides in the scan_port function:

C

int scan_port(const char *ip, int port) {
    // 1. Create a TCP socket (AF_INET, SOCK_STREAM)
    // 2. Configure target sockaddr_in structure with IP and port
    // 3. Set SO_RCVTIMEO and SO_SNDTIMEO (0.5s)
    // 4. Attempt connection using connect()
    // 5. Close socket and return 1 if connect() was successful (result == 0)
}
The timeout configuration is critical for performance and is achieved by setting socket options:

C

struct timeval timeout;
timeout.tv_sec = 0;
timeout.tv_usec = 500000; // 0.5 seconds
setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
