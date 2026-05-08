#include <unistd.h>
#include <stdio.h>

int main()
{
    printf("executing ls using exec()\n");
    
    // execl() replaces the current process image with /bin/ls
    // Arguments:
    // 1. Path to the executable: "/bin/ls"
    // 2. argv[0]: "ls" (program name)
    // 3. "-l": option for long listing format
    // 4. "-h": option for human-readable file sizes
    // 5. NULL: marks the end of the argument list
    execl("/bin/ls", "ls", "-l","-h", NULL);

    // If exec() succeeds, this line will never execute
    // because the current process is replaced by "ls"
    printf("After exec()\n");

    return 0;
}
