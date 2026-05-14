#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void sigint_handler(int signum)
{
    printf("SIGINT arrived \n");
}

int main()
{
    signal(SIGINT, sigint_handler);
    while(1)
    {
        printf("Inside main \n");
        sleep(1);
    }
    
    return 0;
}
