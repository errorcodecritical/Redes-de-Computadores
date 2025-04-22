#include "server.h"

int closeFunction() { return -1; }

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

void send_engineer_menu(int client_fd) {
    int state = 0;
    char* choice_error_prompt = "The choice you entered is not valid, please enter a valid option (1-4): ";
    int nread;
    char buffer[BUF_SIZE];
    while (1) {
        switch (state) {
        case 0:
            while (1) {
                char* menu = "\nWelcome Engineer! Please select an option:\n"
                    "1. View available challenges\n"
                    "2. Apply for a challenge\n"
                    "3. Update profile\n"
                    "4. Logout\n"
                    "Enter your option (1-4): ";
                write(client_fd, menu, strlen(menu));
                nread = read(client_fd, buffer, BUF_SIZE - 1);
                buffer[nread - 2] = '\0';
                if (strcmp(buffer, "1") == 0 || strcmp(buffer, "2") == 0 || strcmp(buffer, "3") == 0 || strcmp(buffer, "4") == 0) {
                    state = atoi(buffer);
                }
                else write(client_fd, choice_error_prompt, strlen(choice_error_prompt));
                state = 1;
                break;
            }
            break;
        }
    }
}

void send_organization_menu(int client_fd) {
    char buffer[BUF_SIZE];
    int nread;
    char* choice_error_prompt = "The choice you entered is not valid, please enter a valid option (1-4): ";
    char* menu = "\nWelcome Non-Profit Organization! Please select an option:\n"
        "1. Add a new challenge\n"
        "2. List all challenges\n"
        "3. View applications\n"
        "4. Logout\n"
        "Enter your option (1-4): ";
    write(client_fd, menu, strlen(menu));
    while (1) {
        nread = read(client_fd, buffer, BUF_SIZE - 1);
        buffer[nread - 2] = '\0';
        if (strcmp(buffer, "1") == 0 || strcmp(buffer, "2") == 0 || strcmp(buffer, "3") == 0 || strcmp(buffer, "4") == 0) {

            printf("User choice: %s\n", buffer);
            fflush(stdout);
            close(client_fd);
            return;

        }
        else
            write(client_fd, choice_error_prompt, strlen(choice_error_prompt));
    }
}

void send_admin_menu(int client_fd) {
    int nread;
    char buffer[BUF_SIZE];
    int state = 0;
    switch (state) {

    case 0:
        while (state == 0) {
            char* menu0 = "\nWelcome Admin! Please select an option:\n"
                "1. Manage engineers\n"
                "2. Manage organizations\n"
                "3. Manage challenges\n"
                "4. Logout\n"
                "Enter your option (1-4): ";
            char* choice_error_prompt1 = "The choice you entered is not valid, please enter a valid option (1-4): ";
            write(client_fd, menu0, strlen(menu0));
            while (1) {

                nread = read(client_fd, buffer, BUF_SIZE - 1);
                buffer[nread - 2] = '\0';
                if (strcmp(buffer, "1") == 0 || strcmp(buffer, "2") == 0 || strcmp(buffer, "3") == 0 || strcmp(buffer, "4") == 0) {
                    fflush(stdout);
                    close(client_fd);
                    state = atoi(buffer);
                    break;
                }
                else
                    write(client_fd, choice_error_prompt1, strlen(choice_error_prompt1));
            }
        }
        break;

    case 1:
        char* menu2 = "\nYou've chosen option 1. Manage engineers. Please select an option\n"
            "1. List engineers\n"
            "2. Show pending engineers\n"
            "3. Remove engineers\n"
            "4. Back"
            "5. Logout\n"
            "Enter your option (1-5): ";
        char* choice_error_prompt2 = "The choice you entered is not valid, please enter a valid option (1-5): ";

        while (state == 1) {
            write(client_fd, menu2, strlen(menu2));
            while (1) {
                nread = read(client_fd, buffer, BUF_SIZE - 1);
                buffer[nread - 2] = '\0';
                if (strcmp(buffer, "1") == 0 || strcmp(buffer, "2") == 0 || strcmp(buffer, "3") == 0 || strcmp(buffer, "4") == 0 || strcmp(buffer, "5")) {
                    fflush(stdout);
                    int choice = atoi(buffer);
                    switch (choice) {
                    case 1:
                        // listEngineers();
                        break;
                    case 2:
                        // pendingEngineers();
                        break;
                    case 3:
                        // removeEngineers();
                        break;
                    case 4:
                        state = 1;
                        break;
                    case 5:
                        closeFunction();
                        break;
                    }
                    break;
                }
                else
                    write(client_fd, choice_error_prompt2, strlen(choice_error_prompt2));
            }
        }
    case 2:
        char* menu3 = "\nYou've chosen option 1. Manage engineers. Please select an option\n"
            "1. List organizations\n"
            "2. Show pending organizations\n"
            "3. Remove organizations\n"
            "4. Back"
            "5. Logout\n"
            "Enter your option (1-5): ";
        char* choice_error_prompt3 = "The choice you entered is not valid, please enter a valid option (1-5): ";

        while (state == 2) {
            write(client_fd, menu3, strlen(menu3));
            while (1) {
                nread = read(client_fd, buffer, BUF_SIZE - 1);
                buffer[nread - 2] = '\0';
                if (strcmp(buffer, "1") == 0 || strcmp(buffer, "2") == 0 || strcmp(buffer, "3") == 0 || strcmp(buffer, "4") == 0 || strcmp(buffer, "5")) {
                    fflush(stdout);
                    int choice = atoi(buffer);
                    switch (choice) {
                    case 1:
                        //listOrganizations();
                        break;
                    case 2:
                        //pendingOrganizations();
                        break;
                    case 3:
                        //removeOrganizations();
                        break;
                    case 4:
                        state = 1;
                        break;
                    case 5:
                        closeFunction();
                        break;
                    }
                    break;
                }
                else
                    write(client_fd, choice_error_prompt2, strlen(choice_error_prompt2));
            }
        }

    }
}

int authenticate_user(int client_fd) {

    char* login_prompt = "Welcome to engineers without borders!\n"
        "Enter your login ID: ";
    char* password_prompt = "Enter your password: ";
    char* authentication_error_prompt = "User not registered\n";
    write(client_fd, login_prompt, strlen(login_prompt));

    char buffer[BUF_SIZE];
    int nread = read(client_fd, buffer, BUF_SIZE - 1);
    buffer[nread - 2] = '\0';

    // Simulate authentication based on hardcoded credentials (for demo purposes)
    if (strcmp(buffer, "engineer123\0") == 0) {
        write(client_fd, password_prompt, strlen(password_prompt));
        nread = read(client_fd, buffer, BUF_SIZE - 1);
        buffer[nread - 2] = '\0';
        if (strcmp(buffer, "pass123") == 0) {
            return 0; // Engineer
        }
    }
    else if (strcmp(buffer, "org456") == 0) {
        write(client_fd, password_prompt, strlen(password_prompt));
        nread = read(client_fd, buffer, BUF_SIZE - 1);
        buffer[nread - 2] = '\0';
        if (strcmp(buffer, "pass456") == 0) {
            return 1; // Organization
        }
    }
    else if (strcmp(buffer, "admin789") == 0) {
        write(client_fd, password_prompt, strlen(password_prompt));
        nread = read(client_fd, buffer, BUF_SIZE - 1);
        buffer[nread - 2] = '\0';
        if (strcmp(buffer, "adminpass") == 0) {
            return 2; // Admin
        }
    }
    else
        write(client_fd, authentication_error_prompt, strlen(authentication_error_prompt));
    return -1; // Authentication failed
}
