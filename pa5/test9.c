#include    "malloc.h"

int main (int argc, char **argv){
    string a = (string) calloc(2, 200);
    a[1] = 'h';
    free(a);
    return 0;
}
