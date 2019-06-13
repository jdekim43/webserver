//
// Created by 김진용 on 2019. 4. 4..
//

#include "processor_pool.h"

void ProcessorPool::proceed(int client_socket_fd) {
    request_queue->push(client_socket_fd);

    for (int i = 0; i < processor_count; i++) {
        Processor* processor = processors[i];
        if (!(processor->isActive())) {
            processor->start();
            break;
        }
    }
}

void ProcessorPool::join() {
    for (int i = 0; i < processor_count; i++) {
        processors[i]->stop();
    }
}