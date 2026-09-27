#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "main.h"

#define USER_ID_SIZE 4
#define USER_AGE_SIZE 4

#define USER_ID_OFFSET 0
#define USER_AGE_OFFSET 4
#define USER_NAME_OFFSET 8

#define USER_RECORD_SIZE 40

void write_u32_le(unsigned char *dest, uint32_t value)
{
    dest[0] = value & 0xFF;
    dest[1] = (value >> 8) & 0xFF;
    dest[2] = (value >> 16) & 0xFF;
    dest[3] = (value >> 24) & 0xFF;
}

void serialize_user(const User *user, unsigned char *buffer)
{
    write_u32_le(buffer + USER_ID_OFFSET, user->id);

    write_u32_le(buffer + USER_AGE_OFFSET, user->age);

    memcpy(buffer + USER_NAME_OFFSET, user->name, USER_NAME_SIZE);
}

uint32_t read_u32_le(const unsigned char *src)
{
    return (uint32_t)src[0] |
           ((uint32_t)src[1] << 8) |
           ((uint32_t)src[2] << 16) |
           ((uint32_t)src[3] << 24);
}

void deserialize_user(const unsigned char *buffer, User *user)
{
    user->id = read_u32_le(buffer + USER_ID_OFFSET);

    user->age = read_u32_le(buffer + USER_AGE_OFFSET);

    memcpy(user->name, buffer + USER_NAME_OFFSET, USER_NAME_SIZE);
}

int main(void)
{
    char input[128];

    while (1) {
        printf("peanutdb> ");

        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        if (strcmp(input, "exit\n") == 0) {
            break;
        }

        printf("You entered: %s", input);
    }

    return 0;
}
