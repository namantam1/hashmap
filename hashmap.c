/*
MIT License

Copyright (c) 2021 Naman Tamrakar

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

IDEA:
Hashmap is a data structure where data store in the form of key value pairs
where the datatype of key is generally int, float, string, char but the data
type of value can be any data type that can be created in C language.

It act same as an array, the key difference is that in array only index which is
of type interger can act as the key of DS but in hasmap we have freedom of
choosing any primitive data type that we described above.

In this implementation of hasmap only string can be taken as key.

So the idea here is that we will take an array of fixed length to store our data
at index which will act as key that we will generate from the hashing the
algorithm and to avoid collision case we will use linked list at each index.


*/
#include "hashmap.h"

#include <stdio.h>
#include <string.h>

#define NEW(data) (data *)malloc(sizeof(data))
#define FREE(data) \
    free(data);    \
    data = NULL;

/*
**********************************************************
*  LINKED LIST IMPLEMENTATION                            *
**********************************************************
*/
typedef struct Node {
    void_ptr data;
    string key;
    struct Node *next;
} node;

typedef node *node_ptr;
typedef const node_ptr c_node_ptr;

static node_ptr _create_node(c_string key, size_t size, c_void_ptr data,
                             node_ptr next) {
    node_ptr n = NEW(node);
    n->key = key;
    n->next = next;

    if (data) {
        n->data = malloc(size);
        memcpy(n->data, data, size);
    }

    return n;
}

static bool _destroy_node(node_ptr *n, void_ptr data, size_t size) {
    if (data) memcpy(data, (*n)->data, size);
    FREE((*n)->data)
    FREE(*n);
    return true;
}

static void _prepend(node_ptr *head, c_string key, c_void_ptr data,
                     size_t size) {
    // create a new node with the given data
    // point it to head
    node_ptr n = _create_node(key, size, data, *head);

    // point head to new node
    *head = n;
}

static node_ptr _find_node(node_ptr head, c_string key) {
    while (head) {
        if (strcmp(head->key, key) == 0) return head;
        head = head->next;
    }
    return NULL;
}

static bool _delete_node(node_ptr *head, c_string key, void_ptr data,
                         size_t size) {
    if (*head == NULL) return false;

    node_ptr previous = *head, first = previous->next;

    if (first == NULL && strcmp(previous->key, key) == 0) {
        return _destroy_node(head, data, size);
    }

    while (first) {
        if (strcmp(first->key, key) == 0) {
            previous->next = first->next;
            return _destroy_node(&first, data, size);
        }

        previous = first;
        first = first->next;
    }
}

static void _print_nodes(node_ptr n, void (*print_data)(c_void_ptr)) {
    while (n) {
        printf("%s: ", n->key);
        print_data(n->data);
        printf(", ");
        n = n->next;
    }
}

/*
===============================
* HASMAP IMPLEMENTATION       *
===============================
*/
#define ARR_SIZE 10

typedef struct Map {
    node_ptr nodes[ARR_SIZE];
    size_t size;
    int array_length;
    int length;
} map;

static void _initialize_map_nodes(node_ptr *nodes, int arr_len) {
    for (int i = 0; i < arr_len; i++) nodes[i] = NULL;
}

static int _hash_function(string key, int arr_len) {
    int length = strlen(key);
    unsigned int hash_val = 0;
    for (int i = 0; i < length; i++) {
        hash_val += key[i];
        hash_val *= key[i];
    }

    return hash_val % arr_len;
}

/**
 * Function to create a map
 *
 * @param size: Size of data
 * @param key: key string of map
 * @param data: data pointer of map
 * @return returns a map pointer
 */
map_ptr map_create(size_t size, string key, c_void_ptr data) {
    map_ptr m = NEW(map);
    m->size = size;
    m->array_length = ARR_SIZE;
    m->length = 0;
    _initialize_map_nodes(m->nodes, m->array_length);

    if (key != NULL) {
        m->nodes[_hash_function(key, m->array_length)] =
            _create_node(key, m->size, data, NULL);
        m->length++;
    }

    return m;
}

/**
 * Function to update or create an element with given key
 *
 * @param m: map pointer
 * @param key: key of map
 * @param data: data to put
 *
 * @return void(0)
 */
void map_set(map_ptr m, string key, void_ptr data) {
    // generate the hash
    int hash_val = _hash_function(key, m->array_length);

    // check if key already exists
    node_ptr n = _find_node(m->nodes[hash_val], key);

    // if yes then update its data
    if (n) memcpy(n->data, data, m->size);
    // else create new element
    else {
        _prepend(&m->nodes[hash_val], key, data, m->size);
        m->length++;
    }
}

/**
 * Function to get an element from key if not found returns NULL.
 *
 * @param m: map pointer
 * @param key: key of map
 *
 * @return data pointer || void(0)
 */
void_ptr map_get(map_ptr m, string key) {
    node_ptr p =
        _find_node(m->nodes[_hash_function(key, m->array_length)], key);
    if (p != NULL)
        return p->data;
    else
        return p;
}

/**
 * Function to delete an element with given key
 *
 * @param m: map pointer
 * @param key: key of map
 * @param data: data to which this data will be copied
 *
 * @return true if success else false
 */
bool map_delete(map_ptr m, string key, void_ptr data) {
    bool done = _delete_node(&m->nodes[_hash_function(key, m->array_length)],
                             key, data, m->size);
    if (done) m->length--;
    return done;
}

/**
 * Function to get the length of map
 * 
 * @param m: map pointer
 * @return length of map
*/
int map_length(map_ptr m) {
    return m != NULL ? m->length : 0;
}

/**
 * Function to delete an element with given key
 *
 * @param m: map pointer
 * @param print_data: void function which takes constant void pointer as
 * argument
 * @return void(0)
 */
void map_display(map_ptr m, void (*print_data)(c_void_ptr)) {
    if (m == NULL) {
        printf("map is NULL, %p\n", m);
        return;
    }

    printf("{");
    for (int i = 0; i < m->array_length; i++) {
        _print_nodes(m->nodes[i], print_data);
    }
    printf("}\n");
}

/**
 * Function to delete a map completely
 *
 * @param m: double pointer to map
 */
void map_destroy(map_ptr *m) {
    // iterate over nodes to delete them
    for (int i = 0; i < (*m)->array_length; i++) {
        node_ptr *n = &(*m)->nodes[i];
        while (*n) {
            node_ptr temp = *n;
            *n = (*n)->next;
            _destroy_node(&temp, NULL, (*m)->size);
        }
    }

    // free the main map now
    free(*m);
    *m = NULL;
}
