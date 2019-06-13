//
// Created by 김진용 on 2019. 4. 4..
//

#ifndef PROJECT1_WEBSERVER_PROCESSOR_POOL_H
#define PROJECT1_WEBSERVER_PROCESSOR_POOL_H

#include "processor.h"

/**
 * 설정한 개수만큼 Processor 를 만들고 요청이 들어오면 Processor 들을 실행해 요청을 처리한다.
 */
class ProcessorPool {
public:
    ProcessorPool(int processor_count, RequestQueue* request_queue, Controller* controller) {
        this->request_queue = request_queue;
        this->processor_count = processor_count;
        this->processors = new Processor* [processor_count];

        for (int i = 0; i < processor_count; i++) {
            processors[i] = new Processor(request_queue, controller);
        }
    }

    ~ProcessorPool() {
        for (int i = 0; i < processor_count; i++) {
            delete processors[i];
        }

        delete[] processors;
    }

    void proceed(int);

    void join();

private:
    RequestQueue* request_queue;
    int processor_count;
    Processor** processors;
};

#endif //PROJECT1_WEBSERVER_PROCESSOR_POOL_H
