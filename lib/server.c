#include "server.h"

void process_client(int client_fd) {
    int user_role;
    char buffer[BUF_SIZE];
    int nread;

    // Authenticate user and get their role (0: Engineer, 1: Organization, 2: Admin)
    user_role = authenticate_user(client_fd);

    // Based on the user role, send appropriate menu
    if (user_role == 0) {
        send_engineer_menu(client_fd);
    }
    else if (user_role == 1) {
        send_organization_menu(client_fd);
    }
    else if (user_role == 2) {
        send_admin_menu(client_fd);
    }
    else {
        write(client_fd, "Authentication failed. Closing connection.", 41);
        close(client_fd);
        return;
    }

}
