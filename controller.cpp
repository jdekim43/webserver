//
// Created by 김진용 on 2019. 3. 14..
//

#include "controller.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

string Controller::getContentType(string extension) {
    transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

    if (extension == "html") {
        return "text/html";
    } else if (extension == "ico") {
        return "image/vnd.microsoft.icon";
    } else if (extension == "jpg" || extension == "jpeg") {
        return "image/jpeg";
    } else if (extension == "png") {
        return "image/png";
    } else if (extension == "js") {
        return "text/javascript";
    } else if (extension == "css") {
        return "text/css";
    } else if (extension == "gif") {
        return "image/gif";
    } else if (extension == "pdf") {
        return "application/pdf";
    } else if (extension == "mp3") {
        return "audio/mpeg3";
    }

    return "application/octet-stream";
}

Response* FileController::handle(Request* request) {
    string http_version = request->getHttpVersion();

    //읽을 파일 경로
    string path = web_root + request->getPath();

    //경로의 끝이 '/' 로 끝날 경우 해당 디렉토리의 index.html 을 반환합니다.
    if (path[path.size() - 1] == '/') {
        path = path + "index.html";
    }

    cout << "Serve file : " << path << endl;

    //요청한 파일을 오픈합니다.
    ifstream inFile(path, ios::in | ios::binary);
    string* response_body;

    //파일을 읽을 수 있으면 처리하고 아니면 NotFoundResponse 를 반환합니다.
    if (inFile.is_open()) {
        //파일로부터 내용을 읽어 buffer 에 저장합니다.
        vector<unsigned char> buffer(istreambuf_iterator<char>(inFile), {});
        //buffer 를 string 으로 만들어 response_body 에 저장합니다.
        response_body = new string(buffer.begin(), buffer.end());
        //파일을 닫습니다.
        inFile.close();
    } else {
        return new NotFoundResponse(http_version);
    }

    //확장자를 가져오고 확장자를 이용해 content_type 을 매칭시킵니다.
    size_t extension_position = path.find_last_of('.');
    string extension = path.substr(extension_position + 1);
    string content_type = getContentType(extension);

    //위 내용을 이용해 Response 를 생성합니다.
    return new SuccessResponse(http_version, content_type, response_body);
}