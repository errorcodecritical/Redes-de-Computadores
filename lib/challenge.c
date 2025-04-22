#include "challenge.h"

#define MAX_CHALLENGES 100  // Define a maximum or manage dynamic resizing

typedef struct {
    challenge* challenges;
    int index;
} CallbackData;

int select_callback_challenges(void *data, int argc, char **argv, char **azColName) {
    CallbackData* cbData = (CallbackData*)data;

    if (cbData->index >= MAX_CHALLENGES) {
        return 1; // Stop processing if array is full
    }

    challenge* e = &cbData->challenges[cbData->index];

    e->id = argv[0] ? atoi(argv[0]) : 0;
    e->name = argv[1] ? strdup(argv[1]) : NULL;
    e->description = argv[2] ? strdup(argv[2]) : NULL;
    e->engineerType = argv[3] ? strdup(argv[3]) : NULL;
    e->hours = argv[4] ? atoi(argv[4]) : 0;
    e->organizationId = argv[5] ? atoi(argv[5]) : 0;
    e->status = argv[6] ? atoi(argv[6]) : 0;

    cbData->index++;
    return 0;
}

static int callback_challenges(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    for(i = 0; i < argc; i++) {
       printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
 }

int add_challenge(char* name, char* description, char* type, int hours, int organization_id, bool status) {
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
    sprintf(sql, "INSERT INTO challenges (name,description,type,hours,organization_id,status) VALUES ('%s','%s','%s',%d,%d,%d); ",
        name, description, type, hours, organization_id, status);

    /* Execute SQL statement */    
    if(sqlite3_exec(db, sql, callback_challenges, 0, &err) != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", err);
        sqlite3_free(err);
        return 0;
    } else {
        fprintf(stdout, "Records created successfully\n");
    }

    sqlite3_close(db);

    return 1;
}

int update_challenge(challenge* challenges) {
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
    sprintf(sql, "UPDATE engineers SET name='%s',description='%s',type='%s',hours='%d',organization_id='%d',status='%d'; ",
        challenges->name, challenges->description, challenges->engineerType, challenges->hours, challenges->organizationId, challenges->status);

    /* Execute SQL statement */
    if(sqlite3_exec(db, sql, callback_challenges, 0, &err) != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", err);
        sqlite3_free(err);
        return 0;
    } else {
        fprintf(stdout, "Operation done successfully\n");
    }

    sqlite3_close(db);
    return 1; 
}

int remove_challenge(int id) {
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
    sprintf(sql, "DELETE from challenges where id='%d'; SELECT * from challenges", id);

    /* Execute SQL statement */
    if(sqlite3_exec(db, sql, callback_challenges, 0, &err) != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", err);
        sqlite3_free(err);
        return 0;
    } else {
        fprintf(stdout, "Operation done successfully\n");
    }

    sqlite3_close(db);
    return 1;
}

int get_all_challenges(challenge** challenges, char* condition) {
    sqlite3* db;
    char sql[512];
    char* err = 0;

    *challenges = malloc(MAX_CHALLENGES * sizeof(challenge));

    CallbackData cbData = { .challenges = *challenges, .index = 0 };

    /* Open database */  
    if(sqlite3_open(LOCAL_DB, &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    } else {
        fprintf(stderr, "Opened database successfully\n");
    }

    /* Create SQL statement */
    sprintf(sql, "SELECT * from challenges %s", condition);

    /* Execute SQL statement */    
    if(sqlite3_exec(db, sql, select_callback_challenges, &cbData, &err) != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", err);
        sqlite3_free(err);
        return 0;
    } else {
        fprintf(stdout, "Records selected successfully\n");
    }

    sqlite3_close(db);

    return cbData.index;
}

// void addChallengePrompt(int client_fd, organization * org){

//     char name[BUF_SIZE];
//     char description[BUF_SIZE];
//     char engineerType[BUF_SIZE];
//     char hours[BUF_SIZE];
//     int nread;
    
//     char* challenge_prompt = "You're now registering a new challenge please insert:\n"
//                              "Challenge name: ";

//     write(client_fd, challenge_prompt, strlen(challenge_prompt));
//     nread = read(client_fd, name, BUF_SIZE-1);
//     name[nread-2] = '\0';

//     char* description_prompt = "\nDescription: ";
//     write(client_fd, description_prompt, strlen(description_prompt));
//     nread = read(client_fd, description, BUF_SIZE-1);
//     description[nread-2] = '\0';

//     char* engineerType_prompt = "\nengineerType: ";
//     write(client_fd, engineerType_prompt, strlen(engineerType_prompt));
//     nread = read(client_fd, engineerType, BUF_SIZE-1);
//     engineerType[nread-2] = '\0';

//     char* hours_prompt = "\nhours: ";
//     write(client_fd, hours_prompt, strlen(hours_prompt));
//     nread = read(client_fd, hours, BUF_SIZE-1);
//     hours[nread-2] = '\0';
    
//     int h = atoi(hours);

//     challenge* chall = new_challenge(name, description, engineerType, h);

//     add_challenge(org->challenge_list, chall);

// }
