#include    "malloc.h"

int main (int argc, char **argv){
    string s = (string) malloc(200);
    strcpy(s, "blah blah");
    free(s);
    free(s);
    return 0;
}
