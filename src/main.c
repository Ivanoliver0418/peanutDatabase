#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "main.h"
#include "pager.h"

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

int read_page(FILE *file, uint32_t page_id, unsigned char *page)
{
    long offset;

    offset = (long)page_id * PAGE_SIZE;

    if (fseek(file, offset, SEEK_SET) != 0) {
        return 0;
    }

    if (fread(page, PAGE_SIZE, 1, file) != 1) {
        return 0;
    }

    return 1;
}

int write_page(FILE *file, uint32_t page_id, const unsigned char *page)
{
    long offset;

    offset = (long)page_id * PAGE_SIZE;

    if (fseek(file, offset, SEEK_SET) != 0) {
        return 0;
    }

    if (fwrite(page, PAGE_SIZE, 1, file) != 1) {
        return 0;
    }

    return 1;
}

int main(void)
{
    Pager *pager;
    
    void *page0a;
    void *page0b;
    
    void *page1a;
    void *page1b;

    pager = pager_open("peanut.db");

    if (pager == NULL) {
        printf("Could not open database\n");
        return 1;
    }
    page0a = get_pager(pager, 0);

    if (page0a == NULL) {
        printf("Could not get page 0\n");
        pager_close(pager);
        return -1;
    }

    page0b = get_pager(pager, 0);

    if (page0b == NULL) {
        printf("Could not get page 0 again\n");
        pager_close(pager);
        return 1;
    }

    page1a = get_pager(pager, 1);

    if (page1a == NULL) {
        printf("Could not open page 1\n");
        pager_close(pager);
        return 1;
    }

    page1b = get_pager(pager, 1);

    if (page1b == NULL) {
        printf("Could not get page 1 again\n");
        pager_close(pager);
        return 1;
    }

    printf("page0a address: %p\n", page0a);
    printf("page0b address: %p\n", page0b);
    
    printf("page1a address: %p\n", page1a);
    printf("page1b address: %p\n", page1b);

    pager_close(pager);

    return 0;
}
