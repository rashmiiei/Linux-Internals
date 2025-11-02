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
    // Thread attribute object
    // Used to define thread properties like detach state, stack size, scheduling
    pthread_attr_t attr; 
    
    // Initialize attribute object
    // Always initialize before using
    pthread_attr_init(&attr); 
    
    // Set thread to DETACHED
    // Detached threads cannot be joined and clean up their own resources
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    
    pthread_t tid; // Thread ID variable
    
    // Create a new thread with the specified attributes
    pthread_create(&tid, &attr, thread_function, NULL);
    
    // Wait for the created thread to finish
    // pthread_join blocks the main thread until the specified thread exits
    // Second argument can store the thread's return value (we pass NULL since we don't need it)
    //It won't work in this case because the thread is already detachable
	// undefined behaviour. Better dont use it.
    pthread_join(tid, NULL);
    
    // Main thread prints its message
    printf("Back in main thread \n");
    
    // Destroy the attribute object
    // Good practice to clean up, although not strictly necessary here
    pthread_attr_destroy(&attr);
    
    return 0;
    
}

    