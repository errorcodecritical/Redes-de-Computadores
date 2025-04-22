#ifndef STRUCTS_API_H
#define STRUCTS_API_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h> 
#include <string.h>

#include "sqlite3.h"

#define LOCAL_DB "bin/local.db"

// Struct pre declaration
struct engineer;
struct challenge;
struct organization;

// Vector declaration

typedef struct str {
    int size;
    char* text;
} str;

// Engineer struct declaration

typedef struct engineer {
    char* name;
    int number;
    char* engineeringSpecialty;
    char* employmentInstitution;
    bool studentStatus;
    char* areasOfExpertise;
    char* email;
    char* phoneNumber;
    char* password;
    bool status;
} engineer;

// End of Engineer struct declaration

// Beginning of organization declaration with dependencies

// Beggining of chellenge declaration

typedef struct challenge {
    int id;
    char* name;
    char* description;
    char* engineerType;
    int hours;
    int organizationId;
    int status;
} challenge;

// Ending of chellenge declaration

// Beggining of organization struct declaration

typedef struct organization {
    int organizationId;
    char* name;
    int taxIdentificationNumber;
    char* email;
    char* address;
    char* activityDescription;
    char* phoneNumber;
    char* password;
    int status;
} organization;

#define STRING(s, n) strncpy(malloc(n), s, n)

#endif