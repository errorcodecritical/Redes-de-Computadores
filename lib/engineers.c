#include "engineers.h"

engineer* new_engineer(char* nm, int numb, char* engineeringSpecialty, char* employInst,
    bool studStat, char* areasOfExpertise, char* email, char* phone, char* pass) {

    struct engineer* eng = (engineer*)malloc(sizeof(engineer));
    eng->name = STRING(nm, 64);
    eng->number = numb;
    eng->engineeringSpecialty = STRING(engineeringSpecialty, 64);
    eng->employmentInstitution = STRING(employInst, 64);
    eng->studentStatus = studStat;
    eng->areasOfExpertise = STRING(areasOfExpertise, 64);
    eng->email = STRING(email, 64);
    eng->phoneNumber = STRING(phone, 12);

    eng->password = STRING(pass, 64);

    return eng;
}

int add_engineer() { return 1; }
int remove_engineer() { return 1; }

int get_all_engineers() { return 1; }
int get_accepted_engineers() { return 1; }
int get_pending_engineers() { return 1; }
int get_rejected_engineers() { return 1; }
