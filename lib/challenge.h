#ifndef CHALLENGE_API_H
#define CHALLENGE_API_H

#include "structs.h"

#define BUF_SIZE 1024

int add_engineer();
int remove_engineer();

int get_all_engineers();
int get_accepted_engineers();
int get_pending_engineers();
int get_rejected_engineers();

int save_challenge_data();
int load_challenge_data();

#endif