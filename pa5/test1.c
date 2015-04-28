#include    "malloc.h"

int main (int argc, char **argv){
    // Case 1:
    void *p1 = malloc(100);
    void *p2 = malloc(75);
    void *p3 = malloc(50);
    void *p4 = malloc(125);
    free(p1);
    free(p2);
    free(p3);
    free(p4);
    return 0;
}
