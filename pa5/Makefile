
all: malloc test1 test2 test3 test4 test5 test6 test7 test8 test9 test10

test1: malloc test1.c
	gcc -o test1 malloc.o test1.c
test2: malloc test2.c
	gcc -o test2 malloc.o test2.c
test3: malloc test3.c
	gcc -o test3 malloc.o test3.c
test4: malloc test4.c
	gcc -o test4 malloc.o test4.c
test5: malloc test5.c
	gcc -o test5 malloc.o test5.c
test6: malloc test6.c
	gcc -o test6 malloc.o test6.c
test7: malloc test7.c
	gcc -o test7 malloc.o test7.c
test8: malloc test8.c
	gcc -o test8 malloc.o test8.c
test9: malloc test9.c
	gcc -o test9 malloc.o test9.c
test10: malloc test10.c
	gcc -o test10 malloc.o test10.c
malloc:
	gcc -g -c malloc.c malloc.h

clean:
	rm -f malloc *.o *.gch test1 test2 test3 test4 test5 test6 test7 test8 test9 test10
