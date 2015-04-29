PA5: Error detecting malloc() and free()
by Sakib Jalal and Andrew Lee

DESIGN
    We use a block of memory called "block" to allocate our memory blocks
    in. The memory block has a static size of BLOCK_SIZE. The my_malloc()
    function creates a memory chunk to allocate the amount of bytes that the
    user requests. The free() function frees a specified memory chunk
    from memory (block), and when freeing a memory chunk, we check the memory
    chunks preceding and succeeding the memory chunk to be freed. If they
    too happen to be free, we combine the space of the memory chunk that
    we want to free with the preceding and/or succeeding memory chunks.

    In our implementations of malloc() and free(), we account for several possible
    errors which may occur. We consider the errors of users freeing pointers
    that were never allocated, freeing pointers which were not returned from
    malloc and freeing a pointer which was already properly freed.

    To deal with saturation, the situation where there is no more space
    left for allocation in our block, we print an error message informing the
    user that there is no more room for allocation and we return a void pointer
    with value NULL, or 0.

    To deal with fragmentation, we implement a best fit algorithm for our
    malloc() function. Our malloc() searches through the memory chunks
    avaliable to see which chunk is greater than and also closest to the required
    size of the allocation we need to make. This reduces many possible
    fragmentation issues, thus optimizing our memory allocation.

SPACE AND TIME COMPLEXITY
    The space complexity for this program is O(1).  When calling malloc(), a
    constant amount of space is used to allocate each struct for each memory
    chunk. Overall, we have a constant amount of memory in which we make our
    allocations in the block. Obviously, free() has constant space complexity,
    as it does not use any extra space.

    The overall runtime complexity is O(n), where n is the number of memory
    chunks we have in our memory block. Our malloc() function takes O(n)
    to run because it checks all memory chunks to see which is the most suitable
    size for the allocation to be made. Our free function takes O(1) time
    because the free function has a constant number of instructions to execute
    in order to successfully free a memory chunk in block.

EXTRA CREDIT
    1. Leak Detection (20 points): We detect if any memory leaks occur at the end of
       executing any program which uses our malloc function. We implemented
       this by checking the is_free field for each MemEntry object. If the memory
       chunk's is_free field is equal to 0 at the end of the program's execution,
       we print to the leak summary that the memory chunk was not freed.

    2. Calloc (5 points): We implemented calloc() by calling malloc(), zeroing out
       the chunk of memory we are given by malloc with memset() and subsequently
       returning the pointer back to the user, with NULL checks in the middle.

    3. Corruption Detection (10 points): We check for corruption by checking if the
       pattern field for each memory chunk in our memory space is
       valid for a predetermined value, which we chose to be BLOCK_SIZE + 69.
       If it is not valid, we assume that the memory chunk has been written over
       with some other value and that our memory space has become corrupt.
	5. Realloc(5 Points): We implemented realloc() by calling my_malloc and then
	   using memcpy to copy the old pointer data to the new pointer. We then use my_free
	   to free the old pointer.
