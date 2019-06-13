CC = g++ -std=c++14

OBJECTS = main.o webserver.o server_socket.o request_acceptor.o processor_pool.o processor.o controller.o request_queue.o request.o response.o
TARGET = myserver

ifeq (run,$(firstword $(MAKECMDGOALS)))
  RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  $(eval $(RUN_ARGS):;@:)
endif

build: $(TARGET)
	rm -f $(OBJECTS)

run: build
	./$(TARGET) $(RUN_ARGS)

$(TARGET) : $(OBJECTS)
	$(CC) -pthread -o $(TARGET) $(OBJECTS)

main.o: webserver.h main.cpp
	$(CC) -c main.cpp

webserver.o: webserver.h webserver.cpp processor_pool.h request_acceptor.h
	$(CC) -pthread -c webserver.cpp

server_socket.o: server_socket.h server_socket.cpp
	$(CC) -c server_socket.cpp

request_acceptor.o: request_acceptor.h request_acceptor.cpp server_socket.h processor_pool.h
	$(CC) -pthread -c request_acceptor.cpp

processor_pool.o: processor_pool.h processor_pool.cpp
	$(CC) -c processor_pool.cpp

processor.o: processor.h processor.cpp controller.h request_queue.h
	$(CC) -pthread -c processor.cpp

controller.o: controller.h controller.cpp request.h response.h
	$(CC) -c controller.cpp

request_queue.o: request_queue.h request_queue.cpp
	$(CC) -c request_queue.cpp

request.o: request.h request.cpp
	$(CC) -c request.cpp

response.o: response.h response.cpp
	$(CC) -c response.cpp