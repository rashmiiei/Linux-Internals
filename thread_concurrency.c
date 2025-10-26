#include <stdio.h>
#include<pthread.h>
#include <unistd.h>

// ---------------------------------------------------------------------------
// Thread Function 1: print_X
// ---------------------------------------------------------------------------
// This thread runs independently and continuously prints 'X'.
// The function has the standard pthread signature: void* func(void* arg)
//   - 'arg' can carry data into the thread (not used here, so we pass NULL)
//   - return value can send data back when the thread finishes (we return NULL)
// ---------------------------------------------------------------------------
void * print_X(void *arg)
{
    // Infinite loop — thread keeps running until the process terminates
   while(1)
   {
       printf("X"); // Print a character to show this thread is active
   }
    // This line is never reached because of the infinite loop,
    // but pthread functions must return a void*.
   return NULL;
}

// ---------------------------------------------------------------------------
// Thread Function 2: print_O
// ---------------------------------------------------------------------------
// Same as print_X(), but prints 'O' continuously to represent another task.
// Running both together demonstrates true concurrency between threads.
// ---------------------------------------------------------------------------
void * print_O(void *arg)
{
    while(1)
   {
       printf("O"); // Print 'O' from the second thread
   }
   return NULL; 
}
int main() 
{
    pthread_t tid1, tid2; // Variables to store thread IDs for both threads
    
    // Create the first thread
    // Parameters:
    // 1. &tid1         → address of thread ID variable
    // 2. NULL          → default thread attributes
    // 3. print_X       → function executed by this thread
    // 4. NULL          → argument passed to the function (none)
    pthread_create(&tid1, NULL, print_X, NULL);
    
    // Create the second thread
    // Works the same as above, but runs print_O()
    pthread_create(&tid2, NULL, print_O, NULL);
    
    // Main thread sleeps for 1 second
    // This allows both threads to run and print output
    // Without this sleep, the main thread might exit immediately,
    // terminating the process before other threads have time to run
    sleep(1);
    
    // This message is printed by the main thread
    // after the 1-second delay.
    printf("\nback in main thread \n");

    // When main() exits, the process terminates,
    // and all threads are automatically killed.
    // In real applications, you'd use pthread_join() or pthread_detach()
    // to cleanly manage thread lifetimes.
    return 0;
}