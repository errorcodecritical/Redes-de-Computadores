#include "engineers.h"

engineer* new_engineer(char* nm, int numb, engineeringSpecialty* engSpec_list, char* employInst,
    bool studStat, aoE_list* areasOfExpertise_list, char* email, char* phone, char* pass) {

    struct engineer* eng = (engineer*)malloc(sizeof(engineer));
    eng->name = STRING(nm, 64);
    eng->number = numb;
    eng->engineeringSpecialty_list = engSpec_list;
    eng->employmentInstitution = STRING(employInst, 64);
    eng->studentStatus = studStat;
    eng->areasOfExpertise_list = areasOfExpertise_list;
    eng->email = STRING(email, 64);

    for (int i = 0; i < 9; i++) {
        *(eng->phoneNumber + i) = *(phone);
    }

    eng->password = STRING(pass, 64);

    return eng;
}

int add_engineer() { return 1; }
int remove_engineer() { return 1; }

int get_all_engineers() { return 1; }
int get_accepted_engineers() { return 1; }
int get_pending_engineers() { return 1; }
int get_rejected_engineers() { return 1; }
