//
// Created by 김진용 on 2019. 3. 14..
//

#ifndef PROJECT1_WEBSERVER_RESPONSE_H
#define PROJECT1_WEBSERVER_RESPONSE_H

#include <string>

using namespace std;

/**
 * 클라이언트에 보낼 정보를 담고 있으며 http 양식에 맞춰 message 를 생성합니다.
 */
class Response {
public:
    Response(string, int, string, string, string*);

    ~Response() {
        delete body;
    }

    string* serialize();

private:
    string http_version;
    int status_code;
    string status_message;
    string content_type;
    unsigned long content_length;
    string* body;
};

class SuccessResponse : public Response {
public:
    SuccessResponse(string, string, string*);
};

class NotFoundResponse : public Response {
public:
    explicit NotFoundResponse(string);
};

#endif //PROJECT1_WEBSERVER_RESPONSE_H