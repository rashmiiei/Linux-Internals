#include <stdio.h>
#include <pthread.h> // For POSIX threads (pthread_create, pthread_join)

// ---------------------------------------------------------------------------
// Thread Function 1: print_X
// ---------------------------------------------------------------------------
// This thread continuously prints 'X'.
// Signature: void* function(void* arg)
//   - 'arg' can carry data into the thread (not used here, so we pass NULL)
//   - return value is void*; we return NULL because we don't need to return anything
// ---------------------------------------------------------------------------
void *print_X (void *arg)
{
    // Infinite loop: this thread will keep running until the process terminates
    while(1)
    {
        printf("X"); // Print character to indicate thread activity
    }
    return NULL;
}

// ---------------------------------------------------------------------------
// Thread Function 2: print_O
// ---------------------------------------------------------------------------
// Similar to print_X, but prints 'O' instead.
// Demonstrates concurrent execution of multiple threads.
// ---------------------------------------------------------------------------
void *print_O (void *arg)
{
    while(1)
    {
        printf("O"); // Print character to indicate thread activity
    }
    return NULL;
}
int main() 
{
    pthread_t tid1, tid2; // Thread ID variables for both threads
    
    // Create first thread to run print_X
    // Arguments:
    // 1. &tid1         → pointer to thread ID variable
    // 2. NULL          → default thread attributes (stack size, scheduling)
    // 3. print_X       → function the thread will execute
    // 4. NULL          → argument passed to the thread function (none here)
    pthread_create(&tid1, NULL, print_X, NULL);
    
    // Create second thread to run print_O
    pthread_create(&tid2, NULL, print_O, NULL);
    
    // -----------------------------------------------------------------------
    // Synchronization using pthread_join
    // -----------------------------------------------------------------------
    // pthread_join blocks the calling thread (main thread here) until the
    // specified thread terminates.
    // This ensures that the main thread waits for both threads to finish.
    // Since both threads run infinite loops, the main thread will wait forever
    // and the next printf() will practically never execute.
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    
    // This line will not execute in this program because both threads are infinite
    printf("\n back in main thread \n");
    
    return 0;

}
