#include "malloc.h"

#define BLOCK_SIZE  10000

static char block[BLOCK_SIZE];


void* my_malloc(size_t size, string file, size_t line) {
    static int initialized = 0;
    static MemEntry root;
    MemEntry p, succ, smallest = 0;
    int extra_memory = BLOCK_SIZE;

    // If block is uninitialized
    if (!initialized) {
        //Initialize block to be NULL.
		memset(block, 0, BLOCK_SIZE);
		
		root = (MemEntry) block;
        root->prev = root->next = 0;
        root->size = BLOCK_SIZE - sizeof(struct MemEntry);
        root->is_free = 1;
        root->pattern = BLOCK_SIZE + 69;
        root->file = file;
        root->line_num = line;
        atexit(leak_check);
        initialized = 1;
 //   	printf("sizeof(struct MemEntry): %d\n", sizeof(MemEntry));
	}

    // Error checks
    if (is_corrupt() == 1) {
        printf(RED "The data is corrupt. Malloc() can't allocate space.\n");
        printf("\tExiting malloc()\n" RESET);
        return 0;
    } else if ((int) size <= 0) {
        printf(RED "Error: Cannot allocate non-positive space!\n");
        printf("\tError made on line %zd in %s\n" RESET, line, file);
        return 0;
    } else if (size > BLOCK_SIZE) {
        printf(RED "Error: Cannot allocate more than total available space!\n");
        printf("\tError made on line %zd in %s\n" RESET, line, file);
        return 0;
    }

    p = root;

    do {
        // Set smallest member to p if p is big enough, free and closest to size
        if (p->size >= size && p->is_free && p->size-size < extra_memory) {
            extra_memory = p->size - size;
            smallest = p;
        }
        p = p->next;
    } while (p);

    if (!smallest) {
        printf(RED "Error: No room in any block to allocate this chunk!\n");
        printf("\tError made on line %zd in %s\n" RESET, line, file);
        return 0;
    }

    p = smallest;

    if (p->size < (size + sizeof(struct MemEntry))) {
        // Cannot break the current smallest chunk into two chunks
        p->is_free = 0;
        p->line_num = line;
        p->file = file;
		//printf("Returning P: %p Next %p Prev %p\n", p, p->next, p->prev);
		return p+1;
    } else {
        //printf("Splitting node %p %p (addr: %p) \n", p, p->prev, &p->prev);
		// Separate current chunk into two chunks.
        succ = (MemEntry) ((string)p + sizeof(struct MemEntry) + size);
        succ->pattern = BLOCK_SIZE + 69;
        succ->prev = p;
        succ->next = p->next;
        if (p->next)
            p->next->prev = succ;
        p->next = succ;
        succ->size = p->size - sizeof(struct MemEntry) - size;
        succ->is_free = 1;
        p->size = size;
        p->is_free = 0;
        p->file = file;
        p->line_num = line;

		if(succ->prev != p || p->next->prev != p || succ->prev == succ)
			abort();
       	//printf("Succ: %p Next %p (%p) Prev %p (%p) d\n", succ, succ->next, &(succ->next), succ->prev, &(succ->prev), succ->is_free); 
		//printf("Returning P: %p Next %p Prev %p %d\n", p, p->next, p->prev, p->is_free);
		//printf("Corresponding Mementry Here: %p\n", p);
		
		return ((void*) p) + sizeof(struct MemEntry);
    }

    printf(RED "Error: No room in any block to allocate this chunk!\n");
    printf("\tError made on line %zd in %s\n" RESET, line, file);
    return 0;
}


void* my_calloc(size_t size, string file, size_t line) {
    void* ptr = my_malloc(size, file, line);
    
    if (!ptr) {
        return 0;
    }

    memset(ptr, 0, size);
    
    return ptr;
}

void* my_realloc(void* ptr, size_t size, string file, size_t line){
    void* new = my_malloc(size, file, line);
    
    if(ptr){
        MemEntry assoc = ptr - sizeof(struct MemEntry);
        memcpy(new, ptr, assoc->size >= size ? size : assoc->size);

        my_free(ptr, file, line);
    }

    return new;
}


void my_free(void* p, string file, size_t line) {
    if (!p) {
        printf(RED "Error: Cannot free null pointer!\n");
        printf("\tError made on line %zd in %s\n" RESET, line, file);
        return;
    }

    MemEntry ptr, pred, succ;

    if ((string)(p-1) < block || (string)(p-1) > block+BLOCK_SIZE) {
        printf(RED "Error: Invalid free! Pointer was not malloc'd.\n");
        printf("\tError made on line %zd in %s\n" RESET, line, file);
        return;
    }

    // Get MemEntry struct of pointer to be freed
    ptr = p - sizeof(struct MemEntry);

/*	
	printf("Pointer %p Next %p Prev %p\n", ptr, ptr->next, ptr->prev);
	
	if(ptr->next)
		printf("\tNext: %d\n", ptr->next->is_free);

	if(ptr->prev)
		printf("\tPrev: %d\n", ptr->prev->is_free);
*/	

    if (ptr->pattern != BLOCK_SIZE + 69) {
        printf(RED "Error: Invalid free! Corrupt data.\n");
        printf("\tError made on line %zd in %s\n" RESET, line, file);
        return;
    } else if (ptr->is_free) {
        printf(RED "Error: Invalid free! Pointer is already freed.\n");
        printf("\tError made on line %zd in %s\n" RESET, line, file);
        return;
    }

	ptr->is_free = 1;

	MemEntry next = ptr->next;
	MemEntry prev = ptr->prev;

	if(ptr->prev){
		if(ptr->prev->is_free){
//			printf("Merging with previous node %p.\n", prev);
			prev->size += sizeof(struct MemEntry) + ptr->size;
			prev->next = next;
			ptr = prev;
		
			if(next)
				ptr->next->prev = prev;
		}
	}

	if(next){
//		printf(next->is_free ? "wtf\n" : "oh boy it works!\n");

		if(next->is_free){
			//printf("Merging with next node %p.\n", next);
			ptr->size +=  sizeof(struct MemEntry) + next->size;
			ptr->next = next->next;
		
			if(ptr->next)
				ptr->next->prev = ptr;
		}
	}
}


void leak_check() {
    MemEntry root = (MemEntry) block, p = root;
    int num_leaks = 0;

    printf("Leaked Memory Summary:\n");

    if (is_corrupt()) {
        printf(RED "\tThe data block is corrupt.\n");
        printf("\t\tCannot check for leaked memory.\n" RESET);
        return;
    }

    while (p) {
         if (!p->is_free) {
            printf(RED "\tLeaked memory allocation!\n");
            printf("\t\tLine %zd in %s\n" RESET, p->line_num, p->file);
            num_leaks++;
         }
         p = p->next;
    }

    if (num_leaks == 0) {
        printf(GREEN "\tNo leaked memory! :)\n" RESET);
    }

}


int is_corrupt() {

    MemEntry root = (MemEntry) block, p = root;

    while (p) {
        if (p->pattern != BLOCK_SIZE + 69)
            return 1;
        p = p->next;
    }

    return 0;
}
