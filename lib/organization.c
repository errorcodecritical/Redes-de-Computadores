// #include "organization.h"

// #define MAX_ORGANIZATIONS 100  // Define a maximum or manage dynamic resizing

// typedef struct {
//     organization* organizations;
//     int index;
// } CallbackData;

// int select_callback_organizations(void *data, int argc, char **argv, char **azColName) {
//     CallbackData* cbData = (CallbackData*)data;

//     if (cbData->index >= MAX_ORGANIZATIONS) {
//         return 1; // Stop processing if array is full
//     }

//     challenge* e = &cbData->organizations[cbData->index];

//     e->id = argv[0] ? atoi(argv[0]) : 0;
//     e->name = argv[1] ? strdup(argv[1]) : NULL;
//     e->description = argv[2] ? strdup(argv[2]) : NULL;
//     e->engineerType = argv[3] ? strdup(argv[3]) : NULL;
//     e->hours = argv[4] ? atoi(argv[4]) : 0;
//     e->organizationId = argv[5] ? atoi(argv[5]) : 0;
//     e->status = argv[6] ? atoi(argv[6]) : 0;

//     cbData->index++;
//     return 0;
// }

// static int callback_organizations(void *NotUsed, int argc, char **argv, char **azColName) {
//     int i;
//     for(i = 0; i < argc; i++) {
//        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
//     }
//     printf("\n");
//     return 0;
//  }

// int add_organization(char* name, int tax_id, char* email, char* address, char* description, char* phone, char* password, int status) {
//     sqlite3* db;
//     char sql[512];
//     char* err = 0;

//     /* Open database */  
//     if(sqlite3_open(LOCAL_DB, &db)) {
//         fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
//         return 0;
//     } else {
//         fprintf(stderr, "Opened database successfully\n");
//     }

//     /* Create SQL statement */
//     sprintf(sql, "INSERT INTO challenges (name,description,type,hours,organization_id,status) VALUES ('%s','%s','%s',%d,%d,%d); ",
//         name, description, type, hours, organization_id, status);

//     /* Execute SQL statement */    
//     if(sqlite3_exec(db, sql, callback_challenges, 0, &err) != SQLITE_OK){
//         fprintf(stderr, "SQL error: %s\n", err);
//         sqlite3_free(err);
//         return 0;
//     } else {
//         fprintf(stdout, "Records created successfully\n");
//     }

//     sqlite3_close(db);

//     return 1;
// }

// int update_organization(organization* organizations) {

// }

// int remove_organization(int id) {

// }

// int get_all_organizations(organization** organizations, char* condition) {

// }
