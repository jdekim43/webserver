//
// Created by 김진용 on 2019. 3. 18..
//

#ifndef PROJECT1_WEBSERVER_SERVER_SOCKET_H
#define PROJECT1_WEBSERVER_SERVER_SOCKET_H

#include <netinet/in.h>
#include <unistd.h>

using namespace std;

/**
 * ServerSocket 은 socket 을 생성/관리합니다.
 */
class ServerSocket {
public:
    ServerSocket();

    /**
     * socket 을 port 에 bind 시킵니다.
     *
     * int port     port number
     */
    void bind(int);

    /**
     * 소켓 연결 요청을 받기 시작합니다.
     */
    void listen();

    /**
     * 소켓을 닫습니다.
     */
    void close();

    int getServerFd() {
        return server_fd;
    }

protected:
    sockaddr_in* server_address;

private:
    int server_fd;
};

#endif //PROJECT1_WEBSERVER_SERVER_SOCKET_H