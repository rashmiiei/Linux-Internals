#include <stdio.h>      // For printf()
#include <pthread.h>    // For POSIX thread functions
#include <unistd.h>     // For sleep()

// Thread function — this function will be executed by the new thread
// Signature: void* function_name(void* arg)
//   - 'void* arg' allows passing any type of argument to the thread
//   - 'void*' return allows the thread to return any type of result
// This function runs independently of the main thread.
void *thread_function (void *arg)
{
    printf("Thread is executing \n"); 	// Print message to show thread is running
    return NULL; 						// Thread returns NULL (required for pthreads)
}

int main() 
{
    pthread_t tid; // Declare a thread ID variable
    
    // Create a new thread
    // Arguments:
    // 1. &tid          → pointer to thread ID
    // 2. NULL          → default thread attributes
    // 3. thread_function → function the thread will execute
    // 4. NULL          → argument to pass to the thread function
    if(pthread_create(&tid, NULL, thread_function, NULL) != 0)
    {
        printf("Thread creation failed \n"); 	// Error handling if thread creation fails
        return -1; 								// Exit with error code
    }
    sleep(1); // Pause main thread to ensure new thread has time to execute
    printf("back in main thread \n"); // Message from main thread
}