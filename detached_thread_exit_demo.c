#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Thread function: executed by the new thread
void * thread_function(void *arg)
{
    int num=5;
    while(num--)
    {
        printf("Thread is executing \n");
        sleep(1); // Sleep 1 second to simulate work
    }
    
    // Thread finishes and returns NULL
    // Detached threads clean up automatically; return value cannot be collected
    return NULL; 
}

int main() 
{
    // Thread attribute object: used to define properties of the thread
    // Examples: detach state, stack size, scheduling policy, etc.
    pthread_attr_t attr; 
    
    // Initialize the attribute object with default values
    // Must always initialize before using
    pthread_attr_init(&attr); 
    
    // Set the thread to be DETACHED
    // Detached threads automatically clean up resources after finishing
    // You CANNOT join a detached thread
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    
    pthread_t tid; 
    
    // Create a new thread with the specified attributes
    // Parameters:
    // 1. &tid -> pointer to store the thread ID
    // 2. &attr -> pointer to the attribute object
    // 3. thread_function -> function the thread will execute
    // 4. NULL -> argument passed to thread function (none in this case)
    pthread_create(&tid, &attr, thread_function, NULL);
    
    // Attempt to join a detached thread
    // THIS IS INCORRECT: joining a detached thread is not allowed
    // Behavior is undefined (usually returns error EINVAL or may crash)
    pthread_join(tid, NULL);
    
    // Print message from main thread
    // May execute before, after, or interleaved with detached thread output
    // Output is unpredictable due to thread scheduling
    printf("Back in main thread \n");
    
    // Destroy the attribute object to clean up resources
    pthread_attr_destroy(&attr);
    
    // Exit main thread but keep process alive for any remaining threads
    // Necessary here because the detached thread may still be running
    //we just pass NULL to indicate “no value to return
    pthread_exit(NULL);
    
}

    