#include "challenge.h"

challenge* new_challenge(char* nm, char* descript, char* engType, int h) {
    struct challenge* chall = (challenge*)malloc(sizeof(challenge));
    chall->name = STRING(nm, 64);
    chall->description = STRING(descript, 256);
    chall->engineerType = STRING(engType, 64);
    chall->hours = h;

    return chall;
}

challenge_list* new_challenge_list() {
    struct challenge_list* list = ((challenge_list*)malloc(sizeof(challenge_list)));
    list->top = NULL;
    list->bottom = NULL;

    return list;
}

void add_challenge(challenge* chall, challenge_list* list) {
    if (list->top == NULL) {
        list->top = chall;
        list->bottom = chall;
    }
    else {
        list->bottom->next = chall;
        list->bottom = chall;
    }
}

// void printChallenges(int client_fd, organization* org) {
//     challenge* currentChall = org->challenge_list->top;
//     char hours[BUF_SIZE];

//     while(currentChall != NULL){

//         write(client_fd, currentChall->name, strlen(currentChall->name));
//         write(client_fd, currentChall->description, strlen(currentChall->description));
//         write(client_fd, currentChall->engineerType, strlen(currentChall->engineerType));
//         sprintf(hours, "%d", currentChall->hours);
//         write(client_fd, hours, strlen(hours));

//         sprintf(hours, "%d", currentChall->hours);

//         printf("%s, %s, %s, %s\n", currentChall->name, currentChall->description, currentChall->engineerType, hours);

//         currentChall = currentChall->next;
//     }

// }

// void addChallengePrompt(int client_fd, organization * org){

//     char name[BUF_SIZE];
//     char description[BUF_SIZE];
//     char engineerType[BUF_SIZE];
//     char hours[BUF_SIZE];
//     int nread;
    
//     char* challenge_prompt = "You're now registering a new challenge please insert:\n"
//                              "Challenge name: ";

//     write(client_fd, challenge_prompt, strlen(challenge_prompt));
//     nread = read(client_fd, name, BUF_SIZE-1);
//     name[nread-2] = '\0';

//     char* description_prompt = "\nDescription: ";
//     write(client_fd, description_prompt, strlen(description_prompt));
//     nread = read(client_fd, description, BUF_SIZE-1);
//     description[nread-2] = '\0';

//     char* engineerType_prompt = "\nengineerType: ";
//     write(client_fd, engineerType_prompt, strlen(engineerType_prompt));
//     nread = read(client_fd, engineerType, BUF_SIZE-1);
//     engineerType[nread-2] = '\0';

//     char* hours_prompt = "\nhours: ";
//     write(client_fd, hours_prompt, strlen(hours_prompt));
//     nread = read(client_fd, hours, BUF_SIZE-1);
//     hours[nread-2] = '\0';
    
//     int h = atoi(hours);

//     challenge* chall = new_challenge(name, description, engineerType, h);

//     add_challenge(org->challenge_list, chall);

// }


int remove_challenge() { return 1; }
int get_all_challenges() { return 1; }
int get_accepted_challenges() { return 1; }
int get_pending_challenges() { return 1; }
int get_rejected_challenges() { return 1; }
