#include <stdio.h>
#include <pthread.h>

typedef struct
{
    int num;
    char ch;
    double d;
} data_t;

// ---------------------------------------------------------------------------
// Thread function
// ---------------------------------------------------------------------------
// This thread receives a pointer to data_t as void*.
// It casts the void* back to data_t* and accesses the fields using -> operator.
void *thread_function (void *arg)
{
    // Cast the void* argument back to a pointer to data_t
    data_t *data = (data_t *)arg;
    
    // Access struct members using '->' since data is a pointer
    printf("num = %d\n ch = %c\n d = %g\n", data->num, data->ch, data->d);
    return NULL;
}
int main() 
{
    pthread_t tid;
    data_t data = {10, 'A', 12.3}; // Initialize struct with example values
    
    // Create a thread
    // Parameters:
    // 1. &tid                → store thread ID
    // 2. NULL                → default thread attributes
    // 3. thread_function     → function the thread will execute
    // 4. (void*)&data        → pointer to struct passed as argument
    pthread_create(&tid, NULL, thread_function, (void*)&data);
    
    // Wait for thread to finish
    pthread_join(tid, NULL);
    
    printf("Back in main thread \n"); // Main thread continues
    
    return 0;
}