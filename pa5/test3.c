#include    "malloc.h"

int main (int argc, char **argv){
    // Case 3:
    void *p1 = malloc(2500);
    void *p2 = malloc(2500);
    void *p3 = malloc(2500);
    void *p4 = malloc(2500);
    free(p1);
    free(p2);
    free(p3);
    return 0;
}
