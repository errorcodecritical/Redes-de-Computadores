#ifndef STRUCTS_API_H
#define STRUCTS_API_H

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h> 
#include <string.h>

// Struct pre declaration

struct areasOfExpertise;
struct engineeringSpecialty;
struct engineer;
struct challenge;
struct organization;

// Vector declaration

typedef struct str {
    int size;
    char* text;
} str;

typedef struct areasOfExpertise {
    char* data;
    struct areasOfExpertise* next;
} areasOfExpertise;

typedef struct aoE_list {
    areasOfExpertise* top;
    areasOfExpertise* bottom;
} aoE_list;

typedef struct engineeringSpecialty {
    char* data;
    struct engineeringSpecialty* next;

} engineeringSpecialty;

typedef struct engSpec_List {
    engineeringSpecialty* top;
    engineeringSpecialty* bottom;
} engSpec_List;

// Engineer struct declaration

typedef struct engineer {
    char* name;
    int number;
    engSpec_List* engineeringSpecialty_list;
    char* employmentInstitution;
    bool studentStatus;
    aoE_list* areasOfExpertise_list;
    char* email;
    char phoneNumber[9];
    char* password;
} engineer;

// End of Engineer struct declaration

// Beginning of organization declaration with dependencies

// Beggining of chellenge declaration

typedef struct challenge {
    char* name;
    char* description;
    char* engineerType;
    int hours;
    struct challenge* next;
} challenge;

typedef struct challenge_list {
    challenge* top;
    challenge* bottom;
} challenge_list;

// Ending of chellenge declaration

// Beggining of organization struct declaration

typedef struct organization {
    char* name;
    int taxIdentificationNumber;
    char* email;
    char* address;
    char* activityDescription;
    char* phoneNumber;
    challenge_list* challenge_list;
    char* password;
} organization;

#define STRING(s, n) strncpy(malloc(n), s, n)

#endif