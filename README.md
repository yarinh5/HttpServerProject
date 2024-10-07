# HTTP Server with Multi-Threading

This project is a basic HTTP server implemented in C++ that supports multi-threading using a Thread Pool to handle multiple connections concurrently. It can serve static files in response to GET requests.

## Features
- **Multi-threading**: Efficiently handles multiple client connections using a custom ThreadPool.
- **GET request support**: Serves static files such as HTML, CSS, JavaScript, etc.
- **Dynamic content serving**: Determines content type dynamically based on the file extension.
- **ThreadPool management**: Distributes incoming connections across threads for optimal performance.

## How to Build and Run

### Prerequisites
- **C++ Compiler**: Ensure you have a modern C++ compiler that supports C++11 or higher (such as GCC, Clang, or MSVC).
- **Boost Library** (optional for certain functionalities): Install Boost if required for WebSocket support or other advanced features.

### Build Instructions

1. Clone the repository:
   ```bash
   git clone https://github.com/USERNAME/HttpServerProject.git
   cd HttpServerProject

   Compile the code:

Using GCC/Clang:

Copy code
g++ -std=c++11 -pthread -o HttpServer main.cpp server.cpp ThreadPool.cpp
Using MSVC:

```bash
Copy code
cl /EHsc /std:c++11 main.cpp server.cpp ThreadPool.cpp
Run the server:

bash
Copy code
./HttpServer
Open your browser and visit http://localhost:8080 to see the server in action.

Project Structure
main.cpp: Entry point of the application, initializes and starts the server.
server.h/server.cpp: Contains the implementation of the HTTP server, including handling connections, requests, and serving static files.
ThreadPool.h/ThreadPool.cpp: A custom thread pool implementation to manage concurrent connections efficiently.
Example Usage
Start the server and visit the following URLs:

http://localhost:8080/: Serves the index.html file from the static folder.
http://localhost:8080/file.html: Serves file.html if available in the static folder.
Handling large numbers of concurrent connections using multi-threading for optimal performance.

Future Enhancements
POST request support: Extend the server to handle POST requests and process JSON data.
SSL/HTTPS support: Add support for SSL using OpenSSL for secure connections.
Logging: Implement logging to track requests and server activity.
REST API: Add support for a REST API to handle more complex requests.

