#include "server.h"

void manageOrganizations(int client_fd, organization* organizations, int size);
void manageEngineers(int client_fd, engineer* engineers, int size);
void manageChallenges(int client_fd, challenge* challenge_list, int size);

int closeFunction() { return -1; }

void process_client(int client_fd) {
    // Authenticate user and get their role (0: Engineer, 1: Organization, 2: Admin)
    int nread;
    char buffer[BUF_SIZE];
    int state = 0;

    do{
        char* menu0 = "========================================================"
                    "       \nWelcome to engineers without borders!\n"
                    "========================================================"
                        "\nPlease select an option:\n"
        "1. Login\n"
        "2. Organization Registration\n"
        "3. Engineer Registration\n"
        "4. Exit\n"
        "Enter your option (1-4): ";
        //char* choice_error_prompt0 = "The choice you entered is not valid, please enter a valid option (1-3): ";
        
        
        writeStr(client_fd, menu0);
        /*while(1){
            nread = read(client_fd, buffer, BUF_SIZE-1);
            buffer[nread-2] = '\0';
            if(strcmp(buffer, "1") == 0 ||strcmp(buffer, "2") == 0 ||strcmp(buffer, "3") == 0){
                state = atoi(buffer);
                printf("%d", state);
                break;
            }
            else{
                write(client_fd, choice_error_prompt0, strlen(choice_error_prompt0));
                fflush(stdout);
            }
        }*/
        state = getSelectedOptionInRange(client_fd, 1, 4);

        switch (state)
        {
        case 1:
            int user_role = authenticate_user(client_fd);

            // Based on the user role, send appropriate menu
            switch (user_role) {
            case 0:
                send_engineer_menu(client_fd);
                break;
            case 1:
                send_organization_menu(client_fd);
                break;
            case 2:
                send_admin_menu(client_fd);
                break;
            default:
                writeStr(client_fd, "Authentication failed. Closing connection.");
                close(client_fd);
                break;
            }
            break;
        case 2:
            system("cls");  
            writeStr(client_fd, "==================================================================\n");
            writeStr(client_fd, "                      MENU - NON-PROFIT REGIST \n");
            writeStr(client_fd, "         PLEASE ENTER THE DATA OF YOUR NON-PROFIT ORGANIZATION \n");
            writeStr(client_fd, "==================================================================\n\n");	
            writeStr(client_fd, " > Non-Profit Organization Registration:\n");
            organizationRegister(client_fd);
            break;
        case 3:
            system("cls");  
            writeStr(client_fd, "==================================================================\n");
            writeStr(client_fd, "                        MENU - VOLUNTEER REGIST \n");
            writeStr(client_fd, "           PLEASE ENTER YOUR DATA AND CREDENTIALS \n");
            writeStr(client_fd, "==================================================================\n\n");
            writeStr(client_fd, " > Volunteer Engineer Registration:\n");
            engineerRegister(client_fd);
            break;
        
        default:
            break;
        }
    } while (state!=4);
    

    
}

void send_engineer_menu(int client_fd) {
    int state = 0;
    //char* choice_error_prompt = "The choice you entered is not valid, please enter a valid option (1-4): ";
    int nread;
    char buffer[BUF_SIZE];
        
    char* menu = "========================================================"
                "                 \nWelcome Engineer!\n"
                "========================================================"
    "\nPlease select an option:\n"
        "1. View available challenges\n"
        "2. Apply for a challenge\n"
        "3. Update profile\n"
        "4. Logout\n"
        "Enter your option (1-4): ";
    write(client_fd, menu, strlen(menu));
    state = getSelectedOptionInRange(client_fd, 1, 4);
    /*
    while (1) {
        nread = read(client_fd, buffer, BUF_SIZE - 1);
        buffer[nread - 2] = '\0';
        if (strcmp(buffer, "1") == 0 || strcmp(buffer, "2") == 0 || strcmp(buffer, "3") == 0 || strcmp(buffer, "4") == 0) {
            state = atoi(buffer);
            break;
        }
        else
            write(client_fd, choice_error_prompt, strlen(choice_error_prompt));
        
    }*/
    switch (state) {
        case 1:
            write(client_fd, "not yet implemented", strlen("not yet implemented"));
            break;
        case 2:
            write(client_fd, "not yet implemented", strlen("not yet implemented"));
            break;
        case 3:
            write(client_fd, "not yet implemented", strlen("not yet implemented"));
            break;
        default:
            write(client_fd, "not yet implemented", strlen("not yet implemented"));
            break;
    }
        
}

