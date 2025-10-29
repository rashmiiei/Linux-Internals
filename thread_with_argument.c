#include <stdio.h>
#include <pthread.h> // For POSIX threads (pthread_create, pthread_join)

// ---------------------------------------------------------------------------
// Thread function
// ---------------------------------------------------------------------------
// The thread function accepts a void* argument (to allow passing any type of data)
// Here, we cast it back to int* to access the integer passed from main()
void * thread_function(void *arg)
{
    // Cast void* back to int* and dereference to get the integer value
    printf("Data from main function is %d \n", *(int *)arg);
    
    // Thread function must return void*, here we return NULL since no value needed
    return NULL;
}

int main() 
{
    pthread_t tid; // Thread ID variable
    int num = 10;  // Data to pass to the thread
    
    // Create a new thread
    // Parameters:
    // 1. &tid                 → pointer to store thread ID
    // 2. NULL                 → default thread attributes
    // 3. thread_function      → function the thread will execute
    // 4. (void*) &num         → argument to pass to the thread function
    if(pthread_create(&tid, NULL, thread_function, (void*) &num) != 0)
    {
        printf("thread creation failed \n"); // Error handling
        return -1;
    }
    
    // Wait for the thread to finish
    pthread_join(tid, NULL);

    return 0;
}