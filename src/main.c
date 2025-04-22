#include <stdio.h>

#include "server.h"

int main() {
    int fd, client;
    struct sockaddr_in addr, client_addr;
    int client_addr_size;
    bzero((void*)&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(SERVER_PORT);

    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        error("in function socket");

    if (bind(fd, (struct sockaddr*)&addr, sizeof(addr)) < 0)
        error("in function bind");

    if (listen(fd, 5) < 0)
        error("in function listen");

    printf("Banana");

    while (1) {
        client_addr_size = sizeof(client_addr);
        client = accept(fd, (struct sockaddr*)&client_addr, (socklen_t*)&client_addr_size);

        if (client > 0) {
            if (fork() == 0) {
                close(fd);
                process_client(client);
                exit(0);
            }
            close(client);
        }
    }
    return 0;
}
