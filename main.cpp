#include <iostream>
#include <sstream>

#include "webserver.h"

#define DEFAULT_PORT 8080
#define DEFAULT_WEB_ROOT "./web_root"
#define DEFAULT_PROCESSOR_COUNT 4

using namespace std;

int main(int argc, char* argv[]) {
    //웹서버에서 사용할 포트 번호
    int port = DEFAULT_PORT;
    //FileController 에서 읽어올 파일이 존재하는 폴더 경로
    string web_root = DEFAULT_WEB_ROOT;
    //요청을 처리할 프로세서 쓰레드 개수
    int processor_count = DEFAULT_PROCESSOR_COUNT;

    switch (argc) {
        default: {
            stringstream processor_count_stream(argv[3]);
            int num;
            if (!(processor_count_stream >> num).fail()) {
                processor_count = num;
            }
        }
        case 3: {
            stringstream processor_count_stream(argv[2]);
            string path;
            if (!(processor_count_stream >> path).fail()) {
                web_root = path;
            }
        }
        case 2: {
            stringstream port_stream(argv[1]);
            int num;
            if (!(port_stream >> num).fail()) {
                port = num;
            }
        }
        case 1:
        case 0:
            break;
    }

    cout << "Use web_root : " << web_root << endl;
    //요청을 처리할 컨트롤러를 생성합니다. FileController 는 request 의 path 를 보고 web_root 하위에서 해당 파일을 반환합니다.
    Controller* controller = new FileController(web_root);

    //웹서버를 생성합니다.
    WebServer server(controller, processor_count);

    //웹서버를 실행합니다.
    server.start(port);

    cout << "Press 'Enter' key to shutdown\n\n";
    cin.get();

    //웹서버를 종료합니다.
    server.stop();

    delete controller;

    return 0;
}