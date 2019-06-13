//
// Created by 김진용 on 2019. 3. 14..
//

#include "webserver.h"

#include <iostream>


WebServer::WebServer(Controller* controller, int processor_count) {
    cout << "Create WebServer (processor_count : " << processor_count << ")" << endl;
    this->controller = controller;
    this->request_queue = new RequestQueue();
    this->processor_count = processor_count;
    this->processor_pool = new ProcessorPool(processor_count, request_queue, controller);
}

WebServer::~WebServer() {
    delete request_queue;
    delete processor_pool;
    cout << "Destroy WebServer" << endl;
}

void WebServer::start(int port) {
    cout << "Starting WebServer (port : " << port << ")" << endl;

    //소켓을 생성하고 오픈합니다.
    socket = new ServerSocket();
    socket->bind(port);
    socket->listen();

    //요청을 받아 큐에 대기시킵니다.
    acceptor = new RequestAcceptor(socket, processor_pool);
    request_accept_thread = new thread(&RequestAcceptor::run, acceptor);
}

void WebServer::stop() {
    cout << "Shutdown WebServer" << endl;
    //RequestAcceptor 와 Processor 를 중지시킵니다.
    acceptor->setActive(false);

    //모든 요청에 응답하기를 기다립니다.
    processor_pool->join();

    socket->close();
//    request_accept_thread->join();
    delete acceptor;
    delete socket;
}