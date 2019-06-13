//
// Created by 김진용 on 2019. 3. 18..
//

#ifndef PROJECT1_WEBSERVER_REQUEST_ACCEPTOR_H
#define PROJECT1_WEBSERVER_REQUEST_ACCEPTOR_H

#include <map>
#include <string>
#include <thread>
#include <queue>
#include <sys/socket.h>
#include <string.h>

#include "server_socket.h"
#include "processor_pool.h"

#define bzero(b,len) (memset((b), '\0', (len)), (void) 0)

using namespace std;

/**
 * socket 으로 클라이언트와 연결되면 해당 fd 를 RequestQueue 에 추가합니다.
 */
class RequestAcceptor {
public:
    RequestAcceptor(ServerSocket* socket, ProcessorPool* processor_pool) {
        this->processor_pool = processor_pool;
        this->socket = socket;
        this->client_address = new sockaddr_in();
        this->socket_address_size = sizeof(*client_address);
        bzero(client_address, socket_address_size);
    }

    ~RequestAcceptor() {
        delete client_address;
    }

    void setActive(bool isActive) {
        this->isActive = isActive;
    }

    void run();

protected:
    bool isActive = true;
    ProcessorPool* processor_pool;

private:
    ServerSocket* socket;
    sockaddr_in* client_address;
    socklen_t socket_address_size;
};

#endif //PROJECT1_WEBSERVER_REQUEST_ACCEPTOR_H