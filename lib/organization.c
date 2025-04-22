#include "organization.h"

organization* new_organization(char* nm, int taxID, char* mail, char* addr, char* actDescript, char* phone, challenge_list* chall_list, char* pass) {
    struct organization* org = (organization*)malloc(sizeof(organization));
    org->name = STRING(nm, 64);
    org->taxIdentificationNumber = taxID;
    org->email = STRING(mail, 64);
    org->address = STRING(addr, 256);
    org->activityDescription = STRING(actDescript, 256);
    org->phoneNumber = STRING(phone, 12);
    org->challenge_list = chall_list;
    org->password = STRING(pass, 64);

    return org;
}

int add_organization() { return 1; }
int remove_organization() { return 1; }

int get_all_organizations() { return 1; }
int get_accepted_organizations() { return 1; }
int get_pending_organizations() { return 1; }
int get_rejected_organizations() { return 1; }