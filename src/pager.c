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
