#include <stdio.h>

#include "../hashmap.h"
#include "minunit.h"

typedef struct {
    string name;
    int age;
} user;

user users[] = {{.name = "Naman", .age = 21},
                {.name = "Jhon Abra", .age = 15},
                {.name = "Shushma", .age = 33},
                {.name = "Kavita rajput", .age = 19},
                {.name = "Abraham", .age = 40}};
string keys[] = {"naman", "jhon", "shushma", "kavita", "abraham"};
int LEN = sizeof(users) / sizeof(user);
map_ptr m = NULL;

static void print_user(c_void_ptr data) {
    if (data == NULL) {
        printf("data is NULL, %p\n", data);
        return;
    }
    const user *u = data;
    printf("{\"name\": \"%s\", \"age\": %d}", u->name, u->age);
}

static void asser_user_eq(user *u1, user *u2) {
    mu_assert_int_eq(u1->age, u2->age);
    mu_assert_string_eq(u1->name, u2->name);
}

MU_TEST(test_create) {
    m = map_create(sizeof(user), NULL, NULL);
    map_display(m, print_user);
    mu_assert(m != NULL, "map not created");
    mu_assert_int_eq(0, map_length(m));
}

MU_TEST(test_set) {
    for (int i = 0; i < LEN; i++) {
        map_set(m, keys[i], &users[i]);
        map_display(m, print_user);
        printf("length: %d\n", map_length(m));

        mu_assert_int_eq(i + 1, map_length(m));
    }
}

MU_TEST(test_get) {
    for (int i = 0; i < LEN; i++) {
        user *u = map_get(m, keys[i]);
        print_user(u);

        asser_user_eq(&users[i], u);
    }
}

MU_TEST(test_update) {
    int initial_length = map_length(m);
    string new_name = "Naman Tamrakar";
    users[0].name = new_name;

    map_set(m, keys[0], &users[0]);

    user *u = map_get(m, keys[0]);
    print_user(u);

    mu_assert_int_eq(initial_length, map_length(m));
    mu_assert_string_eq(new_name, u->name);
    asser_user_eq(&users[0], u);
}

MU_TEST(test_delete) {
    int initial_len = map_length(m);
    mu_assert(map_delete(m, "hello", NULL) == false,
              "deleting a unknown key returing true");

    for (int i = LEN - 1; i >= 0; i--) {
        user u;
        mu_assert(map_delete(m, keys[i], &u) == true,
                  "map delete returned false");
        print_user(&u);

        mu_assert_int_eq(--initial_len, map_length(m));
        mu_assert(map_get(m, keys[i]) == NULL, "map get should return NULL");
        asser_user_eq(&u, &users[i]);
    }

    mu_assert(map_delete(m, keys[0], NULL) == false,
              "deleting a deleted key returing true");
}

MU_TEST(test_destroy) {
    map_destroy(&m);
    map_display(m, print_user);
    mu_assert(m == NULL, "map pointer should be NULL");
    mu_assert_int_eq(0, map_length(m));
}

MU_TEST_SUITE(test_suit) {
    MU_RUN_TEST(test_create);
    MU_RUN_TEST(test_set);
    MU_RUN_TEST(test_get);
    MU_RUN_TEST(test_update);
    MU_RUN_TEST(test_delete);
    MU_RUN_TEST(test_destroy);
}

int main() {
    MU_RUN_SUITE(test_suit);
    MU_REPORT();

    return 0;
}