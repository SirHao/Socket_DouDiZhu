/*! index_map.h
 *  this file contain a simple impl of index-based map
 *  the logic is too simple and just like an array
 */
#ifndef SF_SOCKET_4_MEMCACHED_INDEX_MAP_H
#define SF_SOCKET_4_MEMCACHED_INDEX_MAP_H


#include <sys/types.h>
#include <stddef.h>



#define IDM_INDEX_BITS 16
#define IDM_ENTRY_BITS 10
#define IDM_ENTRY_SIZE (1 << IDM_ENTRY_BITS)
#define IDM_ARRAY_SIZE (1 << (IDM_INDEX_BITS - IDM_ENTRY_BITS))
#define IDM_MAX_INDEX  ((1 << IDM_INDEX_BITS) - 1)

#define idm_array_index(index) (index >> IDM_ENTRY_BITS)
#define idm_entry_index(index) (index & (IDM_ENTRY_SIZE - 1))

/*!
 * @index_map: the map which stores the entries' pointer
 * which means:
 *  1.map must be initialized by caller(eg. @memset(...) or @calloc(...))
 *  2.entry's pointer must be initialized and free by caller
 */
struct index_map {
    void **array[IDM_ARRAY_SIZE];
};

/*!
 * idm_at(...)find and return entry by index
 * @param idm :a pointer to map or map's address
 * @param index :index used in @idm_set()
 * @return entry (must have)
 */
static inline void *idm_at(struct index_map *idm, int index) {
    void **entry;
    entry = idm->array[idm_array_index(index)];
    return entry[idm_entry_index(index)];
}

/*!
 * find a entry ,return it or NULL
 * @param idm :map to store:
 * @param index: index used in @idm_set()
 * @return :entry pointer or NULL
 */
static inline void *idm_lookup(struct index_map *idm, int index) {
    return ((index <= IDM_MAX_INDEX) && idm->array[idm_array_index(index)]) ?
           idm_at(idm, index) : NULL;
}

int idm_set(struct index_map *idm, int index, void *item);
void *idm_clear(struct index_map *idm, int index);


#endif 