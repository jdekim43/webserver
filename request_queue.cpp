//
// Created by 김진용 on 2019. 3. 19..
//

#include "request_queue.h"

bool RequestQueue::empty() {
    bool is_empty;

    m.lock();
    is_empty = real_queue.empty();
    m.unlock();

    return is_empty;
}

void RequestQueue::push(int socket_fd) {
    m.lock();
    real_queue.push(socket_fd);
    m.unlock();
}

int RequestQueue::pop() {
    int socket_fd = -1;

    m.lock();
    if (!real_queue.empty()) {
        socket_fd = real_queue.front();
        real_queue.pop();
    }
    m.unlock();

    return socket_fd;
}