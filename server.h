#ifndef SERVER_H
#define SERVER_H

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <netinet/in.h>
#endif

#include "ThreadPool.h"
#include <string>

class HttpServer {
public:
    HttpServer(int port, size_t threadCount);
    void start();
    void stop();

private:
    SOCKET serverSocket;
    struct sockaddr_in serverAddr;
    ThreadPool pool; // ThreadPool instance

    void handleRequest(SOCKET clientSocket);
    std::string getFileContent(const std::string& filePath);
    std::string parseRequest(const std::string& request, const std::string& requestType);
};

#endif
