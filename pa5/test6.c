#include    "malloc.h"

int main (int argc, char **argv){
    string s = (string) malloc(200);
    strcpy(s, "blah blah");
    printf("%s\n", s);
	s[2] = 'w';
	printf("\n\n%s\n\n", s);
	free(s);
    free(s);
    return 0;
}
