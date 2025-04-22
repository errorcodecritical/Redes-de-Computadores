#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <stdbool.h> 
#include <unistd.h>
#define SERVER_PORT 9000
#define BUF_SIZE 1024

////////////////////////////////////////////////////////////////////////////////////////////////////////

//Ainda n estão definidas mas aparecem no menu em baixo

////////////////////////////////////////////////////////////////////////////////////////////////////////

int listEngineers(){ return 1; }
int pendingEngineers(){ return 1; }
int removeEngineers(){ return 1; }

int listOrganizations(){ return 1; }
int pendingOrganizations(){ return 1; }
int removeOrganizations(){ return 1; }

int listChallenges(){ return 1; }
int pendingChallenges(){ return 1; }
int removeChallenges(){ return 1; }

int closeFunction(){ return 1; }

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

// Struct pre declaration

struct str;
struct areasOfExpertise;
struct engineeringSpecialty;
struct engineer;
struct challenge;
struct organization;

// Vector declaration

typedef struct str{

    int size;
    char* text;
    
}str;



typedef struct areasOfExpertise{
    
    str* data;
    struct areasOfExpertise* next;

}areasOfExpertise;



typedef struct aoE_list{

    areasOfExpertise* top;
    areasOfExpertise* bottom;

}aoE_list;



typedef struct engineeringSpecialty{

    str* data;
    struct engineeringSpecialty* next;

}engineeringSpecialty;

typedef struct engSpec_List{

    engineeringSpecialty* top;
    engineeringSpecialty* bottom;

}engSpec_List;

typedef struct challenge_list{

    challenge* top;
    challenge* bottom;

}challenge_list;


// Engineer struct declaration

typedef struct engineer{

    str* name;
    int number;
    engSpec_List* engineeringSpecialty_list;
    str* employmentInstitution;
    bool studentStatus;
    aoE_list* areasOfExpertise_list;
    str* email;
    char phoneNumber[9];
    str* password;

}engineer;


// End of Engineer struct declaration



// Beginning of organization declaration with dependencies

// Beggining of chellenge declaration

typedef struct challenge{

    str* name;
    str* description;
    str* engineerType;
    int hours;
    struct challenge* next;

}challenge;


// Ending of chellenge declaration


// Beggining of organization struct declaration

typedef struct organization{

    str* name;
    int taxIdentificationNumber;
    str* email;
    str* address;
    str* activityDescription;
    char phoneNumber[9];
    challenge_list* challenge_list;
    str* password;

}organization;


typedef struct sc{
    struct str* string;
    int size;
}sc;

typedef struct bc{
    struct sc* small_class;
    struct str* bctext;
}bc;


str* create_String(char data[]){

    str* st = (str*)malloc(sizeof(str));
    int count = 0;
    while(*(data+count) != '\0'){
        count++;
    }
    count++;
    st -> size = count;

    st -> text = (char*)malloc(count); 

    for(int i = 0; i < count; i++){
        *((st -> text) + i) = data[i]; 
        printf("%c", *((st -> text) + i));
        if(*((st -> text) + i) == '\0'){
            printf("0");
        }
    }
    printf("\n");
    return st;
}

engineer* new_engineer(char* nm, int numb, engineeringSpecialty* engSpec_list, char* employInst,
                          bool studStat, aoE_list* areasOfExpertise_list, char* email, char* phone, char* pass){

    struct engineer* eng = (engineer*)malloc(sizeof(engineer));
    eng->name = create_String(nm);
    eng->number = numb;
    eng->engineeringSpecialty_list = engSpec_list;
    eng->employmentInstitution = create_String(employInst);
    eng->studentStatus = studStat;
    eng->areasOfExpertise_list = areasOfExpertise_list;
    eng->email = create_String(email);
    for(int i = 0; i<9; i++){
        *(eng->phoneNumber+i) = *(phone);
    }
    eng->password = create_String(pass);

    return eng;

}

organization* new_organization(char* nm, int taxID, char* mail, char* addr, char* actDescript, char* phone, challenge* chall_list, char* pass){
    struct organization* org = (organization*)malloc(sizeof(organization));
    org->name = create_String(nm);
    org->taxIdentificationNumber = create_String(taxID);
    org->email = create_String(mail);
    org->address = create_string(addr);
    org->activityDescription = create_String(actDescript);
    for(int i = 0; i<9; i++){
        *(org->phoneNumber + i) = *(phone + i);
    }
    org->challenge_list = chall_list;
    org->password = create_String(pass);

    return org;
}

