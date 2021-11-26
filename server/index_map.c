//
// Created by lucas on 2021/8/10.
//

#include "index_map.h"

#include <errno.h>
#include <sys/types.h>
#include <stdlib.h>


static int idm_grow(struct index_map *idm, int index)
{
    idm->array[idm_array_index(index)] = calloc(IDM_ENTRY_SIZE, sizeof(void *));
    if (!idm->array[idm_array_index(index)])
        goto nomem;

    return index;

    nomem:
    errno = ENOMEM;
    return -1;
}

int idm_set(struct index_map *idm, int index, void *item)
{
    void **entry;

    if (index > IDM_MAX_INDEX) {
        errno = ENOMEM;
        return -1;
    }

    if (!idm->array[idm_array_index(index)]) {
        if (idm_grow(idm, index) < 0)
            return -1;
    }

    entry = idm->array[idm_array_index(index)];
    entry[idm_entry_index(index)] = item;
    return index;
}

void *idm_clear(struct index_map *idm, int index)
{
    void **entry;
    void *item;

    entry = idm->array[idm_array_index(index)];
    item = entry[idm_entry_index(index)];
    entry[idm_entry_index(index)] = NULL;
    return item;
}