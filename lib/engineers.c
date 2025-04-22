#include "engineers.h"

engineer* new_engineer(char* nm, int numb, engineeringSpecialty* engSpec_list, char* employInst,
    bool studStat, aoE_list* areasOfExpertise_list, char* email, char* phone, char* pass) {

    struct engineer* eng = (engineer*)malloc(sizeof(engineer));
    eng->name = create_String(nm);
    eng->number = numb;
    eng->engineeringSpecialty_list = engSpec_list;
    eng->employmentInstitution = create_String(employInst);
    eng->studentStatus = studStat;
    eng->areasOfExpertise_list = areasOfExpertise_list;
    eng->email = create_String(email);

    for (int i = 0; i < 9; i++) {
        *(eng->phoneNumber + i) = *(phone);
    }

    eng->password = create_String(pass);

    return eng;
}

int add_engineer() { return 1; }
int remove_engineer() { return 1; }

int get_all_engineers() { return 1; }
int get_accepted_engineers() { return 1; }
int get_pending_engineers() { return 1; }
int get_rejected_engineers() { return 1; }
