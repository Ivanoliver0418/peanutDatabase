#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>

#define USER_NAME_SIZE 32

#define USER_ID_SIZE 4
#define USER_AGE_SIZE 4
#define USER_ID_OFFSET 0
#define USER_AGE_OFFSET 4
#define USER_NAME_OFFSET 8
#define USER_RECORD_SIZE 40

/* Struct for data */
typedef struct {
    uint32_t id;
    uint32_t age;
    char name[USER_NAME_SIZE];
} User;

void write_u32_le(unsigned char *dest, uint32_t value);

void serialize_user(const User *user, unsigned char *buffer);

uint32_t read_u32_le(const unsigned char *src);

void deserialize_user(const unsigned char *buffer, User *user);

#endif
