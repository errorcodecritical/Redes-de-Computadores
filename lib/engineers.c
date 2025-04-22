#include "engineers.h"

#define MAX_ENGINEERS 100  // Define a maximum or manage dynamic resizing

typedef struct {
    engineer* engineers;
    int index;
} CallbackData;

int select_callback_engineers(void *data, int argc, char **argv, char **azColName) {
    CallbackData* cbData = (CallbackData*)data;

    if (cbData->index >= MAX_ENGINEERS) {
        return 1; // Stop processing if array is full
    }

    engineer* e = &cbData->engineers[cbData->index];

    e->name = argv[0] ? strdup(argv[0]) : NULL;
    e->number = argv[1] ? atoi(argv[1]) : 0;
    e->engineeringSpecialty = argv[2] ? strdup(argv[2]) : NULL;
    e->employmentInstitution = argv[3] ? strdup(argv[3]) : NULL;
    e->studentStatus = argv[4] ? atoi(argv[4]) : false; // SQLite stores booleans as integers
    e->areasOfExpertise = argv[5] ? strdup(argv[5]) : NULL;
    e->email = argv[6] ? strdup(argv[6]) : NULL;
    e->phoneNumber = argv[7] ? strdup(argv[7]) : NULL;
    e->password = argv[8] ? strdup(argv[8]) : NULL;

    cbData->index++;
    return 0;
}

int callback_engineers(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    for(i = 0; i < argc; i++) {
       printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
 }

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

int add_engineer(char* name, int number, char* specialty, char* institution, bool student, char* areas_of_expertise, char* email, char* phone, char* password, int status) {
    sqlite3* db;
    char sql[512];
    char* err = 0;

    /* Open database */  
    if(sqlite3_open(LOCAL_DB, &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    } else {
        fprintf(stderr, "Opened database successfully\n");
    }

    /* Create SQL statement */
    sprintf(sql, "INSERT INTO engineers (name,number,specialty,institution,student,areas_of_expertise,email,phone,password,status) VALUES ('%s',%d,'%s','%s',%d,'%s','%s','%s','%s', %d); ",
        name, number, specialty, institution, student, areas_of_expertise, email, phone, password, status);

    /* Execute SQL statement */    
    if(sqlite3_exec(db, sql, callback_engineers, 0, &err) != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", err);
        sqlite3_free(err);
        return 0;
    } else {
        fprintf(stdout, "Records created successfully\n");
    }

    sqlite3_close(db);

    return 1;
}

int update_engineer(engineer* engineers) {
    sqlite3* db;
    char sql[512];
    char* err = 0;

    /* Open database */  
    if(sqlite3_open(LOCAL_DB, &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    } else {
        fprintf(stderr, "Opened database successfully\n");
    }

    /* Create merged SQL statement */
    sprintf(sql, "UPDATE engineers SET name='%s',number='%d',specialty='%s',institution='%s',student='%d',areas_of_expertise='%s',email='%s',phone='%s',password='%s',status='%d'; ",
        engineers->name, engineers->number, engineers->engineeringSpecialty, engineers->employmentInstitution, engineers->studentStatus, engineers->areasOfExpertise, engineers->email, engineers->phoneNumber, engineers->password, engineers->status);

    /* Execute SQL statement */
    if(sqlite3_exec(db, sql, callback_engineers, 0, &err) != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", err);
        sqlite3_free(err);
        return 0;
    } else {
        fprintf(stdout, "Operation done successfully\n");
    }

    sqlite3_close(db);
    return 1; 
}

int remove_engineer(char* email) {
    sqlite3* db;
    char sql[512];
    char* err = 0;

    /* Open database */  
    if(sqlite3_open(LOCAL_DB, &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    } else {
        fprintf(stderr, "Opened database successfully\n");
    }

    /* Create merged SQL statement */
    sprintf(sql, "DELETE from engineers where email='%s'; SELECT * from engineers", email);

    /* Execute SQL statement */
    if(sqlite3_exec(db, sql, callback_engineers, 0, &err) != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", err);
        sqlite3_free(err);
        return 0;
    } else {
        fprintf(stdout, "Operation done successfully\n");
    }

    sqlite3_close(db);
    return 1; 
}

int get_all_engineers(engineer** engineers, char* condition) { 
    sqlite3* db;
    char sql[512];
    char* err = 0;

    *engineers = malloc(MAX_ENGINEERS * sizeof(engineer));

    CallbackData cbData = { .engineers = *engineers, .index = 0 };

    /* Open database */  
    if(sqlite3_open(LOCAL_DB, &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    } else {
        fprintf(stderr, "Opened database successfully\n");
    }

    /* Create SQL statement */
    sprintf(sql, "SELECT * from engineers %s", condition);

    /* Execute SQL statement */    
    if(sqlite3_exec(db, sql, select_callback_engineers, &cbData, &err) != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", err);
        sqlite3_free(err);
        return 0;
    } else {
        fprintf(stdout, "Records selected successfully\n");
    }

    sqlite3_close(db);

    return cbData.index;
}