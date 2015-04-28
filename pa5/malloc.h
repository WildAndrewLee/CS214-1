#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* string;
typedef struct MemEntry* MemEntry;

#define malloc(x)       my_malloc( x, __FILE__, __LINE__)
#define calloc(x,y)       my_calloc( x*y, __FILE__, __LINE__)
#define free(x)         my_free( x, __FILE__, __LINE__)

#define RED             "\x1b[31m"
#define GREEN           "\x1b[32m"
#define RESET           "\x1b[0m"

#define MEM_SIZE        sizeof(struct MemEntry)

struct MemEntry {
    struct MemEntry *prev, *next;
    size_t is_free, size, line_num, pattern;
    string file;
};


void* my_malloc(size_t size, string file, size_t line);
void* my_calloc(size_t size, string file, size_t line);
void my_free(void* ptr, string file, size_t line);
void leak_check();
int is_corrupt();

