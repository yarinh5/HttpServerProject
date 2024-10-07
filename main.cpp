#include "server.h"

int main() {
    HttpServer server(8080, 4); // Use Thread Pool with 4 threads
    server.start();
    return 0;
}
