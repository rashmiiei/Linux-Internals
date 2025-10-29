#include <stdio.h>
#include <pthread.h> // For POSIX threads (pthread_create, pthread_join)

// ---------------------------------------------------------------------------
// Thread function
// ---------------------------------------------------------------------------
// This thread function receives an array of integers as a void* argument.
// Inside the thread, we cast the void* back to int* to access array elements.
// Here, we calculate the sum of the first two elements of the array.
void * thread_function(void *arg)
{
    int *ptr = (int *)arg; // Cast void* to int* to access integer array
    printf("Sum is %d \n", *(ptr) + *(ptr+1)); // Calculate sum of first 2 elements
    return NULL; // Return NULL since no data needs to be returned
}


int main() 
{
    pthread_t tid; // Thread ID variable
    int num[] = {10, 20};  // Array of integers to pass to the thread
    
    // Create a new thread
    // Arguments:
    // 1. &tid                 → pointer to store thread ID
    // 2. NULL                 → default thread attributes
    // 3. thread_function      → function the thread will execute
    // 4. (void*)num           → pointer to integer array to pass as argument
    if(pthread_create(&tid, NULL, thread_function, (void*)num) != 0)
    {
        printf("thread creation failed \n"); // Error handling
        return -1;
    }
    
    // Wait for the thread to finish
    pthread_join(tid, NULL); // Blocks main thread until thread_function completes
    
    printf("Back in main thread \n");

    return 0;
}