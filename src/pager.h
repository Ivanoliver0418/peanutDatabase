#ifndef PAGER_H
#define PAGER_H

#include <stdint.h>
#include <stdio.h>

#define PAGE_TYPE_OFFSET 0
#define PAGE_TYPE_SIZE 4

#define PAGE_RECORD_COUNT_OFFSET 4
#define PAGE_RECORD_COUNT_SIZE 4

#define PAGE_HEADER_SIZE 8

#define PAGE_SIZE 4096

#define TABLE_MAX_PAGES 100



typedef struct {
    FILE *file;
    uint32_t page_count;
    void *pages[TABLE_MAX_PAGES];
} Pager;

typedef struct {
    Pager* pager;
    uint32_t num_rows;
} Table;

Pager *pager_open(const char *filename);

int pager_read_page(Pager *pager, uint32_t page_id, unsigned char *page);

int pager_write_page(Pager *pager, uint32_t page_id, const unsigned char *page);

void pager_close(Pager *pager);

Table* db_open(const char *filename);

#endif
