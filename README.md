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

