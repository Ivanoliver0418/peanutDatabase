#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "pager.h"

Pager *pager_open(const char *filename) 
{
    Pager *pager;
    FILE *file;
    long file_size;
    
    /* Creates memory for pager */
    pager = malloc(sizeof(Pager));

    if (pager == NULL) {
        return NULL;
    }
    
    /* Read file */
    file = fopen(filename, "r+b");

    /* Write file if we have nothing to read */
    if (file == NULL) {
        file = fopen(filename, "w+b");
    }

    if (file == NULL) {
        free(pager);
        return NULL;
    }

    /* Getting file size then move to the end */
    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        free(pager);
        return NULL;
    }

    /* Tells the current position pointer for a given file stream. */
    file_size = ftell(file);

    if (file_size < 0) {
        fclose(file);
        free(pager);
        return NULL;
    }

    /* Database should have complete pages */
    if (file_size % PAGE_SIZE != 0) {
        printf("FAILED: incomplete database page\n");
        fclose(file);
        free(pager);
        return NULL;
    }

    pager->file = file;
    pager->page_count = (uint32_t)file_size / PAGE_SIZE;

    uint32_t i;

    for (i = 0; i < TABLE_MAX_PAGES; i++) {
        pager->pages[i] = NULL;
    }

    printf("Pager opened successfully.\n");
    printf("Page count = %u\n", pager->page_count);

    return pager;
}

int pager_read_page(Pager *pager, uint32_t page_id, unsigned char *page)
{
    long offset;

    /* page id starts from 0 */
    if (page_id >= pager->page_count) {
        return 0;
    }
    
    offset = page_id * PAGE_SIZE;

    /* Checks for cursor */
    if (fseek(pager->file, offset, SEEK_SET) != 0) {
        return 0;
    }

    if (fread(page, PAGE_SIZE, 1, pager->file) != 1) {
        return 0;
    }

    return 1;
}

int pager_write_page(Pager *pager, uint32_t page_id, const unsigned char *page)
{
    long offset;

    /* page id starts from 0 */
    if (page_id >= pager->page_count) {
        return 0;
    }

    offset = page_id * PAGE_SIZE;

    if (fseek(pager->file, offset, SEEK_SET) != 0) {
        return 0;
    }

    if (fwrite(page, PAGE_SIZE, 1, pager->file) != 1) {
        return 0;
    }

    fflush(pager->file);

    return 1;
}

void pager_close(Pager *pager)
{
    if (pager == NULL) {
        return;
    }

    if (pager->file != NULL) {
        fclose(pager->file);
    }

    free(pager);
}

void page_init(unsigned char *page)
{
    memset(page, 0, PAGE_SIZE);

    write_u32_le(page + PAGE_RECORD_COUNT_OFFSET, 0);
}

uint32_t page_get_type(const unsigned char *page)
{
    return read_u32_le(page + PAGE_TYPE_OFFSET);
}

uint32_t page_get_record_count(const unsigned char *page)
{
    return read_u32_le(page + PAGE_RECORD_COUNT_OFFSET);
}

void page_set_record_count(unsigned char *page, uint32_t count)
{
    write_u32_le(page + PAGE_RECORD_COUNT_OFFSET, count);
}

unsigned char *page_record_at(unsigned char *page, uint32_t record_number)
{
    return page + PAGE_HEADER_SIZE + record_number * USER_RECORD_SIZE;
}

void* get_pager(Pager* pager, uint32_t page_id) 
{
    if (page_id >= TABLE_MAX_PAGES) {
        printf("Tried to fetch page number out of bounds. %d > %d\n",
                page_id, TABLE_MAX_PAGES);
        return NULL;
    }

    if (pager->pages[page_id] == NULL) {
        /* Cache miss. Allocate memory and load from file. */
        void *page;
        long offset;
        printf("Cache miss: page %u\n", page_id);

        page = malloc(PAGE_SIZE);

        if (page == NULL) {
            return NULL;
        }
        
        if (page_id < pager->page_count) {
            offset = (long)page_id * PAGE_SIZE;
            if (fseek(pager->file, offset, SEEK_SET) != 0) {
                free(page);
                return NULL;
            }
            if (fread(page, PAGE_SIZE, 1, pager->file) != 1) {
                free(page);
                return NULL;
            }

        } else if (page_id == pager->page_count) {
            memset(page, 0, PAGE_SIZE);
            pager->page_count++;
        } else {
            free(page);
            return NULL;
        }

        pager->pages[page_id] = page;
    } else {
        /* Page already in RAM. */
        printf("cache hit: page %u\n", page_id);
    }

    return pager->pages[page_id];
}
