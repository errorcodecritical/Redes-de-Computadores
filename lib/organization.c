#include "organization.h"

#define MAX_ORGANIZATIONS 100  // Define a maximum or manage dynamic resizing

typedef struct {
    organization* organizations;
    int index;
} CallbackData;

int select_callback_organizations(void *data, int argc, char **argv, char **azColName) {
    CallbackData* cbData = (CallbackData*)data;

    if (cbData->index >= MAX_ORGANIZATIONS) {
        return 1; // Stop processing if array is full
    }

    organization* e = &cbData->organizations[cbData->index];

    e->organizationId = argv[0] ? atoi(argv[0]) : 0;
    e->name = argv[1] ? strdup(argv[1]) : NULL;
    e->taxIdentificationNumber = argv[2] ? atoi(argv[2]) : 0;
    e->email = argv[3] ? strdup(argv[3]) : NULL;
    e->address = argv[4] ? strdup(argv[4]) : NULL;
    e->activityDescription = argv[5] ? strdup(argv[5]) : NULL;
    e->phoneNumber = argv[6] ? strdup(argv[6]) : NULL;
    e->password = argv[7] ? strdup(argv[7]) : NULL;
    e->status = argv[8] ? atoi(argv[8]) : 0;

    cbData->index++;
    return 0;
}

static int callback_organizations(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    for(i = 0; i < argc; i++) {
       printf("%30s = %30s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
 }

int add_organization(char* name, int tax_id, char* email, char* address, char* description, char* phone, char* password, int status) {
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
    sprintf(sql, "INSERT INTO organizations (name,tax_id,email,address,description,phone,password,status) VALUES ('%s',%d,'%s','%s','%s','%s','%s',%d); ",
        name, tax_id, email, address, description, phone, password, status);

    /* Execute SQL statement */    
    if(sqlite3_exec(db, sql, callback_organizations, 0, &err) != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", err);
        sqlite3_free(err);
        return 0;
    } else {
        fprintf(stdout, "Records created successfully\n");
    }

    sqlite3_close(db);

    return 1;
}

int update_organization(organization* organizations) {
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
    sprintf(sql, "UPDATE organizations SET name='%s',tax_id='%d',email='%s',address='%s',description='%s',phone='%s',password='%s',status='%d' WHERE id='%d'; ",
        organizations->name, organizations->taxIdentificationNumber, organizations->email, organizations->address, organizations->activityDescription, organizations->phoneNumber, organizations->password, organizations->status, organizations->organizationId);

    /* Execute SQL statement */
    if(sqlite3_exec(db, sql, callback_organizations, 0, &err) != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", err);
        sqlite3_free(err);
        return 0;
    } else {
        fprintf(stdout, "Operation done successfully\n");
    }

    sqlite3_close(db);
    return 1; 
}

int remove_organization(int id) {
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
    sprintf(sql, "DELETE from organizations where id='%d'; SELECT * from organizations", id);

    /* Execute SQL statement */
    if(sqlite3_exec(db, sql, callback_organizations, 0, &err) != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", err);
        sqlite3_free(err);
        return 0;
    } else {
        fprintf(stdout, "Operation done successfully\n");
    }

    sqlite3_close(db);
    return 1;
}

int get_all_organizations(organization** organizations, char* condition) {
    sqlite3* db;
    char sql[512];
    char* err = 0;

    *organizations = malloc(MAX_ORGANIZATIONS * sizeof(organization));

    CallbackData cbData = { .organizations = *organizations, .index = 0 };

    /* Open database */  
    if(sqlite3_open(LOCAL_DB, &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    } else {
        fprintf(stderr, "Opened database successfully\n");
    }

    /* Create SQL statement */
    sprintf(sql, "SELECT * from organizations %s", condition);

    /* Execute SQL statement */    
    if(sqlite3_exec(db, sql, select_callback_organizations, &cbData, &err) != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", err);
        sqlite3_free(err);
        return 0;
    } else {
        fprintf(stdout, "Records selected successfully\n");
    }

    sqlite3_close(db);

    return cbData.index;
}

void organizationRegister(int client_fd) {

    char orgName[100], taxID[20], email[100], address[200], description[300], phone[20], pass[20];
    int nread;

    // Get organization details
    write(client_fd, "Enter the organization name: ", strlen("Enter the organization name: "));
    nread = read(client_fd, orgName, 100 - 1);
    orgName[nread - 2] = '\0';


    write(client_fd, "Enter a password: ", strlen("Enter a password: "));
    nread = read(client_fd, pass, 20 - 1);
    pass[nread - 2] = '\0';

    write(client_fd, "Enter the tax identification number: ", strlen("Enter the tax identification number: "));
    nread = read(client_fd, taxID, 20 - 1);
    taxID[nread - 2] = '\0';

    write(client_fd, "Enter the organization's email address: ", strlen("Enter the organization's email address: "));
    nread = read(client_fd, email, 100 - 1);
    email[nread - 2] = '\0';

    write(client_fd, "Enter the organization's address: ", strlen("Enter the organization's address: "));
    nread = read(client_fd, address, 200 - 1);
    address[nread - 2] = '\0';

    write(client_fd, "Enter a brief description of your organization's activities: ", strlen("Enter a brief description of your organization's activities: "));
    nread = read(client_fd, description, 300 - 1);
    description[nread - 2] = '\0';

    write(client_fd, "Enter your mobile phone number (optional): ", strlen("Enter your mobile phone number (optional): "));
    nread = read(client_fd, phone, 20 - 1);
    phone[nread - 2] = '\0';


    write(client_fd, "\n Registration successful!\n", strlen("\n Registration successful!\n"));

    
    add_organization(orgName,taxID,email,address,description,phone,pass,1);
    
}