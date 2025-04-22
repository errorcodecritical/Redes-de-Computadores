#ifndef ORGANIZATION_API_H
#define ORGANIZATION_API_H

#include "structs.h"

int add_organization();
int remove_organization();

int get_all_organizations();
int get_accepted_organizations();
int get_pending_organizations();
int get_rejected_organizations();

int save_organization_data();
int load_organization_data();

#endif