#include <stdbool.h>
#include <stdlib.h>

#ifndef __QUEUE_H__
#define __QUEUE_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef void *void_ptr;
typedef const void *c_void_ptr;
typedef char *string;
typedef const string c_string;

typedef struct Map map;
typedef map *map_ptr;
typedef const map_ptr c_map_ptr;

/**
 * Function to create a map
 *
 * @param size: Size of data
 * @param key: key string of map
 * @param data: data pointer of map
 * @return returns a map pointer
 */
map_ptr map_create(size_t size, string key, c_void_ptr data);

/**
 * Function to update or create an element with given key
 *
 * @param m: map pointer
 * @param key: key of map
 * @param data: data to put
 *
 * @return void(0)
 */
void map_set(map_ptr m, string key, void_ptr data);

/**
 * Function to get an element from key if not found returns NULL.
 *
 * @param m: map pointer
 * @param key: key of map
 *
 * @return data pointer || void(0)
 */
void_ptr map_get(map_ptr m, string key);

/**
 * Function to delete an element with given key
 *
 * @param m: map pointer
 * @param key: key of map
 * @param data: data to which this data will be copied
 *
 * @return true if success else false
 */
bool map_delete(map_ptr m, string key, void_ptr data);

/**
 * Funtion to get the length of map
 * 
 * @param m: map pointer
 * @return length of map
*/
int map_length(map_ptr m);

/**
 * Function to delete an element with given key
 *
 * @param m: map pointer
 * @param print_data: void function which takes constant void pointer as
 * argument
 * @return void(0)
 */
void map_display(map_ptr m, void (*print_data)(c_void_ptr));

/**
 * Function to delete a map completely
 *
 * @param m: double pointer to map
 */
void map_destroy(map_ptr *m);

#ifdef __cplusplus
}
#endif

#endif  // __QUEUE_H__