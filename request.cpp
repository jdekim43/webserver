//
// Created by 김진용 on 2019. 3. 14..
//
#include "request.h"

#include <sstream>

Request::Request(string* message) {
    this->message = message;
    this->headers = new map<string, string>();

    //헤더 영역과 바디 영역을 구분합니다.
    size_t header_split_index = message->find("\r\n\r\n", 0);
    string header = message->substr(0, header_split_index);
    body = new string(message->substr(header_split_index, message->length() - header_split_index));

    //헤더 영역을 처리하기위해 스트림을 만듭니다.
    istringstream header_stream(header);
    string header_line;

    //헤더 첫번째 줄을 가져옵니다.
    getline(header_stream, header_line, '\n');

    //가져오 헤더 첫번째 줄로부터 method, path, http_version 정보를 가져옵니다.
    size_t first_delimiter_position = header_line.find(' ');
    size_t second_delimiter_position = header_line.find(' ', first_delimiter_position + 1);
    method = header_line.substr(0, first_delimiter_position);
    path = header_line.substr(first_delimiter_position + 1, second_delimiter_position - first_delimiter_position - 1);
    http_version = header_line.substr(second_delimiter_position + 1,
                                      header_line.length() - second_delimiter_position - 2);

    //헤더 영역에서 나머지 부분은 key-value 형태를 가지고 있으므로 구분자인 ':' 를 활용하여 map 에 저장합니다.
    while (getline(header_stream, header_line, '\n')) {
        size_t delimiter_position = header_line.find(':');

        if (header_line.length() == 0 || delimiter_position == 0) {
            continue;
        }

        headers->insert(pair<string, string>(header_line.substr(0, delimiter_position),
                                             header_line.substr(delimiter_position + 1)));
    }
}

Request::~Request() {
    delete message;
    delete headers;
    delete body;
}