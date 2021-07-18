#include <stdio.h>
#include "hashmap.h"

typedef struct {
    string name;
    int age;
} user;

void print_user(c_void_ptr data) {
    const user *u = data;
    printf("{name: %s, age: %d}", u->name, u->age);
}

int main() {
    // creating a new map
    map_ptr m = map_create(sizeof(user), "naman",
                           &(user){.name = "Naman Tamrakar", .age = 21});
    
    // set data with key
    map_set(m, "john", &(user){.name = "Jhon", .age = 19});
    map_set(m, "vikas", &(user){.name = "Vikas tam", .age = 22});
    map_set(m, "om", &(user){.name = "Om tam", .age = 18});

    // deiplay map
    map_display(m, print_user);

    // get data from key
    print_user(map_get(m, "naman"));
    print_user(map_get(m, "vikas"));
    print_user(map_get(m, "om"));

    // delete data from key
    map_delete(m, "naman", NULL);
    map_delete(m, "vikas", NULL);
    map_display(m, print_user);
    map_destroy(&m);
    return 0;
}