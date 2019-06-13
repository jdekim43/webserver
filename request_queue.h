//
// Created by 김진용 on 2019. 3. 19..
//

#ifndef PROJECT1_WEBSERVER_REQUEST_QUEUE_H
#define PROJECT1_WEBSERVER_REQUEST_QUEUE_H

#include <queue>
#include <mutex>

using namespace std;

/**
 * 여러개의 요청을 동시에 처리하기 위해 queue 를 사용합니다.
 * Processor 가 여러 쓰레드에서 동작하므로 이 queue 는 thread-safe 합니다.
 */
class RequestQueue {
public:
    bool empty();

    void push(int);

    int pop();

private:
    queue<int> real_queue;
    mutex m;
};

#endif //PROJECT1_WEBSERVER_REQUEST_QUEUE_H