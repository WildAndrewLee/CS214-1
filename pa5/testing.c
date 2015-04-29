#include <stdio.h>
#include <stdlib.h>
#include "malloc.h"

struct node {
	int value;
	struct node* next;
};

typedef struct node* node;

int main(){
	printf("Manual Malloc---------\n");
	int* one = malloc(sizeof(int));
	int* two = malloc(sizeof(int));
	int* three = malloc(sizeof(int));
	int* four = malloc(sizeof(int));

	*one = 1;
	*two = 2;
	*three = 3;
	*four = 4;

	printf("%d %d %d %d", *one, *two, *three, *four);

	free(one);
	free(two);
	free(three);
	free(four);

	printf("\nPost-Manual Malloc----------\n");

	int* x = calloc(sizeof(*x), 10);

	printf("Called calloc-----------\n");

	for(int n = 1; n <= 10; n++)
		x[n - 1] = n;

	int sum = 0;

	for(int n = 0; n < 10; n++)
		sum += x[n];

	printf("Sum of 1-10 array via calloc: %d\n", sum);

	//free(x);
/*
	printf("Post-Calloc\n");	

	node first = (node) malloc(sizeof(node));
	first->value = 1;
	first->next = 0;

	printf("Malloc'd first\n");

	node current = first;
	node next = 0;

	//printf("Created Node %p\n", (void*) current);
	for(int n = 1; n < 10; n++){
		next = (node) malloc(sizeof(node));
		printf("Mementry Should Be Here: %p\n", ((char*) next) - sizeof(struct MemEntry));

		next->value = x[n];
		next->next = 0;
		current->next = next;
		current = next;
		//printf("Created Node %p\n", (void*) current);
	}

	current = first;

	while(current != 0){
		//printf("Will print and free pointer %p\n", current);

		printf("%d ", current->value);
		node temp = current;
		current = current->next;
		free(temp);
	}

	printf("\n");
//  */
	free(x);

	printf("\nLinked List Test Should be 1, 2, 3 (Manual Alloc and Linking)------\n");
	//Testing Linked List Manual Alloc
	node one1 = malloc(sizeof(*one1));
	node two2 = malloc(sizeof(*two2));
	node three3 = malloc(sizeof(*three3));

	one1->next = two2;
	two2->next = three3;
	three3->next = 0;

	one1->value = 1;
	two2->value = 2;
	three3->value = 3;

	node current = one1;

	while(current){
		printf("%d ", current->value);
		node temp = current;
		current = current->next;
		free(temp);
	}

	printf("\nPost Linked-List Test---------\n");

	printf("Testing Realloc (Dynamic Array of User Input Numbers)-----------\n");

	// Testing Realloc

	int* numbers = 0;
	int* more_numbers = 0;
	int count = 0;
	int input = 0;


	do {
		printf("Enter an integer (0 to end): ");
		scanf("%d", &input);
		count++;

		more_numbers = (int*) realloc(numbers, count * sizeof(int));

		if(more_numbers){
			numbers = more_numbers;
			numbers[count - 1] = input;
		}
		else{
			free(numbers);
			printf("Error\n");
			return 0;
		}
	} while(input != 0);

	printf("Numbers Entered: ");
	
	for(int n = 0; n < count; n++)
		printf("%d ", numbers[n]);

	printf("\n");

	free(numbers);

	printf("Post-Realloc------\n");

	return 0;
}
