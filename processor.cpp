//
// Created by 김진용 on 2019. 3. 14..
//

#include "processor.h"

#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

#define bzero(b,len) (memset((b), '\0', (len)), (void) 0)

#define BUFFER_SIZE 4096

void Processor::start() {
    is_enable = true;

    if (is_active) {
        return;
    }

    processor_thread = new thread(&Processor::run, this);
}

void Processor::stop() {
    is_enable = false;

//    if (processor_thread != nullptr) {
//        processor_thread->join();
//    }
}

string* Processor::readMessage(int accept_socket) {
    auto* message = new string();
    char buffer[BUFFER_SIZE] = {0};

    ssize_t size;
    while ((size = read(accept_socket, buffer, BUFFER_SIZE)) == BUFFER_SIZE && size > 0) {
        message->append(buffer);
        bzero(buffer, BUFFER_SIZE);
    }
    message->append(buffer);

    return message;
}

void Processor::run() {
    is_active = true;
    while (is_enable && !(request_queue->empty())) {
        //큐에서 처리할 fd 를 가져옵니다.
        int accept_socket = request_queue->pop();

        //큐에서 가져온 fd 가 0보다 작을경우 정상적인 값이 아닌 것으로 판단하고 다음 요청을 처리합니다.
        if (accept_socket < 0) {
            continue;
        }

        //소켓으로부터 요청 메시지를 읽어옵니다.
        string* request_message = readMessage(accept_socket);

        if (request_message->length() == 0) {
            close(accept_socket);
            continue;
        }

        //읽어온 메시지를 콘솔에 출력합니다.
        cout << "=========== New Request ===========\n" << *request_message << endl;

        auto* request = new Request(request_message);

        //Controller 를 이용해 Request 로 부터 Response 를 생성합니다.
        Response* response = controller->handle(request);

        //response 로부터 http 형식에 맞는 message 를 생성합니다.
        string* response_message = response->serialize();

        //생성된 response_message 를 클라이언트에 보냅니다.
        send(accept_socket, response_message->c_str(), response_message->size(), 0);

        close(accept_socket);

        delete request;
        delete response;
        delete response_message;
    }

    is_active = false;
}