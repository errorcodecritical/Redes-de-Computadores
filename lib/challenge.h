#ifndef CHALLENGE_API_H
#define CHALLENGE_API_H

#include "structs.h"

#define BUF_SIZE 1024

int add_challenge(char* name, char* description, char* type, int hours, int organization_id, bool status);
int update_challenge(challenge* challenges);
int remove_challenge(int id);

int get_all_challenges(challenge** challenges, char* condition);

#endif