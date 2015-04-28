#include    "malloc.h"

int main (int argc, char **argv){
    int a = 9;
    int* b = &a;
    free(b);
    return 0;
}