void send_organization_menu(int client_fd) {
    char buffer[BUF_SIZE];
    int nread;
    int state;
    //char* choice_error_prompt = "The choice you entered is not valid, please enter a valid option (1-4): ";
    char* menu = "========================================================"
                "        \nWelcome Non-Profit Organization!\n"
                "========================================================"
                "\nPlease select an option:\n"
        "1. Add a new challenge\n"
        "2. List all challenges\n"
        "3. Update challenges\n"
        "4. View applications\n"
        "5. Logout\n"
        "Enter your option (1-5): ";
    writeStr(client_fd, menu);
    /*while (1) {
        nread = read(client_fd, buffer, BUF_SIZE - 1);
        buffer[nread - 2] = '\0';
        if (strcmp(buffer, "1") == 0 || strcmp(buffer, "2") == 0 || strcmp(buffer, "3") == 0 || strcmp(buffer, "4") == 0 || strcmp(buffer, "5") == 0) {
            state = atoi(buffer);
            break;
        }
        else     
            write(client_fd, choice_error_prompt, strlen(choice_error_prompt));
    }*/
    state = getSelectedOptionInRange(client_fd, 1, 5);
    switch (state) {
        case 1:
            writeStr(client_fd, "not yet implemented");
            break;
        case 2:
            writeStr(client_fd, "not yet implemented");
            break;
        case 3:
            writeStr(client_fd, "not yet implemented");
            break;
        case 4:
            writeStr(client_fd, "not yet implemented");
            break;
        default:
            writeStr(client_fd, "not yet implemented");
            break;
    }
}

void send_admin_menu(int client_fd) {

    int nread;
    char buffer[BUF_SIZE];
    int state = 0;


    char* menu0 = "========================================================"
                "                \nWelcome Admin!\n"
                "========================================================"
                    "\nPlease select an option:\n"
    "1. Manage engineers\n"
    "2. Manage organizations\n"
    "3. Manage challenges\n"
    "4. Logout\n"
    "Enter your option (1-4): ";
    //char* choice_error_prompt0 = "The choice you entered is not valid, please enter a valid option (1-4): ";
    
    
    write(client_fd, menu0, strlen(menu0));
    /*
    while(1){
        nread = read(client_fd, buffer, BUF_SIZE-1);
        buffer[nread-2] = '\0';
        /*if(strcmp(buffer, "1") == 0 ||strcmp(buffer, "2") == 0 ||strcmp(buffer, "3") == 0 ||strcmp(buffer, "4") == 0){
            state = atoi(buffer);
            printf("%d", state);
            break;
        }
        else{
            write(client_fd, choice_error_prompt0, strlen(choice_error_prompt0));
            fflush(stdout);
        }
    }*/
    state = getSelectedOptionInRange(client_fd, 1, 4);    
    switch (state){
        case 1:

            engineer* e;
            int n = get_all_engineers(&e, "");
            manageEngineers(client_fd, e, n);
            break;

        case 2:
        
            organization* o;
            n = get_all_organizations(&o, "");
            manageOrganizations(client_fd, o, n);
            break;

        case 3:

            challenge* c;
            n = get_all_challenges(&o, "");
            manageChallenges(client_fd, c, n);

            break;
        case 4:
            close(client_fd);
            break;
    }
    
}

