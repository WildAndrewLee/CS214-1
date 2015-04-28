#include    "malloc.h"

int main (int argc, char **argv){
    // Case 4
    void* p1 = malloc(0);
    void* p2 = malloc(-1200);
    return 0;
}
