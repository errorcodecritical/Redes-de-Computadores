#ifndef STRUCTS_API_H
#define STRUCTS_API_H

#include <unistd.h>
#include <stdbool.h> 
#include <string.h>

// Struct pre declaration

struct str;
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
    str* data;
    struct areasOfExpertise* next;
} areasOfExpertise;

typedef struct aoE_list {
    areasOfExpertise* top;
    areasOfExpertise* bottom;
} aoE_list;

typedef struct engineeringSpecialty {
    str* data;
    struct engineeringSpecialty* next;

} engineeringSpecialty;

typedef struct engSpec_List {
    engineeringSpecialty* top;
    engineeringSpecialty* bottom;
} engSpec_List;

typedef struct challenge_list {
    challenge* top;
    challenge* bottom;
} challenge_list;

// Engineer struct declaration

typedef struct engineer {
    str* name;
    int number;
    engSpec_List* engineeringSpecialty_list;
    str* employmentInstitution;
    bool studentStatus;
    aoE_list* areasOfExpertise_list;
    str* email;
    char phoneNumber[9];
    str* password;

} engineer;

// End of Engineer struct declaration

// Beginning of organization declaration with dependencies

// Beggining of chellenge declaration

typedef struct challenge {
    str* name;
    str* description;
    str* engineerType;
    int hours;
    struct challenge* next;
} challenge;

// Ending of chellenge declaration

// Beggining of organization struct declaration

typedef struct organization {
    str* name;
    int taxIdentificationNumber;
    str* email;
    str* address;
    str* activityDescription;
    char phoneNumber[9];
    challenge_list* challenge_list;
    str* password;
} organization;

typedef struct sc {
    struct str* string;
    int size;
} sc;

typedef struct bc {
    struct sc* small_class;
    struct str* bctext;
} bc;

#endif