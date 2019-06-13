//
// Created by 김진용 on 2019. 3. 18..
//

#include "server_socket.h"

#include <iostream>
#include <string.h>

#define bzero(b,len) (memset((b), '\0', (len)), (void) 0)

#define DEFAULT_PORT 8080

ServerSocket::ServerSocket() {
    server_address = new sockaddr_in();
    bzero(server_address, sizeof(sockaddr_in));
    server_address->sin_family = AF_INET;
    server_address->sin_addr.s_addr = INADDR_ANY;
    server_address->sin_port = htons(DEFAULT_PORT);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        cerr << "Fail to open socket" << endl;
        exit(EXIT_FAILURE);
    }
}

void ServerSocket::bind(int port) {
    server_address->sin_port = htons(port);

    if (::bind(server_fd, (struct sockaddr*) server_address, sizeof(*server_address)) < 0) {
        cerr << "Fail to bind" << endl;
        exit(EXIT_FAILURE);
    }
}

void ServerSocket::listen() {
    if (::listen(server_fd, 5) < 0) {
        cerr << "Fail to listen" << endl;
        exit(EXIT_FAILURE);
    }
}

void ServerSocket::close() {
    ::close(server_fd);
}