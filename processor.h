//
// Created by 김진용 on 2019. 3. 14..
//

#ifndef PROJECT1_WEBSERVER_PROCESSOR_H
#define PROJECT1_WEBSERVER_PROCESSOR_H

#include <map>
#include <queue>
#include <thread>
#include <string>

#include "controller.h"
#include "request_queue.h"

using namespace std;

/**
 * RequestQueue 에서 연결을 가져와 Controller 를 이용해 요청을 처리합니다.
 */
class Processor {
public:
    Processor(RequestQueue* request_queue, Controller* controller) {
        this->request_queue = request_queue;
        this->controller = controller;
        this->processor_thread = nullptr;
    }

    bool isActive() {
        return is_active;
    }

    void start();

    void stop();

protected:
    bool is_active = false;
    bool is_enable = true;

    string* readMessage(int);

    void run();

private:
    RequestQueue* request_queue;
    Controller* controller;
    thread* processor_thread;
};

#endif //PROJECT1_WEBSERVER_PROCESSOR_H