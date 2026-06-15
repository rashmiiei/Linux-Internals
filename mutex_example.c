#include <stdio.h>
#include <pthread.h>

// Declare a global mutex variable.
// This will be used to synchronize access to shared data.
pthread_mutex_t lock;

// Shared global variable accessed by both threads.
// Since both threads modify it, we need to protect it with the mutex.
int count;

// Thread routine executed by each created thread.
void *thread_function (void *arg)
{
    // Infinite loop — this thread will run forever.
    // In real applications, we usually add a stopping condition.
    while(1)
    {
        // Lock the mutex before accessing the shared variable.
        // This ensures only one thread enters this section at a time.
        pthread_mutex_lock(&lock);
        
        // ======== START OF CRITICAL SECTION ========
        // Only one thread can execute these lines at once.
        count=0;
        count += 5;
        count += 10;
        // At this point, count will always be 15 (0 + 5 + 10).
        
        // Print the result.
        // This line is still inside the critical section,
        // so the other thread cannot print simultaneously.
        printf("%d \n", count);
        
        // ====== END OF CRITICAL SECTION ======

        // Unlock the mutex so that another thread can enter.
        pthread_mutex_unlock(&lock);
    }
}
int main() 
{
    // Initialize the mutex before using it.
    // The second parameter (NULL) means use default attributes.
    pthread_mutex_init (&lock, NULL);
    
    // Declare thread identifiers.
    pthread_t tid1, tid2;
    
    // Create two threads that both execute the same function.
    pthread_create(&tid1, NULL, thread_function, NULL);
    pthread_create(&tid2, NULL, thread_function, NULL);
    
    // Wait for both threads to complete.
    // Since the threads run infinite loops, this will never return.
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    
    // This line will never execute (threads never end),
    // but if they did, we’d reach here.
    printf("back in main thread \n");
    
     // Destroy the mutex to free system resources.
    pthread_mutex_destroy(&lock);
    

    return 0;
}
