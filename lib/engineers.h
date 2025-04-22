#ifndef ENGINEERS_API_H
#define ENGINEERS_API_H

#include "structs.h"

int add_engineer(char* name, int number, char* specialty, char* institution, bool student, char* areas_of_expertise, char* email, char* phone, char* password, int status);
int remove_engineer(char* email);

int get_all_engineers(engineer** engineers);
int get_accepted_engineers();
int get_pending_engineers();
int get_rejected_engineers();

int save_engineer_data();
int load_engineer_data();

#endif