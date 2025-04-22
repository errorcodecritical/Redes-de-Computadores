#include "challenge.h"

challenge* new_challenge(char* nm, char* descript, char* engType, int h) {
    struct challenge* chall = (challenge*)malloc(sizeof(challenge));
    chall->name = create_String(nm);
    chall->description = create_String(descript);
    chall->engineerType = create_String(engType);
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

int remove_challenge() { return 1; }
int get_all_challenges() { return 1; }
int get_accepted_challenges() { return 1; }
int get_pending_challenges() { return 1; }
int get_rejected_challenges() { return 1; }
