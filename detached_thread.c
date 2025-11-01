#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

// Thread function: this function will be executed by the new thread
void *thread_function(void *arg)
{
    int num=5;
    while(num--)
    {
        printf("thread is executing \n");
        sleep(1); // Sleep for 1 second to simulate time-consuming task
    }
    return NULL; // Thread exits and returns NULL
}

int main() 
{
    //Creating an attribute object
    pthread_attr_t attr;
    
    //Initialise attr object
    pthread_attr_init(&attr);
    
    // Set the thread detach state to detached
    // Detached threads automatically release their resources when finished
    // We do not need to call pthread_join for detached threads
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    
    pthread_t tid; // Thread ID variable
    
    // Create a new thread with the specified attributes
    // Parameters:
    // 1. &tid: pointer to thread ID
    // 2. &attr: pointer to thread attribute object
    // 3. thread_function: function to be executed by thread
    // 4. NULL: argument to pass to thread function (none in this case)
    pthread_create(&tid, &attr, thread_function, NULL);
    
    // Main thread sleeps for 6 seconds
    // This allows the detached thread to run before main thread exits
    sleep(6);
    printf("Back in main thread \n");
    
    // Destroy the attribute object as it's no longer needed
    pthread_attr_destroy(&attr);
    
    // Exit the main thread, but keep the process alive until all threads finish
    // Normally pthread_exit is not needed if all threads are joined or detached finishes
    pthread_exit(NULL);
    
    return 0;
}