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
    
    // Thread finishes and returns NULL (no data to main)
    // For joinable threads, this return value can be collected by pthread_join
    return NULL; 
}

int main() 
{
    // Thread attribute object
    // Used to define thread properties like detach state, stack size, scheduling
    pthread_attr_t attr; 
    
    pthread_attr_init(&attr); // Initialize the attribute object
    
    // Always initialize before using, otherwise behavior is undefined

    // Set the detach state of the thread to JOINABLE
    // JOINABLE threads allow main (or any other thread) to wait for them using pthread_join
    // Default is already JOINABLE, but we set it explicitly for clarity
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    
    pthread_t tid; // Thread ID variable to store the thread identifier
    
    // Create a new thread
    // Parameters:
    // 1. &tid       -> pointer to store thread ID
    // 2. &attr      -> pointer to attribute object
    // 3. thread_function -> function that thread will execute
    // 4. NULL       -> argument to pass to thread function (none in this case)
    pthread_create(&tid, &attr, thread_function, NULL);
    
    // Wait for the created thread to finish
    // pthread_join blocks the main thread until the specified thread exits
    // Second argument can store the thread's return value (we pass NULL since we don't need it)
    pthread_join(tid, NULL);
    
     // At this point, the thread has finished execution
    printf("Back in main thread \n");
    
    // Destroy the attribute object
    // Good practice to clean up, although not strictly necessary here
    pthread_attr_destroy(&attr);
    
    return 0;
    
}
