#ifndef ENGINEERS_API_H
#define ENGINEERS_API_H

#include "structs.h"

int add_engineer();
int remove_engineer();

int get_all_engineers();
int get_accepted_engineers();
int get_pending_engineers();
int get_rejected_engineers();

int save_engineer_data();
int load_engineer_data();

#endif