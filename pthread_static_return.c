#include <stdio.h>
#include <pthread.h>

void *thread_function(void *arg)
{
    int *ptr = (int *)arg; // Cast void* argument to int* to access array
    static int res; // static variable persists after function ends
    res = *ptr + *(ptr+1); // sum first two integers
    return (void *)&res; // return address of static result
}
int main() 
{
    pthread_t tid;
    int num[] = {10, 20}; // Array of integers to pass to the thread
    int *ret; // Pointer to collect thread's return value
    
    // Create a thread
    // Arguments:
    // 1. &tid                → pointer to store thread ID
    // 2. NULL                → default thread attributes
    // 3. thread_function     → function thread will execute
    // 4. (void*)num          → pointer to array passed as argument
    if(pthread_create(&tid, NULL, thread_function, (void *)num) != 0)
    {
        printf("Thread not created \n");
        return -1;
    }
    
    // Wait for thread to finish and collect return value
    // Second argument is (void**)&ret because pthread_join expects void**
    pthread_join(tid, (void**) &ret);
    
    // Access the result returned by thread
    printf("back in main thread and returned value is %d \n", *ret);

    return 0;
}