challenge* new_challenge(char* nm, char* descript, char* engType, int h){

    struct challenge* chall = (challenge*)malloc(sizeof(challenge));
    chall->name = create_String(nm);
    chall->description = create_String(descript);
    chall->engineerType = create_String(engType);
    chall->hours = h;

    return chall;

}

areasOfExpertise* new_areaOfExpertize(char* data){
    
    struct areasOfExpertise* aoE = (areasOfExpertise*)malloc(sizeof(areasOfExpertise));
    aoE->next = NULL;
    aoE->data = create_String(data);

    return aoE;

}

engineeringSpecialty* new_engineeringSpecialty(char* data){

    struct engineeringSpecialty* eS = (engineeringSpecialty*)malloc(sizeof(engineeringSpecialty));
    eS->next = NULL;
    eS->data = create_String(data);

    return eS;

}

aoE_list* new_aoE_List(){

    struct aoE_list* list = ((aoE_list*)malloc(sizeof(aoE_list)));
    list -> top = NULL;
    list -> bottom = NULL;

    return list;

}

void add_aoE(areasOfExpertise* aoE, aoE_list* list){

    if(list->top == NULL){
        list->top = aoE;
        list->bottom = aoE;
    }
    else{
        list->bottom->next = aoE;
        list->bottom = aoE;
    }

}

engSpec_List* new_engSpec_list(){

    struct engSpec_List* list = ((engSpec_List*)malloc(sizeof(engSpec_List)));
    list -> top = NULL;
    list -> bottom = NULL;

    return list;

}

void add_engSpec(engineeringSpecialty* engSpec, engSpec_List* list){

    if(list->top == NULL){
        list->top = engSpec;
        list->bottom = engSpec;
    }
    else{
        list->bottom->next = engSpec;
        list->bottom = engSpec;
    }

}

challenge_list* new_challenge_list(){

    struct challenge_list* list = ((challenge_list*)malloc(sizeof(challenge_list)));
    list -> top = NULL;
    list -> bottom = NULL;

    return list;

}

