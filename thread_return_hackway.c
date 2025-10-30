/*
Key Points: Hack Method using (void*)(long)res

1. Thread function must return void*:
   - C standard requires pthread functions to return a void* pointer.
   - Our value 'res' is an int, not a pointer.

2. 'res' is a local stack variable:
   - Local variables disappear after the function ends.
   - Returning its address directly would be unsafe.

3. Casting to long first:
   - On 64-bit systems, pointers are 8 bytes, ints are usually 4 bytes.
   - Mentor explanation: "We cast to long because long is the same size as a pointer on this system."
   - This allows the compiler to accept the conversion: int → long → void*.

4. Casting to void*:
   - (void*)(long)res tells the compiler to treat this number as a pointer.
   - Important: It does NOT point to valid memory; just stores the integer in a pointer variable.

5. Unsafe to dereference:
   - Doing *ret in main will likely cause a segmentation fault.
   - Pointer does not actually point to real memory.

6. Hack, not proper method:
   - This is a trick to make the code compile.
   - Not portable, unsafe, and should not be used in production.

7. Proper alternatives:
   - Static variable: static int res; return &res; // safe for single thread only
   - Dynamic memory: int *res = malloc(sizeof(int)); return res; // safe for multiple threads, must free() after use

8. Why it exists:
   - Sometimes shown to explain pointer casting.
   - Useful to understand why dynamic or static memory is the correct solution.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

 void *thread_function(void *arg)
{
    int *ptr = (int *)arg; // Cast void* argument to int* to access array
    int res; // Local stack variable to store sum (NOT dynamically allocated)
    res = *ptr + *(ptr+1); // Compute sum of first two integers
    
    //Converts the 4-byte integer into a long (8 bytes) first, then cast to void*.
    //This satisfies the compiler, because now the cast is from 8-byte long → 8-byte void*.
    //Now the integer value is “pretended” to be a pointer.
    //It’s just the number stored in the pointer variable.
    //If you try to dereference it (*ret) in main → segmentation fault.
    return (void *)(long)res; 
}
int main() 
{
    pthread_t tid;
    int num[] = {10, 20}; // Array of integers to pass to the thread
    int *ret; // Pointer to collect thread's return value
    
    // Create a thread
    // Arguments:
    // 1. &tid                → pointer to store thread ID
    // 2. NULL                → default thread attributes
    // 3. thread_function     → function thread will execute
    // 4. (void*)num          → pointer to array passed as argument
    if(pthread_create(&tid, NULL, thread_function, (void *)num) != 0)
    {
        printf("Thread not created \n");
        return -1;
    }
    
    // Wait for thread to finish and collect return value
    // pthread_join expects a void** as second argument
    // Here we pass (void**)&ret
    pthread_join(tid, (void**) &ret);
    
    // Attempt to access returned value
    // PROBLEM: ret is not a valid pointer — it just contains the integer cast as a pointer
    // Dereferencing it (*ret) would cause SEGFAULT
    // Here, just printing ret itself prints the "fake address" (actually the integer value cast as pointer)
    printf("back in main thread and returned value is %d \n", ret);

    return 0;
}