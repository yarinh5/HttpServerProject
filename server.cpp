#include "server.h"
#include <iostream>
#include <fstream>
#include <vector>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#endif

HttpServer::HttpServer(int port, size_t threadCount) : pool(threadCount) {
#ifdef _WIN32
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        std::cerr << "WSAStartup failed: " << result << "\n";
        exit(EXIT_FAILURE);
    }
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
#else
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
#endif

    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Error creating socket\n";
        exit(EXIT_FAILURE);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Error binding to port\n";
        exit(EXIT_FAILURE);
    }

    if (listen(serverSocket, 10) == SOCKET_ERROR) {
        std::cerr << "Error listening\n";
        exit(EXIT_FAILURE);
    }

    std::cout << "HTTP Server started on port " << port << "\n";
}

void HttpServer::start() {
    while (true) {
        SOCKET clientSocket = accept(serverSocket, NULL, NULL);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Error accepting connection\n";
            continue;
        }

        pool.enqueue([this, clientSocket] {
            handleRequest(clientSocket);
            });
    }
}

void HttpServer::stop() {
#ifdef _WIN32
    closesocket(serverSocket);
    WSACleanup();
#else
    close(serverSocket);
#endif
}

void HttpServer::handleRequest(SOCKET clientSocket) {
    std::vector<char> buffer(30000);
    int valread = recv(clientSocket, buffer.data(), buffer.size(), 0);
    if (valread <= 0) {
        std::cerr << "Error reading from socket\n";
        return;
    }

    std::string request(buffer.begin(), buffer.end());

    std::string filePath = parseRequest(request, "GET");
    std::string response = getFileContent(filePath);
    send(clientSocket, response.c_str(), response.size(), 0);

#ifdef _WIN32
    closesocket(clientSocket);
#else
    close(clientSocket);
#endif
}

std::string HttpServer::parseRequest(const std::string& request, const std::string& requestType) {
    size_t startPos = request.find(requestType) + requestType.size() + 1;
    size_t endPos = request.find(" ", startPos);
    std::string filePath = request.substr(startPos, endPos - startPos);
    if (filePath == "/") {
        filePath = "/index.html";
    }
    return "static" + filePath;
}

std::string HttpServer::getFileContent(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        return "HTTP/1.1 404 Not Found\nContent-Type: text/html\n\n<h1>404 Not Found</h1>";
    }

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return "HTTP/1.1 200 OK\nContent-Type: text/html\n\n" + content;
}