int authenticate_user(int client_fd) {

    char* login_prompt = "\nEnter your login ID: ";
    char* password_prompt = "Enter your password: ";
    char* authentication_error_prompt = "User not registered\n";
    writeStr(client_fd, login_prompt);

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


void manageOrganizations(int client_fd, organization* organizations, int size){

    organization* currentOrg = organizations;
    char buffer[1024];
    int nread;
    int choice;
    int count = 0;

    char* option_prompt = "\nPlease select one of the options below\n"
                          "1. Change the status to approved\n"
                          "2. Change the status to pending\n"
                          "3. Change the status to rejected\n"
                          "4. Delete organization"
                          "5. Next organization\n"
                          "6. Previous menu\n"
                          "Your choice(1-6): ";

    char* choice_error_prompt = "The choice you entered is not valid, please enter a valid option (1-5): ";
    

    while(count < size){

        currentOrg = organizations+count;

        writeStr(client_fd, "\nName: ");
        writeStr(client_fd, currentOrg->name);
        writeStr(client_fd, "\nTax Identification Number: ");
        snprintf(buffer, 10, "%d", currentOrg->taxIdentificationNumber);
        writeStr(client_fd, buffer);
        writeStr(client_fd, "\nEmail: ");
        writeStr(client_fd, currentOrg->email);
        writeStr(client_fd, "\nAddress: ");
        writeStr(client_fd, currentOrg->address);
        writeStr(client_fd, "\nActivity Description: ");
        writeStr(client_fd, currentOrg->activityDescription);
        writeStr(client_fd, "\nPhone Number: ");
        writeStr(client_fd, currentOrg->phoneNumber);

        switch (currentOrg->status){
            case 0: writeStr(client_fd, "\n\nStatus: Approved"); break;
            case 1: writeStr(client_fd, "\n\nStatus: Pending"); break;
            case 2: writeStr(client_fd, "\n\nStatus: Rejected"); break;
        }
        
        /*while(1){
            write(client_fd, option_prompt, strlen(option_prompt));
            nread = read(client_fd, buffer, BUF_SIZE-1);
                buffer[nread-2] = '\0';
                if(strcmp(buffer, "1") == 0||strcmp(buffer, "2") == 0||strcmp(buffer, "3") == 0||strcmp(buffer, "4") == 0||strcmp(buffer, "5")||strcmp(buffer, "6")){
                    choice = atoi(buffer);
                    break;
                }
            else write(client_fd, choice_error_prompt, strlen(choice_error_prompt));

        }*/
        choice = getSelectedOptionInRange(client_fd, 1, 6);

        switch(choice){

            case 1: currentOrg->status = 0; break;
            case 2: currentOrg->status = 1; break;
            case 3: currentOrg->status = 2; break;
            case 4: currentOrg->status = -1; break;
            case 6: return;

        }

        count++;

        if (count == size) {
            writeStr(client_fd, "Do you want to see the list from the top (1) or go back to the start menu (2)? Your choice: ");
            nread = read(client_fd, buffer, BUF_SIZE-1);
            buffer[nread-2] = '\0';
            choice = atoi(buffer);
            if(choice == 1){
                count = 0;
            }
            else return;
        }

    }

}



void manageEngineers(int client_fd, engineer* engineers, int size){

    engineer* currentEng = engineers;
    char buffer[1024];
    int nread;
    int choice;
    int count = 0;

    char* option_prompt = "\nPlease select one of the options below\n"
                          "1. Change the status to approved\n"
                          "2. Change the status to pending\n"
                          "3. Change the status to rejected\n"
                          "4. Delete engineer"
                          "5. Next engineer\n"
                          "6. Previous menu\n"
                          "Your choice(1-6): ";

    //char* choice_error_prompt = "The choice you entered is not valid, please enter a valid option (1-6): ";

    while(count < size){

        currentEng = engineers + count;

        writeStr(client_fd, "\nName: ");
        writeStr(client_fd, currentEng->name);
        writeStr(client_fd, "\nOE Number: ");
        sprintf(buffer, "%d", currentEng->number);
        writeStr(client_fd, buffer);
        writeStr(client_fd, "\nEngineering Specialty: ");
        writeStr(client_fd, currentEng->engineeringSpecialty);
        writeStr(client_fd, "\nStudent Status: ");
        if(currentEng->studentStatus){
            writeStr(client_fd, "Studying");
        }
        else writeStr(client_fd, "Not studying");
        writeStr(client_fd, "\nAreas of Expertise: ");
        writeStr(client_fd, currentEng->areasOfExpertise);
        writeStr(client_fd, "\nEmail: ");
        writeStr(client_fd, currentEng->email);
        writeStr(client_fd, "\nPhone Number: ");
        writeStr(client_fd, currentEng->phoneNumber);
        switch (currentEng->status){
            case 0: writeStr(client_fd, "\n\nStatus: Approved"); break;
            case 1: writeStr(client_fd, "\n\nStatus: Pending"); break;
            case 2: writeStr(client_fd, "\n\nStatus: Rejected"); break;
        }
        
        /*while(1){

            write(client_fd, option_prompt, strlen(option_prompt));
            nread = read(client_fd, buffer, BUF_SIZE-1);
                buffer[nread-2] = '\0';
                if(strcmp(buffer, "1") == 0||strcmp(buffer, "2") == 0||strcmp(buffer, "3") == 0||strcmp(buffer, "4") == 0||strcmp(buffer, "5")||strcmp(buffer, "6")){
                    choice = atoi(buffer);
                    break;
                }
            else write(client_fd, choice_error_prompt, strlen(choice_error_prompt));
            
        }*/

        choice = getSelectedOptionInRange(client_fd, 1, 6);

        switch(choice){

            case 1: currentEng->status = 0; break;
            case 2: currentEng->status = 1; break;
            case 3: currentEng->status = 2; break;
            case 4: currentEng->status = -1; break;
            case 6: return;

        }

        count++;

        if(count == size){
            writeStr(client_fd, "Do you want to see the list from the top (1) or go back to the start menu (2)? Your choice: ");
            nread = read(client_fd, buffer, BUF_SIZE-1);
            buffer[nread-2] = '\0';
            choice = atoi(buffer);
            if(choice == 1){
                count = 0;
            }
            else return;
        }

    }

}

void manageChallenges(int client_fd, challenge* challenge_list, int size){
    
    challenge* currentChall = challenge_list;
    char buffer[1024];
    int nread;
    int choice;
    int count = 0;

    char* option_prompt = "\nPlease select one of the options below\n"
                          "1. Change the status to approved\n"
                          "2. Change the status to pending\n"
                          "3. Change the status to rejected\n"
                          "4. Next challenge\n"
                          "5. Previous menu\n"
                          "Your choice(1-5): ";

    //char* choice_error_prompt = "The choice you entered is not valid, please enter a valid option (1-5): ";
    

    while(count < size){

        currentChall = challenge_list + count;

        writeStr(client_fd, "\nName: ");
        writeStr(client_fd, currentChall->name);
        writeStr(client_fd, "\nDescription: ");
        writeStr(client_fd, currentChall->description);
        writeStr(client_fd, "\nEngineer Type: ");
        writeStr(client_fd, currentChall->engineerType);
        writeStr(client_fd, "\nHours: ");
        sprintf(buffer, "%d", currentChall->hours);
        writeStr(client_fd, buffer);
        writeStr(client_fd, "\nOrganization ID: ");
        sprintf(buffer, "%d", currentChall->organizationId);
        writeStr(client_fd, buffer);
        switch (currentChall->status){
            case 0: writeStr(client_fd, "\n\nStatus: Approved"); break;
            case 1: writeStr(client_fd, "\n\nStatus: Pending"); break;
            case 2: writeStr(client_fd, "\n\nStatus: Rejected"); break;
        }

        // for(challenge* currentChall = currentChall->challenge_list; currentChall != NULL; currentChall = currentChall -> next){

        //     write(client_fd, "\nName: ", strlen("\nName: "));
        //     write(client_fd, currentChall->name, currentChall->name);
        //     write(client_fd, "\nDescription: ", strlen("\nDescription "));
        //     write(client_fd, currentChall->description, currentChall->description);
        //     write(client_fd, "\nEngineer Type: ", strlen("\nEngineer Type: "));
        //     write(client_fd, currentChall->engineerType, currentChall->engineerType);
        //     write(client_fd, "\nExpected hours: ", strlen("\nExpected hours: "));
        //     sprintf(buffer, "%d", currentChall->hours);
        //     write(client_fd, buffer, BUF_SIZE-1);

        //     switch (currentChall->status){
        //         case 0: write(client_fd, "\n\nStatus: Approved", strlen("\nStatus: Approved")); break;
        //         case 1: write(client_fd, "\n\nStatus: Pending", strlen("\nStatus: Pending")); break;
        //         case 2: write(client_fd, "\n\nStatus: Rejected", strlen("\nStatus: Rejected")); break;
        //     }
        /*
            while(1){

                write(client_fd, option_prompt, strlen(option_prompt));
                nread = read(client_fd, buffer, BUF_SIZE-1);
                    buffer[nread-2] = '\0';
                    if(strcmp(buffer, "1") == 0||strcmp(buffer, "2") == 0||strcmp(buffer, "3") == 0||strcmp(buffer, "4") == 0||strcmp(buffer, "5")){
                        choice = atoi(buffer);
                        break;
                    }
                    else write(client_fd, choice_error_prompt, strlen(choice_error_prompt)); 
                
            }*/
        choice = getSelectedOptionInRange(client_fd, 1, 5);
        switch(choice){

            case 1: currentChall->status = 0; break;
            case 2: currentChall->status = 1; break;
            case 3: currentChall->status = 2; break;
            case 5: return;

        }


        if(count == size){
            writeStr(client_fd, "Do you want to see the list from the top (1) or go back to the start menu (2)? Your choice: ");
            nread = read(client_fd, buffer, BUF_SIZE-1);
            buffer[nread-2] = '\0';
            choice = atoi(buffer);
            if(choice == 1){
                count = 0;
            }
            else return;
        }

    }
}


int getSelectedOptionInt(int client_fd){
    char buffer[BUF_SIZE];
    size_t nread = read(client_fd, buffer, BUF_SIZE - 1);
    buffer[nread] = 0;

    return atoi(buffer);
}

int getSelectedOptionInRange(int client_fd, int min, int max){
    char errStr[200];
    int read;
    
    sprintf(errStr, "\nThe choice you entered is not valid, please enter a valid option (%d-%d): ", min, max);
    while(true){
        read = getSelectedOptionInt(client_fd);

        if(read >= min && read <= max)
            return read;
        
        writeStr(client_fd, errStr);
    }
}

void writeStr(int client_fd, char* str){
    write(client_fd, str, strlen(str));
}
