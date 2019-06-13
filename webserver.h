//
// Created by 김진용 on 2019. 3. 14..
//

#ifndef PROJECT1_WEBSERVER_WEBSERVER_H
#define PROJECT1_WEBSERVER_WEBSERVER_H

#include <map>
#include <thread>

#include "processor_pool.h"
#include "request_acceptor.h"

using namespace std;

/**
 * WebServer 는 요청을 처리하기 위해 필요한 모든것들을 생성하고 관리합니다.
 * WebServer 를 사용하기 위해서는 응답을 생성하는 Controller 와 Processor 의 쓰레드 개수가 필요합니다..
 */
class WebServer {
public:
    WebServer(Controller*, int);

    ~WebServer();

    /**
     * 웹서버를 실행합니다.
     *
     * int port     port number
     */
    void start(int);

    /**
     * 웹서버를 종료합니다.
     */
    void stop();

protected:
    RequestQueue* request_queue;

private:
    ServerSocket* socket;
    RequestAcceptor* acceptor;
    thread* request_accept_thread;
    int processor_count;
    ProcessorPool* processor_pool;
    Controller* controller;
};

#endif //PROJECT1_WEBSERVER_WEBSERVER_H