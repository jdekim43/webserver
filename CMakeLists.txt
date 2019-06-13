cmake_minimum_required(VERSION 3.12)
project(project1_webserver)

set(CMAKE_CXX_STANDARD 14)

add_executable(project1_webserver main.cpp request.h request.cpp response.h response.cpp controller.h processor.h controller.cpp processor.cpp webserver.h webserver.cpp request_acceptor.h request_acceptor.cpp server_socket.h server_socket.cpp request_queue.h request_queue.cpp processor_pool.h processor_pool.cpp)