#ifndef ORGANIZATION_API_H
#define ORGANIZATION_API_H

#include "structs.h"

int add_organization(char* name, int tax_id, char* email, char* address, char* description, char* phone, char* password, int status);
int update_organization(organization* organizations);
int remove_organization(int id);

int get_all_organizations(organization** organizations, char* condition);

#endif