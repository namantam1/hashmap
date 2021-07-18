[![C/C++ CI](https://github.com/namantam1/hashmap/actions/workflows/CI.yaml/badge.svg)](https://github.com/namantam1/hashmap/actions/workflows/CI.yaml)

# Hashmap Implementation in C Language

## Features - 
1. Generic Data type support.
2. Auto garbage collection while deleting the data from map.
4. Better data structure management.

## How to use -

- Clone this project.
```bash
git clone https://github.com/namantam1/hashmap
cd hashmap
```
- Run the example file with make or command line.
```bash
make && ./example
# or
gcc hashmap.c example.c -o example.out && ./example.out
```
- To use this hashmap in another project import this libary as -
```c
#include "hashmap/hashmap.h"

int main() {
    int data = 10;
    // create a new map
    map_ptr q = map_create(sizeof(int), "some_key", &data);

    // do you stuff
    // ...
    // ...

    // destroy the map if not in use to free the memory.
    map_destroy(&q);
}
```

### Check Complete example
- [example](example.c)

## Issue

If you find any issue please don't hesitate to create an [issue](https://github.com/namantam1/hashmap/issues).

Any Contribution or suggestion are welcome.

## License
This project is under [MIT](LICENSE) License.

## See also
- [Queue Implementation in C](https://github.com/namantam1/queue)
- [Stack Implementation in C](https://github.com/namantam1/stack)
