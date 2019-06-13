//
// Created by 김진용 on 2019. 3. 18..
//

#include "request_acceptor.h"

void RequestAcceptor::run() {
    int last_accept_socket = 0;

    while (isActive) {
        last_accept_socket = accept(socket->getServerFd(), (sockaddr*) client_address, &socket_address_size);
        if (last_accept_socket < 0) {
            continue;
        }

        processor_pool->proceed(last_accept_socket);
    }
}