void add_challenge(challenge* chall, challenge_list* list){

    if(list->top == NULL){
        list->top = chall;
        list->bottom = chall;
    }
    else{
        list->bottom->next = chall;
        list->bottom = chall;
    }

}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void send_admin_menu(int client_fd) {

    int nread;
    char buffer[BUF_SIZE];
    int state = 0;

    while(1){
        printf("%d", state);

        switch (state){

            case 0:

                char* menu0 = "\nWelcome Admin! Please select an option:\n"
                "1. Manage engineers\n"
                "2. Manage organizations\n"
                "3. Manage challenges\n"
                "4. Logout\n"
                "Enter your option (1-4): ";
                char* choice_error_prompt0 = "The choice you entered is not valid, please enter a valid option (1-4): ";

                    
                    write(client_fd, menu0, strlen(menu0));
                    while(1){
                        nread = read(client_fd, buffer, BUF_SIZE-1);
                        buffer[nread-2] = '\0';
                        if(strcmp(buffer, "1") == 0 ||strcmp(buffer, "2") == 0 ||strcmp(buffer, "3") == 0 ||strcmp(buffer, "4") == 0){
                            state = atoi(buffer);
                            printf("%d", state);
                            break;
                        }
                        else
                            write(client_fd, choice_error_prompt0, strlen(choice_error_prompt0));
                            fflush(stdout);
                }
            break;

            case 1:

                char* menu1 = "\nYou've chosen option 1. Manage engineers. Please select an option\n"
                                "1. List engineers\n"
                                "2. Show pending engineers\n"
                                "3. Remove engineers\n"
                                "4. Back\n"
                                "5. Logout\n"
                                "Enter your option (1-5): ";
                char* choice_error_prompt1 = "The choice you entered is not valid, please enter a valid option (1-5): ";

                    write(client_fd, menu1, strlen(menu1));
                    while(1){
                        nread = read(client_fd, buffer, BUF_SIZE-1);
                        buffer[nread-2] = '\0';
                        if(strcmp(buffer, "1") == 0 ||strcmp(buffer, "2") == 0 ||strcmp(buffer, "3") == 0 ||strcmp(buffer, "4") == 0 ||strcmp(buffer, "5")){
                            fflush(stdout);
                            int choice = atoi(buffer);
                            switch (choice){
                                case 1:
                                    listEngineers();
                                    state = 1;
                                    break;
                                case 2:
                                    pendingEngineers();
                                    state = 0;
                                    break;
                                case 3:
                                    removeEngineers();
                                    state = 0;
                                    break;
                                case 4:
                                    state = 0;
                                    break;
                                case 5:
                                    close(client_fd);
                                    return;
                            }
                        }
                        else
                            write(client_fd, choice_error_prompt1, strlen(choice_error_prompt1));
                }
            break;

            case 2:

                char* menu2 = "\nYou've chosen option 1. Manage organizations. Please select an option\n"
                                "1. List organizations\n"
                                "2. Show pending organizations\n"
                                "3. Remove organizations\n"
                                "4. Back\n"
                                "5. Logout\n"
                                "Enter your option (1-5): ";
                char* choice_error_prompt2 = "The choice you entered is not valid, please enter a valid option (1-5): ";

                write(client_fd, menu2, strlen(menu2));
                while(1){
                    nread = read(client_fd, buffer, BUF_SIZE-1);
                    buffer[nread-2] = '\0';
                    if(strcmp(buffer, "1") == 0 ||strcmp(buffer, "2") == 0 ||strcmp(buffer, "3") == 0 ||strcmp(buffer, "4") == 0 ||strcmp(buffer, "5")){
                        fflush(stdout);
                        int choice = atoi(buffer);
                        switch (choice){
                            case 1:
                                listOrganizations();
                                state = 0;
                                break;
                            case 2:
                                pendingOrganizations();
                                state = 0;
                                break;
                            case 3:
                                removeOrganizations();
                                state = 0;
                                break;
                            case 4:
                                state = 0;
                                break;
                            case 5:
                                close(client_fd);
                                return;
                        }
                    }
                    else
                        write(client_fd, choice_error_prompt2, strlen(choice_error_prompt2));
                }
            break;

            case 3:

                char* menu3 = "\nYou've chosen option 1. Manage challenges. Please select an option\n"
                                "1. List challenges\n"
                                "2. Show pending challenges\n"
                                "3. Remove challenges\n"
                                "4. Back\n"
                                "5. Logout\n"
                                "Enter your option (1-5): ";
                char* choice_error_prompt3 = "The choice you entered is not valid, please enter a valid option (1-5): ";

                
                write(client_fd, menu3, strlen(menu3));
                while(1){
                    nread = read(client_fd, buffer, BUF_SIZE-1);
                    buffer[nread-2] = '\0';
                    if(strcmp(buffer, "1") == 0 ||strcmp(buffer, "2") == 0 ||strcmp(buffer, "3") == 0 ||strcmp(buffer, "4") == 0 ||strcmp(buffer, "5")){
                        fflush(stdout);
                        int choice = atoi(buffer);
                        switch (choice){
                            case 1:
                                listChallenges();
                                state = 0;
                                break;
                            case 2:
                                pendingChallenges();
                                state = 0;
                                break;
                            case 3:
                                removeChallenges();
                                state = 0;
                                break;
                            case 4:
                                state = 0;
                                break;
                            case 5:
                                close(client_fd);
                                return;
                        }
                    }
                    else
                        write(client_fd, choice_error_prompt3, strlen(choice_error_prompt3));
                    }
            break;

            case 4:
                close(client_fd);
            break;
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
    int nread = read(client_fd, buffer, BUF_SIZE-1);
    buffer[nread-2] = '\0';
 
    // Simulate authentication based on hardcoded credentials (for demo purposes)
    if (strcmp(buffer, "engineer123\0") == 0) {
        write(client_fd, password_prompt, strlen(password_prompt));
        nread = read(client_fd, buffer, BUF_SIZE-1);
        buffer[nread-2] = '\0';
        if (strcmp(buffer, "pass123") == 0) {
            return 0; // Engineer
        }
    } else if (strcmp(buffer, "org456") == 0) {
        write(client_fd, password_prompt, strlen(password_prompt));
        nread = read(client_fd, buffer, BUF_SIZE-1);
        buffer[nread-2] = '\0';
        if (strcmp(buffer, "pass456") == 0) {
            return 1; // Organization
        }
    } else if (strcmp(buffer, "admin789") == 0) {
        write(client_fd, password_prompt, strlen(password_prompt));
        nread = read(client_fd, buffer, BUF_SIZE-1);
        buffer[nread-2] = '\0';
        if (strcmp(buffer, "adminpass") == 0) {
            return 2; // Admin
        }
    } else
       write(client_fd, authentication_error_prompt, strlen(authentication_error_prompt));
    return -1; // Authentication failed
}

