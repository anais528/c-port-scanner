#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

int scan_port(const char *ip, int port) {
    int sockfd;
    struct sockaddr_in target;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) return 0;

    target.sin_family = AF_INET;
    target.sin_port = htons(port);
    inet_pton(AF_INET, ip, &target.sin_addr);

    // Set a timeout
    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 500000;  // 0.5 seconds
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
    setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));

    int result = connect(sockfd, (struct sockaddr *)&target, sizeof(target));
    close(sockfd);

    return (result == 0);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <IP> <start_port> <end_port>\n", argv[0]);
        return 1;
    }

    const char *ip = argv[1];
    int start = atoi(argv[2]);
    int end = atoi(argv[3]);

    printf("Scanning %s from port %d to %d...\n", ip, start, end);

    for (int port = start; port <= end; port++) {
        if (scan_port(ip, port)) {
            printf("[+] Port %d is open\n", port);
        }
    }

    printf("Scan complete.\n");
    return 0;
}
