//
// Created by 김진용 on 2019. 3. 14..
//

#include "response.h"

Response::Response(string http_version, int status_code, string status_message, string content_type, string* body) {
    this->http_version = move(http_version);
    this->status_code = status_code;
    this->status_message = move(status_message);
    this->content_type = move(content_type);
    this->content_length = body->size();
    this->body = body;
}

string* Response::serialize() {
    return new string(
            http_version + " " + to_string(status_code) + " " + status_message + "\r\n"
            + "Content-Type: " + content_type + "\r\n"
            + "Content-Length: " + to_string(content_length) + "\r\n"
            + "\r\n"
            + *body
    );
}

SuccessResponse::SuccessResponse(string http_version, string content_type, string* body)
        : Response(move(http_version), 200, "OK", move(content_type), body) {

}

NotFoundResponse::NotFoundResponse(string http_version)
        : Response(std::move(http_version), 404, "Not Found", "text/plain", new string("404 Not Found")) {

}