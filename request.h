//
// Created by 김진용 on 2019. 3. 14..
//

#ifndef PROJECT1_WEBSERVER_REQUEST_H
#define PROJECT1_WEBSERVER_REQUEST_H

#include <string>
#include <map>

using namespace std;

/**
 * 요청에 대한 내용을 담고 있으며 message 를 파싱해 값을 설정합니다.
 */
class Request {
public:
    explicit Request(string*);

    ~Request();

    string getPath() {
        return path;
    }

    string getHttpVersion() {
        return http_version;
    }

private:
    string* message;
    string method;
    string path;
    string http_version;
    map<string, string>* headers;
    string* body;
};

#endif //PROJECT1_WEBSERVER_REQUEST_H