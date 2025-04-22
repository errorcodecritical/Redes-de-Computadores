#ifndef CHALLENGE_API_H
#define CHALLENGE_API_H

#include "structs.h"

#define BUF_SIZE 1024

int add_challenge();
int remove_challenge();

int get_all_challenges();
int get_accepted_challenges();
int get_pending_challenges();
int get_rejected_challenges();

int save_challenge_data();
int load_challenge_data();

#endif