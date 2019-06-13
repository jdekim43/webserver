//
// Created by 김진용 on 2019. 3. 14..
//

#ifndef PROJECT1_WEBSERVER_CONTROLLER_H
#define PROJECT1_WEBSERVER_CONTROLLER_H

#include <utility>

#include "request.h"
#include "response.h"

using namespace std;

/**
 * Request 를 보고 적합한 Response 를 생성합니다.
 */
class Controller {
public:
    Controller() = default;

    virtual ~Controller() = default;

    virtual Response* handle(Request*) = 0;

    string getContentType(string);
};

/**
 * Request 의 path 를 이용해 해당하는 파일을 찾아 파일 내용이 담긴 Response 를 생성합니다.
 */
class FileController : public Controller {
public:
    explicit FileController(string web_root) : Controller() {
        this->web_root = move(web_root);
    }

    ~FileController() override = default;

    Response* handle(Request*) override;

protected:
    string web_root;
};

#endif //PROJECT1_WEBSERVER_CONTROLLER_H