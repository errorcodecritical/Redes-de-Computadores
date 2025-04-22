#include "organization.h"

organization* new_organization(char* nm, int taxID, char* mail, char* addr, char* actDescript, char* phone, challenge* chall_list, char* pass) {
    struct organization* org = (organization*)malloc(sizeof(organization));
    org->name = create_String(nm);
    org->taxIdentificationNumber = create_String(taxID);
    org->email = create_String(mail);
    org->address = create_string(addr);
    org->activityDescription = create_String(actDescript);

    for (int i = 0; i < 9; i++) {
        *(org->phoneNumber + i) = *(phone + i);
    }

    org->challenge_list = chall_list;
    org->password = create_String(pass);

    return org;
}

int add_organization() { return 1; }
int remove_organization() { return 1; }

int get_all_organizations() { return 1; }
int get_accepted_organizations() { return 1; }
int get_pending_organizations() { return 1; }
int get_rejected_organizations() { return 1; }