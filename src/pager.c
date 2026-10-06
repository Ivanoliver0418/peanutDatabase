#include <stdio.h>
#include <stdlib.h>

Pager *pager_open(const char *filename) 
{
    Pager *pager;
    FILE *file;
    long page_count;
    
    /* Creates memory for pager */
    pager = malloc(sizeof(pager));

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

    file_size = ftell(file);

    if (file_size < 0) {
        fclose(file);
        free(pager);
        return NULL;
    }

    /* Database should have complete pages */
    if (file_size % PAGE_SIZE != 0) {
        fclose(file);
        free(pager);
        return NULL;
    }

    pager->file = file;
    pager->page_count = page_count;
}

int pager_read_page(Pager *pager, uint32_t page_id, unsigned char *page)
{
    long offset;

    /* page id starts from 0 */
    if (page_id >= pager->count) {
        return 0;
    }
    
    offset = page_id * PAGE_SIZE;

    /* Checks for cursor */
    if (fseek(pager->file, offset, SEEK_SET) != 0) {
        return 0;
    }

    if (fread(file, PAGE_SIZE, 1, pager->file) != 1) {
        return 0;
    }

    return 1;
}

int pager_write_page(Pager *pager, uint32_t page_id, const unsigned char *page)
{
    long offset;

    /* page id starts from 0 */
    if (page_id > page_count) {
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

    if (page_id == pager->page_count) {
        pager->page_count++;
    }

    return 1;
}

void pager_close(Pager *pager)
{
    if (pager == NULL) {
        return NULL;
    }

    if (pager->file != NULL) {
        fclose(pager->file);
    }

    free(pager);
}
